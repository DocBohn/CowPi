/**************************************************************************//**
 *
 * @file cowpi_lcd1602.c
 *
 * @brief @copybrief cowpi_lcd1602.h
 *
 * @copydetails cowpi_lcd1602.h
 *
 ******************************************************************************/

/* CowPi (c) 2021-22 Christopher A. Bohn
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Arduino.h>
#include <stdio.h>
#include "cowpi_setup.h"
#include "cowpi_lcd1602.h"
#include "cowpi_internal.h"


#define ENTRY_MODE_MARKER 0x4
static uint8_t last_entry_mode = ENTRY_MODE_MARKER;
static bool is_backlit = false;


cowpi_lcd1602_send_halfbyte_t cowpi_lcd1602_send_halfbyte = NULL;

static void cowpi_lcd1602_set_4bit_mode(unsigned int configuration);
static void cowpi_lcd1602_send_halfbyte_spi(uint8_t halfbyte, bool is_command);
static void cowpi_lcd1602_send_halfbyte_i2c(uint8_t halfbyte, bool is_command);


/** @private */
void cowpi_setup_lcd1602(unsigned int configuration) {
    if (!(configuration & (SPI | I2C))) {
        char s[115];
        cowpi_error(strcpy_P(s, PSTR("CowPi must use a serial protocol with LCD1602. "
                                     "Use `cowpi_setup(LCD1602 | SPI);` or `cowpi_setup(LCD1602 | I2C);`.")));
        // That may not always be the case -- for example, Arduino Mega 2560, Raspberry Pi, or Raspberry Pi Pico
    }
    /* HD44780U datasheet says LCD needs 40ms after Vcc=2.7V, or 15ms after Vcc=4.5V */
    delayMicroseconds(12500);   // Don't want to use delay(50) just in case interrupts are disabled.
    delayMicroseconds(12500);   // Don't want to use delayMicroseconds(50000) because that's 3x longer than
    delayMicroseconds(12500);   // delayMicroseconds is safe for. Note that 16383 == 2**14 - 1 -- this suggests
    delayMicroseconds(12500);   // that while there will be some drift, the real problem is integer overflow
    /* Place in 4-bit mode because 74HC595 is an 8-bit shift register, and we need RS & EN bits, too */
    cowpi_lcd1602_set_4bit_mode(configuration);
    /* 4-bit mode, 2 line display, 5x8 dot matrix */
    cowpi_lcd1602_send_command(0x28);
    /* with each character: increment location, do not shift display (0x06) */
    cowpi_lcd1602_send_command(LCDENTRY_CURSORMOVESRIGHT | LCDENTRY_TEXTNOSHIFT);
    /* display on, cursor off, no blink (0x0C) */
    cowpi_lcd1602_send_command(LCDONOFF_DISPLAYON | LCDONOFF_CURSOROFF | LCDONOFF_BLINKOFF);
    /* clear display */
    cowpi_lcd1602_clear_display();
}

void cowpi_lcd1602_set_send_halfbyte_function(void (*send_halfbyte_function)(uint8_t halfbyte, bool is_command)) {
    cowpi_lcd1602_send_halfbyte = send_halfbyte_function;
}

void cowpi_lcd1602_place_character(uint8_t address, uint8_t character) {
    cowpi_lcd1602_place_cursor(address);
    cowpi_lcd1602_send_character(character);
}

void cowpi_lcd1602_place_cursor(uint8_t address) {
    cowpi_lcd1602_send_command(address | 0x80);
}

void cowpi_lcd1602_send_command(uint8_t command) {
    cowpi_lcd1602_send_halfbyte((command >> 4) & 0xF, true);
    cowpi_lcd1602_send_halfbyte( command       & 0xF, true);
    if (command & ENTRY_MODE_MARKER) {
        last_entry_mode = command;
    }
    delayMicroseconds(50);      // most commands require 37us-38us according to various datasheets; the exceptions have their own functions
}

void cowpi_lcd1602_send_character(uint8_t character) {
    cowpi_lcd1602_send_halfbyte((character >> 4) & 0xF, false);
    cowpi_lcd1602_send_halfbyte(character & 0xF, false);
    delayMicroseconds(50);      // HD44780U datasheet says 41us (37+4) needed until character is updated and ddram address is updated; SPLC780D simply says 38us
}

void cowpi_lcd1602_create_character(uint8_t encoding, const uint8_t pixel_vector[8]) {
    uint8_t cgram_start = (encoding & 0x7) << 3;
    for (int row = 0; row < 8; row++) {
        cowpi_lcd1602_send_command((cgram_start + row) | 0x40);
        cowpi_lcd1602_send_character(pixel_vector[row]);
    }
}

void cowpi_lcd1602_clear_display() {
    cowpi_lcd1602_send_command(0x01);
    delayMicroseconds(5000);    // tom alby says 5ms; adafruit uses 2ms; HD44780U datasheet simply says that 0x20 is written to each position; SPLC780D datasheet says 1.52ms
}

void cowpi_lcd1602_return_home() {
    cowpi_lcd1602_send_command(0x02);
    delayMicroseconds(2000);    // tom alby is silent; adafruit uses 2ms; datasheets agree on 1.52ms
}

void cowpi_lcd1602_set_backlight(bool backlight_on) {
    is_backlit = backlight_on;
    cowpi_lcd1602_send_command(last_entry_mode);
}

void cowpi_lcd1602_set_4bit_mode(unsigned int configuration) {
    uint8_t i2c_address = cowpi_get_display_i2c_address();
    if (!cowpi_lcd1602_send_halfbyte) {
        if (configuration & SPI) {
            cowpi_lcd1602_set_send_halfbyte_function(cowpi_lcd1602_send_halfbyte_spi);
        } else if (configuration & I2C) {
            if ((i2c_address < 8) || (i2c_address > 127)) {
                char s[61];
                cowpi_error(strcpy_P(s, PSTR("I2C Peripheral address must be between 8 and 127, inclusive.")));
            }
            cowpi_lcd1602_set_send_halfbyte_function(cowpi_lcd1602_send_halfbyte_i2c);
        } else {
            char s[115];
            cowpi_error(strcpy_P(s, PSTR("CowPi must use a serial protocol with LCD1602. "
                                         "Use `cowpi_setup(LCD1602 | SPI);` or `cowpi_setup(LCD1602 | I2C);`.")));
            // That may not always be the case -- for example, Arduino Mega 2560, Raspberry Pi, or Raspberry Pi Pico
        }
    }
    /* If initial state is:     8-bit mode      4-bit mode interbyte    4-bit mode intrabyte
     *      then LCD sees...                                                                */
    cowpi_lcd1602_send_halfbyte(0x3, true);
    /*                                                                  0x3 finishes byte   */
    delayMicroseconds(5000);    // HD44780U datasheet says wait > 4.1ms -- worst case if display was intrabyte
    cowpi_lcd1602_send_halfbyte(0x3, true);
    /*                          0x33: 8-bit mode    0x33: 8-bit mode                        */
    delayMicroseconds(200);     // HD44780U datasheet says wait more than 100us
    cowpi_lcd1602_send_halfbyte(0x3, true);
    /*                          0x30: 8-bit mode    0x30: 8-bit mode    0x33: 8-bit mode    */
    delayMicroseconds(200);     // not in the datasheets, but we determined experimentally that 100us is needed
    cowpi_lcd1602_send_halfbyte(0x2, true);
    /*                          0x20: 4-bit mode    0x20: 4-bit mode    0x20: 4-bit mode    */
    delayMicroseconds(200);     // doesn't seem to be needed ¯\_(ツ)_/¯
}

static void cowpi_lcd1602_send_halfbyte_spi(uint8_t halfbyte, bool is_command) {
    // we'll use the AdaFruit mapping for its SPI+I2C interface -- probably will add other dialect(s) later
    /* LSB    QH  QG  QF  QE  QD  QC  QB  QA  MSB *
     * LSB  LITE  D4  D5  D6  D7  EN  RS  xx  MSB */
    uint8_t rs = is_command ? 0 : 1 << 6;
    uint8_t en = 1 << 5;
    uint8_t packet = rs | (halfbyte << 1) | (is_backlit ? 1 : 0);
    // place data on the line
    digitalWrite(SPI_CHIP_SELECT, LOW);
    shiftOut(MOSI, SCK, cowpi_is_spi_lsbfirst() ? LSBFIRST : MSBFIRST, packet);
    digitalWrite(SPI_CHIP_SELECT, HIGH);
    // pulse
    digitalWrite(SPI_CHIP_SELECT, LOW);
    shiftOut(MOSI, SCK, cowpi_is_spi_lsbfirst() ? LSBFIRST : MSBFIRST, packet | en);
    digitalWrite(SPI_CHIP_SELECT, HIGH);
    // Tom Alby uses NOPs to get to create an exact 0.5us pulse (6 NOPs (6 cycles) + 1 memory write (2 cycles) = 0.5us)
    // but that isn't portable (also: AVR docs say to use _delay_ms() or _delay_us(), which also aren't portable)
    // However, since we're only doing a half-byte at a time, function calls, etc., will provide sufficient delay
    delayMicroseconds(1);
    // end the pulse
    digitalWrite(SPI_CHIP_SELECT, LOW);
    shiftOut(MOSI, SCK, cowpi_is_spi_lsbfirst() ? LSBFIRST : MSBFIRST, packet);
    digitalWrite(SPI_CHIP_SELECT, HIGH);
}

static inline bool transmit_bitbang_i2c(uint8_t value) {
    // On a 16MHz ATMega328P, `shiftOut` should give us 77-91MHz clock, might be too fast for I2C in practice.
    // Probably same (but maybe faster) on Arduino Nano Every.
    // Will definitely be too fast on Arduino's ARM-based devices.
    printf("sending 0x%x\n", value);
    for (int i = 0; i < 8; i++) {
        delayMicroseconds(4);   // 4.7us t_scl, minus the 1us we're going to delay for t_sds
        digitalWrite(SDA, (value >> (7 - i)) & 0x1);
        delayMicroseconds(2);   // 1us t_icr + 250ns t_sds
        digitalWrite(SCL, HIGH);
        delayMicroseconds(6);   // 1us t_icr + 4us t_sch + 0.3us t_icf + 0ns t_sdh
        digitalWrite(SCL, LOW);
    }
    delayMicroseconds(4);       // t_phl = ??
//    digitalWrite(SDA, LOW);
    pinMode(SDA, INPUT);
    delayMicroseconds(2);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(3);
    uint8_t nack = digitalRead(SDA);
    delayMicroseconds(3);
    digitalWrite(SCL, LOW);
    pinMode(SDA, OUTPUT);

    digitalWrite(SDA, LOW);
    return !nack;
}

static void cowpi_lcd1602_send_halfbyte_i2c(uint8_t halfbyte, bool is_command) {
//    printf("halfbyte = 0x%x\tis_command = %d\n", halfbyte, is_command);
    uint8_t packet = 0, rs = 0, en = 0;
    unsigned int dialect = cowpi_get_display_dialect();
    if (dialect == COWPI_DEFAULT) {
        // this mapping is used with most I2C interfaces and libraries
        // https://github.com/johnrickman/LiquidCrystal_I2C
        // https://github.com/blackhack/LCD_I2C
        /* MSB  P7  P6  P5  P4  P3  P2  P1  P0  LSB *
         * MSB  D7  D6  D5  D4 LITE EN  RW  RS  LSB */
        rs = is_command ? 0 : 1;
        en = 1 << 2;
        packet = rs | (halfbyte << 4) | (is_backlit ? 1 << 3 : 0);
    } else if (dialect == ADAFRUIT) {
        // this mapping is used with AdaFruit's SPI+I2C interface
        // https://github.com/adafruit/Adafruit_LiquidCrystal
        /* MSB   GP7 GP6 GP5 GP4 GP3 GP2 GP1 GP0  LSB *
         * MSB  LITE  D7  D6  D5  D4  EN  RS  xx  LSB */
        rs = is_command ? 0 : 1 << 1;
        en = 1 << 2;
        packet = rs | (halfbyte << 3) | (is_backlit ? 1 << 7 : 0);
    } else {
        char s[73];
        cowpi_error(strcpy_P(s, PSTR("CowPi only knows COWPI_DEFAULT and ADAFRUIT dialects for I2C-to-LCD1602 mapping.")));
    }
    // start bit
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
    while (!(TWCR & (1<<TWINT))) {}
//    if ((TWSR & 0xF8) != 0x08) cowpi_error("Controller did not send I2C start!");
    // I2C address + /w
    TWDR = cowpi_get_display_i2c_address() << 1;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT))) {}
//    if ((TWSR & 0xF8) != 0x18) cowpi_error("I2C peripheral did not receive address!");
    // place data on the line
    TWDR = packet;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT))) {}
//    if ((TWSR & 0xF8)!= 0x28) cowpi_error("I2C peripheral did not receive data!");
    // pulse
    TWDR = packet | en;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT))) {}
//    if ((TWSR & 0xF8)!= 0x28) cowpi_error("I2C peripheral did not receive leading edge of the pulse!");
    delayMicroseconds(1);
    // end the pulse
    TWDR = packet;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT))) {}
//    if ((TWSR & 0xF8)!= 0x28) cowpi_error("I2C peripheral did not receive the trailing edge of the pulse!");
    // stop bit
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
/*
    // hold bus "free" for 4.7us (t_buf) between stop and start (almost certainly redundant)
    digitalWrite(SDA, HIGH);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(5);
    // start bit
    digitalWrite(SDA, LOW);
    delayMicroseconds(5);   // .3us t_icf + 4us t_sth (start hold)
    digitalWrite(SCL, LOW);
//    printf("starting...");TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
//    while (!(TWCR & (1<<TWINT)));
//    if ((TWSR & 0xF8) != 0x08) cowpi_error("Controller did not send I2C start!"); else printf("start bit sent\n");
    // I2C address + /w
    bool ack = transmit_bitbang_i2c(cowpi_get_display_i2c_address() << 1);
    if (!ack) cowpi_error("I2C peripheral did not receive address!");
    // place data on the line
    ack = transmit_bitbang_i2c(packet);
    if (!ack) cowpi_error("I2C peripheral did not receive data!");
    // pulse
    transmit_bitbang_i2c(packet | en);
    if (!ack) cowpi_error("I2C peripheral did not receive leading edge of the pulse!");
    delayMicroseconds(1);
    // end the pulse
    transmit_bitbang_i2c(packet);
    if (!ack) cowpi_error("I2C peripheral did not receive trailing edge of the pulse!");
    // stop bit
    digitalWrite(SDA, LOW); // should already be low from ack bit, but just to be sure
    digitalWrite(SCL, LOW); // should already be low, but just to be sure
    delayMicroseconds(5);   // 5us t_sch
    digitalWrite(SCL, HIGH);
    delayMicroseconds(5);   // 1us t_icr + 4us t_sps
    digitalWrite(SDA, HIGH);
//    printf("stopping..."); TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); printf("stopped\n");
//    TWCR = 1<<TWINT;
*/
}

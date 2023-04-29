/**************************************************************************//**
 *
 * @file cowpi_setup.c
 *
 * @brief @copybrief cowpi_setup.h
 *
 * @copydetails cowpi_setup.h
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
#include "cowpi_internal.h"
#include "cowpi_setup.h"
#include "cowpi_boards.h"
#include "cowpi_dummy_pgmspace.h"


static unsigned int cowpi_display_device_and_dialect = COWPI_DEFAULT;
static uint8_t display_i2c_address = 255;


void cowpi_setup(unsigned int configuration) {
    /* Switches and Buttons */
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_SWITCH_DEFAULT, INPUT_PULLUP);     // When using SPI or when no protocol is specified
    pinMode(LEFT_SWITCH_ALTERNATE, INPUT_PULLUP);   // When using I2C
    pinMode(RIGHT_SWITCH_DEFAULT, INPUT_PULLUP);    // When using SPI or when no protocol is specified
    pinMode(RIGHT_SWITCH_ALTERNATE, INPUT_PULLUP);  // When using I2C
    pinMode(LED_EXTERNAL, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    /* Keypad */
    pinMode(KEYPAD_ROW_1, OUTPUT);
    pinMode(KEYPAD_ROW_4, OUTPUT);
    pinMode(KEYPAD_ROW_7, OUTPUT);
    pinMode(KEYPAD_ROW_STAR, OUTPUT);
    pinMode(KEYPAD_COLUMN_1, INPUT_PULLUP);
    pinMode(KEYPAD_COLUMN_2, INPUT_PULLUP);
    pinMode(KEYPAD_COLUMN_3, INPUT_PULLUP);
    pinMode(KEYPAD_COLUMN_A, INPUT_PULLUP);
    digitalWrite(KEYPAD_ROW_1, LOW);
    digitalWrite(KEYPAD_ROW_4, LOW);
    digitalWrite(KEYPAD_ROW_7, LOW);
    digitalWrite(KEYPAD_ROW_STAR, LOW);
    /* External Interrupts */
    pinMode(PUSHBUTTON_NAND, INPUT);
    pinMode(KEYPAD_NAND, INPUT);
    /* Display Module */
    if (configuration & SPI) {
        pinMode(SPI_CHIP_SELECT, OUTPUT);
        pinMode(MOSI, OUTPUT);
        pinMode(SCK, OUTPUT);
        digitalWrite(SPI_CHIP_SELECT, HIGH);
        digitalWrite(MOSI, LOW);
        digitalWrite(SCK, LOW);
        /* Enabling and disabling SPI must happen just-in-time
         * because enabling SPI overrides DDR for CIPO pin
         * (D12 except D50 on Mega2560), setting it to input.
         * See `cowpi_spi_enable` and `cowpi_spi_disable`. */
    }
    if (configuration & I2C) {
        pinMode(SDA, OUTPUT);
        pinMode(SCL, OUTPUT);
        digitalWrite(SDA, HIGH);
        digitalWrite(SCL, HIGH);
        cowpi_initialize_i2c;
    }
    if (configuration & MAX7219) {
        cowpi_display_device_and_dialect |= MAX7219;
        cowpi_setup_max7219(configuration);
    }
    if (configuration & LCD1602) {
        cowpi_display_device_and_dialect |= LCD1602;
        cowpi_setup_lcd1602(configuration);
    }
}

bool cowpi_is_spi_lsbfirst(void) {
    return ((cowpi_display_device_and_dialect & (DISPLAY_DIALECT_MASK | DISPLAY_DEVICE_MASK)) == (ADAFRUIT | LCD1602));
}

void cowpi_set_display_dialect(unsigned int dialect) {
    cowpi_display_device_and_dialect = (cowpi_display_device_and_dialect & ~DISPLAY_DIALECT_MASK) | dialect;
}

unsigned int cowpi_get_display_dialect(void) {
    return (cowpi_display_device_and_dialect & DISPLAY_DIALECT_MASK);
}

void cowpi_set_display_i2c_address(uint8_t peripheral_address) {
    if ((peripheral_address < 8) || (peripheral_address > 127)) {
        char s[61];
        cowpi_error(strcpy_P(s, PSTR("I2C Peripheral address must be between 8 and 127, inclusive.")));
    }
    display_i2c_address = peripheral_address;
}

uint8_t cowpi_get_display_i2c_address(void) {
    return display_i2c_address;
}

/** @private */
void cowpi_error(const char *message) {
    /* Try to give useful information */
    if (stdout) {
        printf("%s\n", message);
    }
    for (;;) {
        digitalWrite(LED_EXTERNAL, HIGH);
        digitalWrite(LED_BUILTIN, HIGH);
        /* if interrupts are disabled then both LEDs lit is the best warning we can give */
        delay(1);
        digitalWrite(LED_EXTERNAL, HIGH);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_EXTERNAL, LOW);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
    }
}

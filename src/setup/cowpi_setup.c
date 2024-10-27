/**************************************************************************//**
 *
 * @file cowpi_setup.c
 *
 * @brief @copybrief cowpi_setup.h
 *
 * @copydetails cowpi_setup.h
 *
 ******************************************************************************/

/* CowPi (c) 2021-24 Christopher A. Bohn
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
#include <CowPi_stdio.h>
#include "../internal/cowpi_internal.h"
#include "cowpi_setup.h"


FILE *cowpi_setup(unsigned long console_bitrate,
                  cowpi_display_module_t display_module,
                  cowpi_display_module_protocol_t communication_protocol) {
    /* stderr */
    stderr = cowpi_add_display_module(
            (cowpi_display_module_t) {.display_module = MORSE_CODE, .words_per_minute = 7},
#if defined (ARDUINO_RASPBERRY_PI_PICO)
            (cowpi_display_module_protocol_t) {.protocol = NO_PROTOCOL, .data_pin = INTERNAL_LED}
#else
            (cowpi_display_module_protocol_t) {.protocol = NO_PROTOCOL, .data_pin = RIGHT_LED}
#endif //PICO or no
    );
    /* stdin & stdout */
    if (console_bitrate > 0) {
        cowpi_stdio_setup(console_bitrate);
    }
    if (stderr == NULL) {
        stderr = stdout;
    }
    /* determine the configuration */
    cowpi_protocol = communication_protocol.protocol;
    if (cowpi_protocol == COWPI_SPI) {
        cowpi_left_switch = LEFT_SWITCH_SPI;
        cowpi_right_switch = RIGHT_SWITCH_SPI;
        cowpi_data_pin = DATA_SPI;
        cowpi_clock_pin = CLOCK_SPI;
        cowpi_latch_pin = CHIP_SELECT_SPI;
    } else if (cowpi_protocol == COWPI_I2C) {
        cowpi_left_switch = LEFT_SWITCH_I2C;
        cowpi_right_switch = RIGHT_SWITCH_I2C;
        cowpi_data_pin = DATA_I2C;
        cowpi_clock_pin = CLOCK_I2C;
    } else {}
    /* unused pins on UnoNano and Mega form factors */
    cowpi_set_floating_input_pins((1 << 2) | (1 << 3));
    /* LEDs */
    cowpi_set_output_pins((1 << LEFT_LED) | (1 << RIGHT_LED) | (1 << INTERNAL_LED));
    /* switches and buttons */
    cowpi_set_pullup_input_pins((1 << LEFT_BUTTON) | (1 << RIGHT_BUTTON));
    if (cowpi_protocol != NO_PROTOCOL) {
        cowpi_set_pullup_input_pins((1 << cowpi_left_switch) | (1 << cowpi_right_switch));
    } else {
        // we don't know which pins are used for the switches, so we'll prep both possibilities
        cowpi_set_pullup_input_pins((1 << LEFT_SWITCH_SPI) | (1 << LEFT_SWITCH_I2C) | (1 << RIGHT_SWITCH_SPI) | (1 << RIGHT_SWITCH_I2C));
    }
    /* keypad */
    cowpi_set_output_pins((1 << KEYPAD_ROW_1) | (1 << KEYPAD_ROW_4) | (1 << KEYPAD_ROW_7) | (1 << KEYPAD_ROW_STAR));
    cowpi_set_pullup_input_pins((1 << KEYPAD_COLUMN_1) | (1 << KEYPAD_COLUMN_2) | (1 << KEYPAD_COLUMN_3) | (1 << KEYPAD_COLUMN_A));
    /* display module */
    if (cowpi_protocol == COWPI_SPI) {
        cowpi_set_output_pins((1 << cowpi_data_pin) | (1 << cowpi_clock_pin) | (1 << cowpi_latch_pin));
        digitalWrite(cowpi_data_pin, LOW);
        digitalWrite(cowpi_clock_pin, LOW);
        digitalWrite(cowpi_latch_pin, HIGH);
    } else if (cowpi_protocol == COWPI_I2C) {
        cowpi_set_floating_input_pins((1 << cowpi_data_pin) | (1 << cowpi_clock_pin));
    } else {}
    if (display_module.display_module == NO_MODULE) {
        return NULL;
    } else {
        FILE *display = cowpi_add_display_module(display_module, communication_protocol);
        if (display == NULL) {
            fprintf(stderr, "\aNo display module\f");
        }
        return display;
    }
}


uint32_t cowpi_output_pins = 0;
uint32_t cowpi_floating_input_pins = 0;
uint32_t cowpi_pullup_input_pins = 0;
uint32_t cowpi_pulldown_input_pins = 0;

void cowpi_set_output_pins(uint32_t pins) {
#if defined (__AVR_ATmega328P__)
    uint8_t ddr_mask;
    ddr_mask = pins & 0xFF;
    DDRD |= ddr_mask;   // pins 0-7
    ddr_mask = (pins >> 8) & 0x3F;
    DDRB |= ddr_mask;   // pins 8-13
    ddr_mask = (pins >> 14) & 0x3F;
    DDRC |= ddr_mask;   // pins 14-19
//#elif defined (ARDUINO_ARCH_RP2040)
    // It looks like RP2040 has a separate register for each pad, so there's no
    // conciseness benefit to directly manipulating the GPIO registers.
#else
    for (int i = 0; i < 32; i++) {
        if (pins & (1 << i)) {
//            pinMode(i, OUTPUT);
            cowpi_pin_mode(i, OUTPUT);
        }
    }
#endif
    cowpi_output_pins |= pins;
    cowpi_floating_input_pins &= ~pins;
    cowpi_pullup_input_pins &= ~pins;
    cowpi_pulldown_input_pins &= ~pins;
}

void cowpi_set_floating_input_pins(uint32_t pins) {
#if defined (__AVR_ATmega328P__)
    uint8_t ddr_mask;
    ddr_mask = pins & 0xFF;
    DDRD &= ~ddr_mask;  // pins 0-7
    PORTD &= ~ddr_mask;
    ddr_mask = (pins >> 8) & 0x3F;
    DDRB &= ~ddr_mask;  // pins 8-13
    PORTB &= ~ddr_mask;
    ddr_mask = (pins >> 14) & 0x3F;
    DDRC &= ~ddr_mask;  // pins 14-19
    PORTC &= ~ddr_mask;
#else
    for (int i = 0; i < 32; i++) {
        if (pins & (1 << i)) {
//            pinMode(i, INPUT);
            cowpi_pin_mode(i, INPUT);
        }
    }
#endif
    cowpi_output_pins &= ~pins;
    cowpi_floating_input_pins |= pins;
    cowpi_pullup_input_pins &= ~pins;
    cowpi_pulldown_input_pins &= ~pins;
}

void cowpi_set_pullup_input_pins(uint32_t pins) {
#if defined (__AVR_ATmega328P__)
    uint8_t ddr_mask;
    ddr_mask = pins & 0xFF;
    DDRD &= ~ddr_mask;  // pins 0-7
    PORTD |= ddr_mask;
    ddr_mask = (pins >> 8) & 0x3F;
    DDRB &= ~ddr_mask;  // pins 8-13
    PORTB |= ddr_mask;
    ddr_mask = (pins >> 14) & 0x3F;
    DDRC &= ~ddr_mask;  // pins 14-19
    PORTC |= ddr_mask;
#else
    for (int i = 0; i < 32; i++) {
        if (pins & (1 << i)) {
//            pinMode(i, INPUT_PULLUP);
            cowpi_pin_mode(i, INPUT_PULLUP);
        }
    }
#endif
    cowpi_output_pins &= ~pins;
    cowpi_floating_input_pins &= ~pins;
    cowpi_pullup_input_pins |= pins;
    cowpi_pulldown_input_pins &= ~pins;
}

#ifdef ARDUINO_ARCH_RP2040
void cowpi_set_pulldown_input_pins(uint32_t pins) {
#if defined (__AVR_ATmega328P__)
    uint8_t ddr_mask;
    ddr_mask = pins & 0xFF;
    DDRD &= ~ddr_mask;  // pins 0-7
    PORTD |= ddr_mask;
    ddr_mask = (pins >> 8) & 0x3F;
    DDRB &= ~ddr_mask;  // pins 8-13
    PORTB |= ddr_mask;
    ddr_mask = (pins >> 14) & 0x3F;
    DDRC &= ~ddr_mask;  // pins 14-19
    PORTC |= ddr_mask;
#else
    for (int i = 0; i < 32; i++) {
        if (pins & (1 << i)) {
//            pinMode(i, INPUT_PULLDOWN);
            cowpi_pin_mode(i, INPUT_PULLDOWN);
        }
    }
#endif
    cowpi_output_pins &= ~pins;
    cowpi_floating_input_pins &= ~pins;
    cowpi_pullup_input_pins &= ~pins;
    cowpi_pulldown_input_pins |= pins;
}
#endif //ARDUINO_ARCH_RP2040

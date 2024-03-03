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
    if (cowpi_protocol == SPI) {
        cowpi_left_switch = LEFT_SWITCH_SPI;
        cowpi_right_switch = RIGHT_SWITCH_SPI;
        cowpi_data_pin = DATA_SPI;
        cowpi_clock_pin = CLOCK_SPI;
        cowpi_latch_pin = CHIP_SELECT_SPI;
    } else if (cowpi_protocol == I2C) {
        cowpi_left_switch = LEFT_SWITCH_I2C;
        cowpi_right_switch = RIGHT_SWITCH_I2C;
        cowpi_data_pin = DATA_I2C;
        cowpi_clock_pin = CLOCK_I2C;
    } else {}
    /* unused pins on UnoNano and Mega form factors */
    cowpi_pin_mode(2, INPUT);
    cowpi_pin_mode(3, INPUT);
    /* LEDs */
    cowpi_pin_mode(LEFT_LED, OUTPUT);
    cowpi_pin_mode(RIGHT_LED, OUTPUT);
    cowpi_pin_mode(INTERNAL_LED, OUTPUT);               // just in case it's not the same as LEFT_LED
    /* switches and buttons */
    cowpi_pin_mode(LEFT_BUTTON, INPUT_PULLUP);
    cowpi_pin_mode(RIGHT_BUTTON, INPUT_PULLUP);
    if (cowpi_protocol != NO_PROTOCOL) {
        cowpi_pin_mode(cowpi_left_switch, INPUT_PULLUP);
        cowpi_pin_mode(cowpi_right_switch, INPUT_PULLUP);
    } else {
        // we don't know which pins are used for the switches, so we'll prep both possibilities
        cowpi_pin_mode(LEFT_SWITCH_SPI, INPUT_PULLUP);
        cowpi_pin_mode(LEFT_SWITCH_I2C, INPUT_PULLUP);
        cowpi_pin_mode(RIGHT_SWITCH_SPI, INPUT_PULLUP);
        cowpi_pin_mode(RIGHT_SWITCH_I2C, INPUT_PULLUP);
    }
    /* keypad */
    cowpi_pin_mode(KEYPAD_ROW_1, OUTPUT);
    cowpi_pin_mode(KEYPAD_ROW_4, OUTPUT);
    cowpi_pin_mode(KEYPAD_ROW_7, OUTPUT);
    cowpi_pin_mode(KEYPAD_ROW_STAR, OUTPUT);
    cowpi_pin_mode(KEYPAD_COLUMN_1, INPUT_PULLUP);
    cowpi_pin_mode(KEYPAD_COLUMN_2, INPUT_PULLUP);
    cowpi_pin_mode(KEYPAD_COLUMN_3, INPUT_PULLUP);
    cowpi_pin_mode(KEYPAD_COLUMN_A, INPUT_PULLUP);
    /* display module */
    if (cowpi_protocol == SPI) {
        cowpi_pin_mode(cowpi_data_pin, OUTPUT);
        cowpi_pin_mode(cowpi_clock_pin, OUTPUT);
        cowpi_pin_mode(cowpi_latch_pin, OUTPUT);
        digitalWrite(cowpi_data_pin, LOW);
        digitalWrite(cowpi_clock_pin, LOW);
        digitalWrite(cowpi_latch_pin, HIGH);
    } else if (cowpi_protocol == I2C) {
        cowpi_pin_mode(cowpi_data_pin, INPUT);
        cowpi_pin_mode(cowpi_clock_pin, INPUT);
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

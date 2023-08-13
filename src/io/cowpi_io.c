/**************************************************************************//**
 *
 * @file cowpi_io.c
 *
 * @brief @copybrief cowpi_io.h
 *
 * @details @copydetails cowpi_io.h
 *
 ******************************************************************************/

/* CowPi (c) 2021-23 Christopher A. Bohn
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
#include "cowpi_io.h"
#include "../internal/cowpi_internal.h"


enum protocols cowpi_protocol = NO_PROTOCOL;
uint8_t cowpi_left_switch = 255;
uint8_t cowpi_right_switch = 255;
uint8_t cowpi_clock_pin = 255;
uint8_t cowpi_data_pin = 255;
uint8_t cowpi_latch_pin = 255;


#if defined (ARDUINO_AVR_UNO) || defined (ARDUINO_AVR_NANO)
#define A_BASE  (4)
#define B_BASE  (14)
#elif defined (ARDUINO_AVR_MEGA2560)
#define A_BASE  (4)
#define B_BASE  (54)
#elif defined (ARDUINO_RASPBERRY_PI_PICO) || defined (PICO_RP2040)
#define A_BASE  (6)
#define B_BASE  (10)
#else
#define A_BASE  (0)
#define B_BASE  (0)
#endif //MICROCONTROLLER BOARD

char cowpi_get_keypress(void) {
    // this function is intentionally unreadable
    int8_t a = 0;
    int8_t b = 0;
    uint16_t c;
    char d = '\0';
    e:
    digitalWrite(A_BASE + 0, a == 0 ? LOW : HIGH);
    digitalWrite(A_BASE + 1, a == 1 ? LOW : HIGH);
    digitalWrite(A_BASE + 2, a == 2 ? LOW : HIGH);
    digitalWrite(A_BASE + 3, a == 3 ? LOW : HIGH);
    switch (c = !digitalRead(B_BASE + b) * (b + 256 * a + 1024)) {
        case 00000: if ((a = (int8_t) ((a + 1) & 0x3)) || (++b < 4)) goto e;   else break;
        case 02000: case 02001: case 02002:             d = (char)(    c - 001717); break;
        case 02400: case 02401: case 02402:             d = (char)(    c - 002314); break;
        case 03000: case 03001: case 03002:             d = (char)(    c - 002711); break;
        case 02003: case 02403: case 03003: case 03403: d = (char)(    a + 000101); break;
        case 03400: case 03401:                         d = (char)(6 * c - 024726); break;
        case 03402:                                     d =                0000043; break;
        default:                                        d =                0000130; break;
    }
    digitalWrite(A_BASE + 0, LOW);
    digitalWrite(A_BASE + 1, LOW);
    digitalWrite(A_BASE + 2, LOW);
    digitalWrite(A_BASE + 3, LOW);
    return d;
}

uint16_t cowpi_get_keypresses(void) {
    // this function is intentionally unreadable
    int8_t a = 0;
    int8_t b = 0;
    uint16_t c;
    uint16_t d = 0;
    e:
    for (int8_t f = 0; f < 4; f++) digitalWrite(A_BASE + f, a == f ? LOW : HIGH);
    switch (c = !digitalRead(B_BASE + b) * (b + 256 * a + 1024)) {
        case 00000: if ((a = (int8_t) ((a + 1) & 0x3)) || (++b < 4))                  goto e; else break;
        case 02000: case 02001: case 02002: d |= 1 <<       (c - 001777); a++;        goto e;
        case 02400: case 02401: case 02402: d |= 1 <<       (c - 002374); a++;        goto e;
        case 03000: case 03001: case 03002: d |= 1 <<       (c - 002771); a++;        goto e;
        case 02003: case 02403: case 03003: d |= 1 <<       (a + 000012); a++;        goto e;
        case 03403:                         d |= 1 <<       (a + 000012);                          break;
        case 03400: case 03402:             d |= 1 << (01617 - (c >> 1)); a = 0; b++; goto e;
        case 03401:                         d |=                 0000001; a = 0; b++; goto e;
        default:                            d  =                 0177777;                          break;
    }
    for (int8_t f = 0; f < 4; f++) digitalWrite(A_BASE + f, LOW);
    return d;
}

bool cowpi_left_button_is_pressed(void) {
    return !digitalRead(LEFT_BUTTON);
}

bool cowpi_right_button_is_pressed(void) {
    return !digitalRead(RIGHT_BUTTON);
}

bool cowpi_left_switch_is_in_left_position(void) {
    if (cowpi_protocol != NO_PROTOCOL) {
        return !digitalRead(cowpi_left_switch);
    } else {
        // if either possible switch position is 0, then (a) that must be where the switch is, and (b) it's to the left
        return !(digitalRead(LEFT_SWITCH_SPI) && digitalRead(LEFT_SWITCH_I2C));
    }
}

bool cowpi_right_switch_is_in_left_position(void) {
    if (cowpi_protocol != NO_PROTOCOL) {
        return !digitalRead(cowpi_right_switch);
    } else {
        // if either possible switch position is 0, then (a) that must be where the switch is, and (b) it's to the left
        return !(digitalRead(RIGHT_SWITCH_SPI) && digitalRead(RIGHT_SWITCH_I2C));
    }
}

bool cowpi_left_switch_is_in_right_position(void) {
    if (cowpi_protocol != NO_PROTOCOL) {
        return digitalRead(cowpi_left_switch);
    } else {
        // if both possible switch positions are 1, then it's to the right, regardless of which pin is being used
        return (digitalRead(LEFT_SWITCH_SPI) && digitalRead(LEFT_SWITCH_I2C));
    }
}

bool cowpi_right_switch_is_in_right_position(void) {
    if (cowpi_protocol != NO_PROTOCOL) {
        return digitalRead(cowpi_right_switch);
    } else {
        // if both possible switch positions are 1, then it's to the right, regardless of which pin is being used
        return (digitalRead(RIGHT_SWITCH_SPI) && digitalRead(RIGHT_SWITCH_I2C));
    }
}

void cowpi_illuminate_right_led(void) {
    digitalWrite(RIGHT_LED, HIGH);
}

void cowpi_illuminate_left_led(void) {
    digitalWrite(LEFT_LED, HIGH);
}

void cowpi_deluminate_right_led(void) {
    digitalWrite(RIGHT_LED, LOW);
}

void cowpi_deluminate_left_led(void) {
    digitalWrite(LEFT_LED, LOW);
}

void cowpi_illuminate_internal_led(void) {
    digitalWrite(LED_BUILTIN, HIGH);
}

void cowpi_deluminate_internal_led(void) {
    digitalWrite(LED_BUILTIN, LOW);
}

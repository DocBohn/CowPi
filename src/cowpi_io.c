/**************************************************************************//**
 *
 * @file cowpi_io.c
 *
 * @brief @copybrief cowpi_io.h
 *
 * @details @copydetails cowpi_io.h
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
#include "cowpi_io.h"
#include "cowpi_internal.h"


static bool cowpi_pin_is_output(uint8_t pin);
static bool cowpi_switch_is_in_left_position(uint8_t default_pin, uint8_t alternate_pin);
static bool cowpi_switch_is_in_right_position(uint8_t default_pin, uint8_t alternate_pin);

char cowpi_get_keypress(void) {
    // returns character corresponding to that on a 4x4 matrix keypad's face (0-9, A-D, *, #)
    // this function is intentionally unreadable
    // (it also won't work right on Mega 2560, but we can fix that)
    int8_t a = 0;
    int8_t b = 14;
    uint16_t c;
    char d = '\0';
    e:
    digitalWrite(4, a == 0 ? LOW : HIGH);
    digitalWrite(5, a == 1 ? LOW : HIGH);
    digitalWrite(6, a == 2 ? LOW : HIGH);
    digitalWrite(7, a == 3 ? LOW : HIGH);
    switch (c = !digitalRead(b) * (b + 256 * a + 1024)) {
        case 00000:     if ((a = (int8_t) ((a + 1) & 0x3)) || (++b < 18)) goto e;  else break;
        case 02016: case 02017: case 02020:                 d = (char)(    c - 001735); break;
        case 02416: case 02417: case 02420:                 d = (char)(    c - 002332); break;
        case 03016: case 03017: case 03020:                 d = (char)(    c - 002727); break;
        case 02021: case 02421: case 03021: case 03421:     d = (char)(    a + 000101); break;
        case 03416: case 03417:                             d = (char)(6 * c - 025052); break;
        case 03420:                                         d =                 000043; break;
        default:                                            d =                 000130; break;
    }
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    return d;
}

bool cowpi_left_button_is_pressed(void) {
    return !digitalRead(LEFT_BUTTON);
}

bool cowpi_right_button_is_pressed(void) {
    return !digitalRead(RIGHT_BUTTON);
}

bool cowpi_left_switch_is_in_left_position(void) {
    return cowpi_switch_is_in_left_position(LEFT_SWITCH_DEFAULT, LEFT_SWITCH_ALTERNATE);
}

bool cowpi_right_switch_is_in_left_position(void) {
    return cowpi_switch_is_in_left_position(RIGHT_SWITCH_DEFAULT, RIGHT_SWITCH_ALTERNATE);
}

bool cowpi_left_switch_is_in_right_position(void) {
    return cowpi_switch_is_in_right_position(LEFT_SWITCH_DEFAULT, LEFT_SWITCH_ALTERNATE);
}

bool cowpi_right_switch_is_in_right_position(void) {
    return cowpi_switch_is_in_right_position(RIGHT_SWITCH_DEFAULT, RIGHT_SWITCH_ALTERNATE);
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

void cowpi_illuminate_external_led(void) {
    digitalWrite(LED_EXTERNAL, HIGH);
}

void cowpi_illuminate_internal_led(void) {
    digitalWrite(LED_BUILTIN, HIGH);
}

void cowpi_deluminate_external_led(void) {
    digitalWrite(LED_EXTERNAL, LOW);
}

void cowpi_deluminate_internal_led(void) {
    digitalWrite(LED_BUILTIN, LOW);
}

static inline bool cowpi_pin_is_output(uint8_t pin) {
    return *portModeRegister(digitalPinToPort(pin)) & digitalPinToBitMask(pin);
}

static bool cowpi_switch_is_in_left_position(uint8_t default_pin, uint8_t alternate_pin) {
    if (!cowpi_pin_is_output(default_pin)) {            // if default isn't used for I2C then it's used for the switch
        return !digitalRead(default_pin);
    } else if (!cowpi_pin_is_output(alternate_pin)) {   // not using default but make sure alternate not used for SPI
        return !digitalRead(alternate_pin);
    } else {                                            // if both SPI and I2C are in use then there isn't a switch here
        return false;
    }
}

static bool cowpi_switch_is_in_right_position(uint8_t default_pin, uint8_t alternate_pin) {
    if (!cowpi_pin_is_output(default_pin)) {            // if default isn't used for I2C then it's used for the switch
        return digitalRead(default_pin);
    } else if (!cowpi_pin_is_output(alternate_pin)) {   // not using default but make sure alternate not used for SPI
        return digitalRead(alternate_pin);
    } else {                                            // if both SPI and I2C are in use then there isn't a switch here
        return false;
    }
}

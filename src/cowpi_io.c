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
#include "cowpi_internal.h"


static bool cowpi_pin_is_output(uint8_t pin);
static bool cowpi_switch_is_in_left_position(uint8_t default_pin, uint8_t alternate_pin);
static bool cowpi_switch_is_in_right_position(uint8_t default_pin, uint8_t alternate_pin);


#if defined ARDUINO_AVR_UNO || defined ARDUINO_AVR_NANO
#define A_BASE  (4)
#define B_BASE  (14)
#elif defined ARDUINO_AVR_MEGA2560
#define A_BASE  (4)
#define B_BASE  (54)
#endif //MICROCONTROLLER BOARD

char cowpi_get_keypress(void) {
    // returns character corresponding to that on a 4x4 matrix keypad's face (0-9, A-D, *, #)
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
        case 00000:     if ((a = (int8_t) ((a + 1) & 0x3)) || (++b < 4)) goto e;  else break;
        case 02000: case 02001: case 02002:                 d = (char)(    c - 001717); break;
        case 02400: case 02401: case 02402:                 d = (char)(    c - 002314); break;
        case 03000: case 03001: case 03002:                 d = (char)(    c - 002711); break;
        case 02003: case 02403: case 03003: case 03403:     d = (char)(    a + 000101); break;
        case 03400: case 03401:                             d = (char)(6 * c - 024726); break;
        case 03402:                                         d =                 000043; break;
        default:                                            d =                 000130; break;
    }
    digitalWrite(A_BASE + 0, LOW);
    digitalWrite(A_BASE + 1, LOW);
    digitalWrite(A_BASE + 2, LOW);
    digitalWrite(A_BASE + 3, LOW);
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

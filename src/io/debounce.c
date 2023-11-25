/**************************************************************************//**
 *
 * @file cowpi_io.c
 *
 * @brief @copybrief debounce.h
 *
 * @details @copydetails debounce.h
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
#include "debounce.h"


#define DEBOUNCE_THRESHOLD (20L)


uint8_t cowpi_debounce_byte(uint8_t current_value, enum input_names input_name) {
    static uint8_t last_actual_value[NUMBER_OF_INPUTS] = {0};
    static uint8_t last_good_value[NUMBER_OF_INPUTS] = {0};
    static unsigned long last_change[NUMBER_OF_INPUTS] = {[0 ... (NUMBER_OF_INPUTS - 1)] = 0x80000000}; // gcc extension
    unsigned long now = millis();
    /*
    // responds immediately and then ignores further changes until input stabilizes -- more responsive
    last_good_value[input_name] = (now - last_change[input_name] < DEBOUNCE_THRESHOLD) ? last_good_value[input_name]
                                                                                       : current_value;
    last_change[input_name] = (current_value == last_actual_value[input_name]) ? last_change[input_name] : now;
    */ /* ...OR... */ /*
    // ignores changes until input stabilizes and then responds -- more immune to transients -- but requires continuous polling
    last_change[input_name] = (current_value == last_actual_value[input_name]) ? last_change[input_name] : now;
    last_good_value[input_name] = (now - last_change[input_name] < DEBOUNCE_THRESHOLD) ? last_good_value[input_name]
                                                                                       : current_value;
    last_actual_value[input_name] = current_value;
    */ /* ...OR... */
    // ignores changes until stabilization, but honors Nyquist rate (if we don't sample at least every 10ms then we don't know whether the input has been stable for 20ms)
    static unsigned long last_call[NUMBER_OF_INPUTS] = {[0 ... (NUMBER_OF_INPUTS - 1)] = 0x80000000}; // gcc extension
    last_change[input_name] = (current_value == last_actual_value[input_name]) ? last_change[input_name] : now;
    last_good_value[input_name] = (now - last_call[input_name] < DEBOUNCE_THRESHOLD / 2) &&
                                  (now - last_change[input_name] < DEBOUNCE_THRESHOLD)
                                  ? last_good_value[input_name]
                                  : current_value;
    last_actual_value[input_name] = current_value;
    last_call[input_name] = now;

    return last_good_value[input_name];
}


uint16_t cowpi_debounce_short(uint16_t current_value, enum input_names input_name) {
    static uint16_t last_actual_value[NUMBER_OF_INPUTS] = {0};
    static uint16_t last_good_value[NUMBER_OF_INPUTS] = {0};
    static unsigned long last_change[NUMBER_OF_INPUTS] = {[0 ... (NUMBER_OF_INPUTS - 1)] = 0x80000000}; // gcc extension
    static unsigned long last_call[NUMBER_OF_INPUTS] = {[0 ... (NUMBER_OF_INPUTS - 1)] = 0x80000000}; // gcc extension
    unsigned long now = millis();
    last_change[input_name] = (current_value == last_actual_value[input_name]) ? last_change[input_name] : now;
    last_good_value[input_name] = (now - last_call[input_name] < DEBOUNCE_THRESHOLD / 2) &&
                                  (now - last_change[input_name] < DEBOUNCE_THRESHOLD)
                                  ? last_good_value[input_name]
                                  : current_value;
    last_actual_value[input_name] = current_value;
    last_call[input_name] = now;
    return last_good_value[input_name];
}


uint32_t cowpi_debounce_long(uint32_t current_value, enum input_names input_name) {
    static uint32_t last_actual_value[NUMBER_OF_INPUTS] = {0};
    static uint32_t last_good_value[NUMBER_OF_INPUTS] = {0};
    static unsigned long last_change[NUMBER_OF_INPUTS] = {[0 ... (NUMBER_OF_INPUTS - 1)] = 0x80000000}; // gcc extension
    static unsigned long last_call[NUMBER_OF_INPUTS] = {[0 ... (NUMBER_OF_INPUTS - 1)] = 0x80000000}; // gcc extension
    unsigned long now = millis();
    last_change[input_name] = (current_value == last_actual_value[input_name]) ? last_change[input_name] : now;
    last_good_value[input_name] = (now - last_call[input_name] < DEBOUNCE_THRESHOLD / 2) &&
                                  (now - last_change[input_name] < DEBOUNCE_THRESHOLD)
                                  ? last_good_value[input_name]
                                  : current_value;
    last_actual_value[input_name] = current_value;
    last_call[input_name] = now;
    return last_good_value[input_name];
}

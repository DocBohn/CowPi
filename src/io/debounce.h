/**************************************************************************//**
 *
 * @file debounce.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Defines the functions that provide software debouncing of mechanical
 * input devices such as tactile switches, membrane switches, and slide
 * switches.
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

#ifndef COWPI_DEBOUNCE_H
#define COWPI_DEBOUNCE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Identifiers to uniquely describe inputs being debounced.
 *
 * Most of the provided identifiers correspond to the likely inputs that would
 * be polled on a Cow Pi board. Two additional identifiers (`INPUT_X` and
 * `INPUT_Y`) are available for mechanical input devices that expand a Cow Pi
 * board.
 */
enum input_names {
    LEFT_BUTTON_DOWN = 0,
    RIGHT_BUTTON_DOWN,
    LEFT_SWITCH_LEFT,
    RIGHT_SWITCH_LEFT,
    LEFT_SWITCH_RIGHT,
    RIGHT_SWITCH_RIGHT,
    KEYPAD,
    INPUT_X,
    INPUT_Y,
    NUMBER_OF_INPUTS
};

/**
 * @brief Applies a software-based low-pass filter to an input, smoothing-out
 * mechanical switch bounce.
 *
 * When the input is stable, this function will return the input's value. When
 * the input is bouncing, this function will return a stable value.
 *
 * The first argument is an expression that you would use to determine the
 * input's value if switch bounce weren't an issue. This might be one of the
 * CowPi library's functions, it might be memory-mapped I/O, or it might be some
 * other expression altogether.
 *
 * Because this function cannot ascertain which input is being debounced (the
 * expression that provides the `current-value` is evaluated before this
 * function starts), you must provide additional information, in the form of
 * the `input_name` argument. Most of the `input_names` correspond to the likely
 * inputs that would be polled on a Cow Pi board. Providing a unique
 * `input_name` allows the library to stabilize multiple bouncing inputs, such
 * as the user pressing both pushbuttons simultaneously.
 *
 * This function is suitable for inputs that can be represented in eight (or
 * fewer) bits.
 *
 * @sa cowpi_debounce_short
 *
 * @param current_value an expression that evaluates to the input's current,
 *      un-debounced value
 * @param input_name a unique enumerated value to distinguish between different
 *      inputs
 * @return the input's value after mechanical bouncing has been filtered-out
 */
uint8_t cowpi_debounce_byte(uint8_t current_value, enum input_names input_name);

/**
 * @brief Applies a software-based low-pass filter to an input, smoothing-out
 * mechanical switch bounce.
 *
 * When the input is stable, this function will return the input's value. When
 * the input is bouncing, this function will return a stable value.
 *
 * The first argument is an expression that you would use to determine the
 * input's value if switch bounce weren't an issue. This might be one of the
 * CowPi library's functions, it might be memory-mapped I/O, or it might be some
 * other expression altogether.
 *
 * Because this function cannot ascertain which input is being debounced (the
 * expression that provides the `current-value` is evaluated before this
 * function starts), you must provide additional information, in the form of
 * the `input_name` argument. Most of the `input_names` correspond to the likely
 * inputs that would be polled on a Cow Pi board. Providing a unique
 * `input_name` allows the library to stabilize multiple bouncing inputs, such
 * as the user pressing both pushbuttons simultaneously.
 *
 * This function is suitable for inputs that can be represented in sixteen (or
 * fewer) bits.
 *
 * @sa cowpi_debounce_byte
 *
 * @param current_value an expression that evaluates to the input's current,
 *      un-debounced value
 * @param input_name a unique enumerated value to distinguish between different
 *      inputs
 * @return the input's value after mechanical bouncing has been filtered-out
 */
uint16_t cowpi_debounce_short(uint16_t current_value, enum input_names input_name);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_DEBOUNCE_H

/**************************************************************************//**
 *
 * @file cowpi_io.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Defines the functions to query inputs and set outputs that can readily
 * be accessed from the general-purpose I/O pins.
 *
 * Re-implementing these functions (using different function names) is a
 * typical part of a memory-mapped I/O lab assignment.
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

#ifndef COWPI_IO_H
#define COWPI_IO_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Scans the keypad to determine which, if any, key was pressed.
 *
 * There is no debouncing. This is a portable implementation, not a 
 * memory-mapped implementation. Returns the ASCII representation of the 
 * character depicted on whichever key was pressed (0-9, A-D, *, #).
 *
 * Assumes a common 4x4 matrix keypad with the rows in Arduino pins D4-D7 and
 * the columns in Arduino pins A0-A3 (D14-D17 on Uno/Nano). A pressed key 
 * grounds a pulled-high input.
 * 
 * @sa cowpi_get_keypresses
 *
 * @return ASCII character corresponding to the key that is pressed, or NUL if
 * no key is pressed
 */
char cowpi_get_keypress(void);

/**
 * @brief Scans the keypad to determine which keys have been pressed.
 *
 * There is no debouncing. This is a portable implementation, not a 
 * memory-mapped implementation.
 * 
 * Returns a bit vector with a 1 (key pressed) or 0 (key not pressed) in each
 * of 16 bits that correspond to the 16 keys. For keys with hexadecimal digits, 
 * the digit indicates the corresponding bit (bit0 corresponds to the "0" key; 
 * bit1 corresponds to the "1" key; ...; and bit13 corresponds to the "D" key). 
 * Additionally, bit14 corresponds to the "#" key and bit15 corresponds to the 
 * "*" key.
 *
 * Assumes a common 4x4 matrix keypad with the rows in Arduino pins D4-D7 and
 * the columns in Arduino pins A0-A3 (D14-D17 on Uno/Nano). A pressed key 
 * grounds a pulled-high input.
 * 
 * @warning This function should only be called if diodes are used to isolate 
 * the keys, as on the Cow Pi mark 3 and mark 4 development boards.
 * 
 * @sa cowpi_get_keypress
 * 
 * @return bit vector that indicates which keys are pressed and which are not
 *      pressed
 */
uint16_t cowpi_get_keypresses(void);

/**
 * @brief Reports whether the left button is pressed.
 *
 * There is no debouncing. This is a portable implementation, not a
 * memory-mapped implementation.
 *
 * Assumes the left button is in Arduino pin D8. A pressed button grounds a
 * pulled-high input.
 *
 * @return `true` if the button is pressed, `false` otherwise
 */
bool cowpi_left_button_is_pressed(void);

/**
 * @brief Reports whether the right button is pressed.
 *
 * There is no debouncing. This is a portable implementation, not a
 * memory-mapped implementation.
 *
 * Assumes the right button is in Arduino pin D9. A pressed button grounds a
 * pulled-high input.
 *
 * @return `true` if the button is pressed, `false` otherwise
 */
bool cowpi_right_button_is_pressed(void);

/**
 * @brief Reports whether the left switch is in the left position.
 *
 * There is no debouncing. This is a portable implementation, not a
 * memory-mapped implementation.
 *
 * Assumes the left switch is in Arduino pin A4 (D18) if SPI (but not I2C) is
 * in use or if no protocol is in use; assumes the switch is in pin D11 if I2C
 * (but not SPI) is in use. If both protocols are in use, then this function
 * will always return `false`. A switch in the left position grounds a
 * pulled-high input.
 *
 * @return `true` if the switch is in the left position, `false` otherwise
 */
bool cowpi_left_switch_is_in_left_position(void);

/**
 * @brief Reports whether the right switch is in the left position.
 *
 * There is no debouncing. This is a portable implementation, not a
 * memory-mapped implementation.
 *
 * Assumes the right switch is in Arduino pin A5 (D19) if SPI (but not I2C) is
 * in use or if no protocol is in use; assumes the switch is in pin D10 if I2C
 * (but not SPI) is in use. If both protocols are in use, then this function
 * will always return `false`. A switch in the left position grounds a
 * pulled-high input.
 *
 * @return `true` if the switch is in the left position, `false` otherwise
 */
bool cowpi_right_switch_is_in_left_position(void);

/**
 * @brief Reports whether the left switch is in the right position.
 *
 * There is no debouncing. This is a portable implementation, not a
 * memory-mapped implementation.
 *
 * Assumes the left switch is in Arduino pin A4 (D18) if SPI (but not I2C) is
 * in use or if no protocol is in use; assumes the switch is in pin D11 if I2C
 * (but not SPI) is in use. If both protocols are in use, then this function
 * will always return `false`. A switch in the right position floats, allowing
 * pulled-high input to remain high.
 *
 * @return `true` if the switch is in the right position, `false` otherwise
 */
bool cowpi_left_switch_is_in_right_position(void);

/**
 * @brief Reports whether the right switch is in the right position.
 *
 * There is no debouncing. This is a portable implementation, not a
 * memory-mapped implementation.
 *
 * Assumes the right switch is in Arduino pin A5 (D19) if SPI (but not I2C) is
 * in use or if no protocol is in use; assumes the switch is in pin D10 if I2C
 * (but not SPI) is in use. If both protocols are in use, then this function
 * will always return `false`. A switch in the right position floats, allowing
 * pulled-high input to remain high.
 *
 * @return `true` if the switch is in the right position, `false` otherwise
 */
bool cowpi_right_switch_is_in_right_position(void);

/**
 * @brief Illuminates the right LED, aka the external LED.
 *
 * This is a portable implementation, not a memory-mapped implementation.
 *
 * Assumes the external LED is in Arduino pin D12. An LED illuminates when the
 * pin is placed high, to match the semantics of Arduino's built-in LED.
 */
void cowpi_illuminate_right_led(void);

/**
 * @brief Illuminates the left LED, aka the built-in LED, aka the internal LED.
 *
 * This is a portable implementation, not a memory-mapped implementation.
 *
 * Assumes the internal LED is in Arduino pin D13. The Arduino semantics are
 * that an LED illuminates when the pin is placed high.
 */
void cowpi_illuminate_left_led(void);

/**
 * @brief Deluminates the right LED, aka the external LED.
 *
 * This is a portable implementation, not a memory-mapped implementation.
 *
 * Assumes the external LED is in Arduino pin D12. An LED deluminates when the
 * pin is placed low, to match the semantics of Arduino's built-in LED.
 */
void cowpi_deluminate_right_led(void);

/**
 * @brief Deluminates the left LED, aka the built-in LED, aka the internal LED.
 *
 * This is a portable implementation, not a memory-mapped implementation.
 *
 * Assumes the internal LED is in Arduino pin D13. The Arduino semantics are
 * that an LED deluminates when the pin is placed low.
 */
void cowpi_deluminate_left_led(void);

/**
 * @brief Illuminates the internal LED, aka the built-in LED, aka the left LED.
 *
 * This is a portable implementation, not a memory-mapped implementation.
 *
 * Assumes the internal LED is in Arduino pin D13. The Arduino semantics are
 * that an LED illuminates when the pin is placed high.
 */
void cowpi_illuminate_internal_led(void);

/**
 * @brief Deluminates the internal LED, aka the built-in LED, aka the left LED.
 *
 * This is a portable implementation, not a memory-mapped implementation.
 *
 * Assumes the internal LED is in Arduino pin D13. The Arduino semantics are
 * that an LED deluminates when the pin is placed low.
 */
void cowpi_deluminate_internal_led(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_IO_H

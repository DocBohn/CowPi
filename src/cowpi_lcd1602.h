/**************************************************************************//**
 *
 * @file cowpi_lcd1602.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Utility functions for 2-row/16-column display modules with 5x8 LCD
 *      characters.
 *
 * If `LCD1602` is part of the argument to `cowpi_setup()`, then the display
 * module will be placed in 4-bit mode, and:
 * - With each character, increment the cursor's location but do not shift the
 *   display
 * - Turn the display on, the cursor off, and no blinking
 * - Clear the display
 *
 * The LCD1602 is complex enough that the firmware program should call
 * `cowpi_lcd1602_send_command()`, `cowpi_lcd1602_send_character()`, or another
 * more-specific function. These functions will take care of dividing the data
 * into halfbytes, managing timing, and other complexities, and will call
 * `cowpi_lcd1602_send_halfbyte()`.
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

#ifndef COWPI_LCD1602_H
#define COWPI_LCD1602_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup display
 *  @{
 */

/**
 * @brief Pointer to function that sends a halfbyte to the LCD1602 display.
 *
 * The `cowpi_lcd1602` utility functions all make use of the
 * `cowpi_lcd1602_send_halfbyte()` function pointer.
 *
 * Initially, `cowpi_lcd1602_send_halfbyte()` is one of two default
 * implementations, depending on the protocol specified in the argument to
 * `cowpi_setup()`. The SPI implementation is a portable software-only
 * implementation that does not use SPI hardware, nor does it use memory-mapped
 * I/O of any form. The I2C implementation currently makes use of the I2C
 * hardware using avr-libc macros.
 *
 * @todo Finish implementing portable software-only I2C implementation.
 *
 * Re-implementing this function to use SPI or I2C hardware is a possible
 * part of a memory-mapped I/O lab assignment.
 *
 * SPI: Assumes the display module's data-in line is connected to the
 * microcontroller's COPI pin (D11 on most Arduino boards), the display module's
 * serial-clock line is connected to the microcontroller's SCK pin (D13 on most
 * Arduino boards), and the display module's chip-select line is connected to
 * Arduino pin D10.
 *
 * I2C: Assumes the display module's data line is connected to the
 * microcontroller's SDA pin (D18 on most Arduino boards) and the display
 * module's serial-clock line is connected to the microcontroller's SCL pin (D19
 * on most Arduino boards).
 *
 * @sa cowpi_lcd1602_set_send_halfbyte_function
 *
 * @param halfbyte the data to be sent to the display module
 * @param is_command indicates whether the data is part of a command (`true`)
 *      or part of a character (`false`)
 */
typedef void (*cowpi_lcd1602_send_halfbyte_t)(uint8_t halfbyte, bool is_command);

/**
 * @brief Reassigns the `cowpi_lcd1602_send_halfbyte` function pointer to point
 *      to the specified function.
 *
 * During setup, this function is used to assign one of the two default
 * `cowpi_lcd1602_send_halfbyte_t` implementations to
 * `cowpi_lcd1602_send_halfbyte`, unless it was previously used to assign a
 * re-implementation. I can also later be used to assign a re-implementation.
 *
 * @param send_halfbyte_function the function to be used to send halfbytes to
 *      the LCD1602 display module
 */
void cowpi_lcd1602_set_send_halfbyte_function(cowpi_lcd1602_send_halfbyte_t send_halfbyte_function);

/**
 * @brief Places the specified character on the display at the specified
 * location.
 *
 * The character is an ASCII or "extended-ASCII" character, or a custom
 * character created by using `cowpi_lcd1602_create_character()`.
 *
 * Note that the base address of the top row is 0x00, and the base address of
 * the bottom row is 0x40.
 *
 * @param address the address of the desired location
 * @param character the character to be displayed
 */
void cowpi_lcd1602_place_character(uint8_t address, uint8_t character);

/**
 * @brief Places the cursor at the specified location without updating the
 * display.

 * While the cursor will move to the specified location, it will only be visibly
 * there if the cursor is on.
 *
 * Note that the base address of the top row is 0x00, and the base address of
 * the bottom row is 0x40.
 *
 * @param address the address of the desired location
 */
void cowpi_lcd1602_place_cursor(uint8_t address);

/**
 * @brief Sends a command to the LCD1602 display module
 *
 * The command is a bitwise disjunction of named constants to specify the
 * entry mode (cursor and text movement to occur after characters are sent), a
 * disjunction of named constants to specify the display mode (whether the
 * display is on, whether the underscore cursor is displayed, and whether the
 * cursor's location blinks), or one shift command (shift display left/right or
 * shift cursor left/right).
 *
 * @param command
 */
void cowpi_lcd1602_send_command(uint8_t command);

/**
 * @brief Displays a character at the cursor's location on the LCD1602 display
 *      module.
 *
 * The character is an ASCII or "extended-ASCII" character, or one of the eight
 * custom characters created by using `cowpi_lcd1602_create_character()`.
 *
 * @param character the character to be displayed
 */
void cowpi_lcd1602_send_character(uint8_t character);

/**
 * @brief Creates a custom character for the LCD1602 display module.
 *
 * The encoding can be a value between 0 and 7, inclusive. Each element of the
 * pixel vector corresponds to a row of the 5x8 character matrix (thus, only
 * 5 bits of each element are used).
 *
 * @param encoding the value used to represent the character
 * @param pixel_vector identifies which LCDs are "on" or "off" for the custom
 *      character.
 */
void cowpi_lcd1602_create_character(uint8_t encoding, const uint8_t pixel_vector[8]);

/**
 * @brief Clears the display and places the cursor in row 0, column 0.
 */
void cowpi_lcd1602_clear_display();

/**
 * @brief Places the cursor in row 0, column 0.
 *
 * If the display was shifted, the display is shifted back to its original
 * position. The contents of each character position remain unchanged.
 */
void cowpi_lcd1602_return_home();

/**
 * @brief Turns the display module's backlight on or off.
 *
 * @param backlight_on indicates whether the backlight should be on (`true`) or
 *      off (`false`)
 */
void cowpi_lcd1602_set_backlight(bool backlight_on);

/** @} */

#ifdef __cplusplus
} // extern "C"
#endif


/** @addtogroup display
 *  @{
 */

/* Entry Mode Commands */
#define LCDENTRY_CURSORMOVESRIGHT   0x06    //!< Instructs the display module to shift the cursor right after a character is displayed
#define LCDENTRY_CURSORMOVESLEFT    0x04    //!< Instructs the display module to shift the cursor left after a character is displayed
#define LCDENTRY_TEXTSHIFTS         0x05    //!< Instructs the display module to shift the entire display after a character is displayed
#define LCDENTRY_TEXTNOSHIFT        0x04    //!< Instructs the display module not to shift the display after a character is displayed

/* Display On/Off Commands */
#define LCDONOFF_DISPLAYON          0x0C    //!< Instructs the display module to turn on the display
#define LCDONOFF_DISPLAYOFF         0x08    //!< Instructs the display module to turn off the display
#define LCDONOFF_CURSORON           0x0A    //!< Instructs the display module to turn on the underscore cursor
#define LCDONOFF_CURSOROFF          0x08    //!< Instructs the display module to turn off the underscore cursor
#define LCDONOFF_BLINKON            0x09    //!< Instructs the display module to blink the cursor's position
#define LCDONOFF_BLINKOFF           0x08    //!< Instructs the display module not to blink the cursor's position

/* Cursor or Display Shift Commands */
#define LCDSHIFT_DISPLAYLEFT        0x18    //!< Shifts the entire display to the left
#define LCDSHIFT_DISPLAYRIGHT       0x1C    //!< Shifts the entire display to the right
#define LCDSHIFT_CURSORLEFT         0x10    //!< Shifts the cursor to the left
#define LCDSHIFT_CURSORRIGHT        0x14    //!< Shifts the cursor to the right

/** @} */


/** @var cowpi_lcd1602_send_halfbyte_t cowpi_lcd1602_send_halfbyte
 *  @copydoc cowpi_lcd1602_send_halfbyte_t
 *  @ingroup display
 */

#endif //COWPI_LCD1602_H

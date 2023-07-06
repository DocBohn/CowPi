/**************************************************************************//**
 *
 * @file cowpi_internal.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Function and constants that are not meant for use by application code.
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

#ifndef COWPI_INTERNAL_H
#define COWPI_INTERNAL_H

#include <stdint.h>

/** @cond */

/* Constants */

    // buttons
static const uint8_t PUSHBUTTON_NAND        = 2;
static const uint8_t LEFT_BUTTON            = 8;
static const uint8_t RIGHT_BUTTON           = 9;
    // switches
#ifdef ARDUINO_AVR_MEGA2560
static const uint8_t LEFT_SWITCH_DEFAULT    = 58;   // aka A4
static const uint8_t RIGHT_SWITCH_DEFAULT   = 59;   // aka A5
#else
static const uint8_t LEFT_SWITCH_DEFAULT    = 18;   // aka A4
static const uint8_t RIGHT_SWITCH_DEFAULT   = 19;   // aka A5
#endif //ARDUINO_AVR_MEGA2560
static const uint8_t LEFT_SWITCH_ALTERNATE  = 11;
static const uint8_t RIGHT_SWITCH_ALTERNATE = 10;
    // keypad
static const uint8_t KEYPAD_NAND            = 3;
static const uint8_t KEYPAD_ROW_1           = 4;
static const uint8_t KEYPAD_ROW_4           = 5;
static const uint8_t KEYPAD_ROW_7           = 6;
static const uint8_t KEYPAD_ROW_STAR        = 7;
#ifdef ARDUINO_AVR_MEGA2560
static const uint8_t KEYPAD_COLUMN_1        = 54;   // aka A0
static const uint8_t KEYPAD_COLUMN_2        = 55;   // aka A1
static const uint8_t KEYPAD_COLUMN_3        = 56;   // aka A2
static const uint8_t KEYPAD_COLUMN_A        = 57;   // aka A3
#else
static const uint8_t KEYPAD_COLUMN_1        = 14;   // aka A0
static const uint8_t KEYPAD_COLUMN_2        = 15;   // aka A1
static const uint8_t KEYPAD_COLUMN_3        = 16;   // aka A2
static const uint8_t KEYPAD_COLUMN_A        = 17;   // aka A3
#endif //ARDUINO_AVR_MEGA2560
    // LEDs
static const uint8_t LEFT_LED               = 13;
static const uint8_t RIGHT_LED              = 12;
static const uint8_t LED_EXTERNAL           = 12;
// Arduino Defined   LED_BUILTIN            = 13
    // SPI
static const uint8_t SPI_CHIP_SELECT        = 10;
// Arduino Defined   MOSI                   = 11                (D51 on Arduino Mega 2560)
// Arduino Defined   SCK                    = 13                (D52 on Arduino Mega 2560)
    // I2C
// Arduino Defined   SDA                    = 18       aka A4   (D20 on Arduino Mega 2560)
// Arduino Defined   SCL                    = 19       aka A5   (D21 on Arduino Mega 2560)


/* Global variable declarations */

// none


/* Internal-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif
void cowpi_error(const char *message);
void cowpi_setup_max7219(unsigned int configuration);
void cowpi_setup_lcd1602(unsigned int configuration);
#ifdef __cplusplus
} // extern "C"
#endif


/* Macros for internal use only */

// none

/** @endcond */

#endif //COWPI_INTERNAL_H

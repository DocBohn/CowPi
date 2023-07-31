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
#include <CowPi_stdio.h>

#if defined (ARDUINO_AVR_UNO)   || defined (ARDUINO_AVR_NANO)           || defined (ARDUINO_AVR_NANO_EVERY)         \
 || defined (ARDUINO_NANO33BLE) || defined (ARDUINO_SAMD_NANO_33_IOT)   || defined (ARDUINO_NANO_RP2040_CONNECT)
#define COWPI_UNONANO_FORMFACTOR
#endif //COWPI_UNONANO_FORMFACTOR

#if defined (ARDUINO_AVR_MEGA2560)
#define COWPI_MEGA_FORMFACTOR
#endif //COWPI_MEGA_FORMFACTOR

#if defined (ARDUINO_RASPBERRY_PI_PICO) || defined (PICO_RP2040)
#define COWPI_PICO_FORMFACTOR
#endif //COWPI_PICO_FORMFACTOR

/** @cond */

/* Constants */

#if defined (COWPI_UNONANO_FORMFACTOR)
    // LEDs
static const uint8_t LEFT_LED               = 13;
static const uint8_t RIGHT_LED              = 12;
static const uint8_t INTERNAL_LED           = 13;
    // buttons
static const uint8_t LEFT_BUTTON            = 8;
static const uint8_t RIGHT_BUTTON           = 9;
    // switches
static const uint8_t LEFT_SWITCH_SPI        = 18;   // aka A4
static const uint8_t RIGHT_SWITCH_SPI       = 19;   // aka A5
static const uint8_t LEFT_SWITCH_I2C        = 11;
static const uint8_t RIGHT_SWITCH_I2C       = 10;
    // keypad
static const uint8_t KEYPAD_ROW_1           = 4;
static const uint8_t KEYPAD_ROW_4           = 5;
static const uint8_t KEYPAD_ROW_7           = 6;
static const uint8_t KEYPAD_ROW_STAR        = 7;
static const uint8_t KEYPAD_COLUMN_1        = 14;   // aka A0
static const uint8_t KEYPAD_COLUMN_2        = 15;   // aka A1
static const uint8_t KEYPAD_COLUMN_3        = 16;   // aka A2
static const uint8_t KEYPAD_COLUMN_A        = 17;   // aka A3
    // display
static const uint8_t CHIP_SELECT_SPI        = 10;
static const uint8_t DATA_SPI               = 11;
static const uint8_t CLOCK_SPI              = 13;
static const uint8_t DATA_I2C               = 18;   // aka A4
static const uint8_t CLOCK_I2C              = 19;   // aka A5

#elif defined (COWPI_MEGA_FORMFACTOR)

    // LEDs
static const uint8_t LEFT_LED               = 13;
static const uint8_t RIGHT_LED              = 12;
static const uint8_t INTERNAL_LED           = 13;
    // buttons
static const uint8_t LEFT_BUTTON            = 8;
static const uint8_t RIGHT_BUTTON           = 9;
    // switches
static const uint8_t LEFT_SWITCH_SPI        = 58;   // aka A4
static const uint8_t RIGHT_SWITCH_SPI       = 59;   // aka A5
static const uint8_t LEFT_SWITCH_I2C        = 11;
static const uint8_t RIGHT_SWITCH_I2C       = 10;
    // keypad
static const uint8_t KEYPAD_ROW_1           = 4;
static const uint8_t KEYPAD_ROW_4           = 5;
static const uint8_t KEYPAD_ROW_7           = 6;
static const uint8_t KEYPAD_ROW_STAR        = 7;
static const uint8_t KEYPAD_COLUMN_1        = 54;   // aka A0
static const uint8_t KEYPAD_COLUMN_2        = 55;   // aka A1
static const uint8_t KEYPAD_COLUMN_3        = 56;   // aka A2
static const uint8_t KEYPAD_COLUMN_A        = 57;   // aka A3
    // display
static const uint8_t CHIP_SELECT_SPI        = 10;   // TODO ????--not 53--need to fix the CowPi_stdio default
static const uint8_t DATA_SPI               = 51;
static const uint8_t CLOCK_SPI              = 52;
static const uint8_t DATA_I2C               = 20;
static const uint8_t CLOCK_I2C              = 21;

//#elif defined (CCOWPI_PICO_FORMFACTOR)

#else
#error CowPi does not yet support your microcontroller board
#endif //FORMFACTOR


/* Global variable declarations */

extern enum protocols cowpi_protocol;
extern uint8_t cowpi_left_switch;
extern uint8_t cowpi_right_switch;
extern uint8_t cowpi_clock_pin;
extern uint8_t cowpi_data_pin;
extern uint8_t cowpi_latch_pin;


/* Internal-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(ARDUINO_ARCH_AVR)
#define pin_number_t uint8_t
#define pin_mode_t uint8_t
#elif defined(ARDUINO_ARCH_MEGAAVR)
#define pin_number_t uint8_t
#define pin_mode_t PinMode
#elif defined(ARDUINO_ARCH_SAMD)
#define pin_number_t pin_size_t
#define pin_mode_t PinMode
#elif defined (ARDUINO_ARCH_MBED)
#define pin_number_t pin_size_t
#define pin_mode_t PinMode
#endif //ARCHITECTURE

/**
 * @brief Configures the specified pin to behave either as an input or an output
 * and, if as an input, then whether it is high-impedance or uses an internal
 * pullup (or pulldown) resistor.
 *
 * @param pin the pin whose mode is to be set
 * @param mode INPUT, OUTPUT, INPUT_PULLUP, or (if supported) INPUT_PULLDOWN
 */
void cowpi_pin_mode(pin_number_t pin, pin_mode_t mode);

#ifdef __cplusplus
} // extern "C"
#endif


/* Macros for internal use only */

// none

/** @endcond */

#endif //COWPI_INTERNAL_H

/*!
 * @mainpage CowPi Library
 *
 * @version 0.6
 *
 * @copyright (c) 2021-23 Christopher A. Bohn
 *
 * @section overview Overview
 *
 * This library is designed to support the "Cow Pi" hardware kit to teach
 * undergraduate students the concepts of memory-mapped I/O, polling,
 * and interrupts.
 *
 * @section hardware Supported Hardware
 *
 * The current version supports:
 *  - Microcontrollers
 *      - ATMega328P (Arduino Uno, Arduino Nano)
 *  - 4x4 matrix keypad
 *  - Two pushbuttons (aka tactile switches)
 *  - Two slide-switches
 *  - Two or three LEDs
 *  - Through the CowPi_stdio library:
 *      - SPI Displays
 *          - 8x8 LED Matrix driven by MAX7219
 *          - 8-digit 7-segment display driven by MAX7219
 *          - 2-row, 16-column HD44780U-based LCD character display, using 74HC595
 *            as a serial interface
 *      - I2C (aka IIC, TWI) Displays
 *          - 2-row, 16-column HD44780U-based LCD character display, using MCP23008
 *            (such as the Adafruit SPI/I2C backpack) or using PCF8574 (such as in
 *            the myriad (nearly) identical I2C serial interfaces available from
 *            many, many sources)
 *
 * As a practical matter, other displays are also supported (assuming they use
 * SPI or I2C) but there are default implementations only for those listed.
 * Similarly, other inputs/outputs using the GPIO pins are readily used with
 * the memory-mapped I/O data structures defined in the library, the default
 * implementations assume the LEDs, switches, buttons, are attached to specific
 * GPIO pins. While additional microcontrollers will be supported, only those
 * listed above currently have data structures for memory-mapped I/O defined in
 * the library.
 *
 * @section license License
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

/**************************************************************************//**
 *
 * @file CowPi.h
 *
 * @author Christopher A. Bohn
 *
 * @brief This header organizes the other headers.  It is the only header from
 * the CowPi library that application code should `#include`.
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

#ifndef COWPI_H
#define COWPI_H

#include <Arduino.h>
#include <CowPi_stdio.h>
#include "setup/cowpi_setup.h"
#include "boards/boards.h"
#include "interrupts/interrupts.h"
#include "io/cowpi_io.h"
#include "io/debounce.h"

#define COWPI_VERSION ("0.6.0")

#endif //COWPI_H

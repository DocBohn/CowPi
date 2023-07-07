/**************************************************************************//**
 *
 * @file cowpi_boards.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Imports the appropriate microcontroller-specific definitions for the
 * microcontroller board that is in use.
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

#ifndef COWPI_BOARDS_H
#define COWPI_BOARDS_H

#include <stdint.h>

#if defined ARDUINO_AVR_UNO || defined ARDUINO_AVR_NANO
#include "cowpi_atmega328p.h"
#elif defined ARDUINO_AVR_NANO_EVERY
#define COWPI_IO_BASE   ((uint8_t *) 0x0)
#error Arduino Nano Every is not yet supported for CowPi
#elif defined ARDUINO_NANO33BLE
// TODO: double-check whether Nano 33 BLE Sense is a distinct board wrt IDE
#error Arduino Nano 33 BLE is not yet supported for CowPi
#elif defined ARDUINO_SAMD_NANO_33_IOT
#error Arduino Nano 33 IOT is not yet supported for CowPi
#elif defined ARDUINO_NANO_RP2040_CONNECT
#error Arduino Nano RP2040 is not yet supported for CowPi
#elif defined ARDUINO_AVR_MEGA2560
#warning Arduino Mega 2560 is not yet supported for CowPi
#elif defined ARDUINO_RASPBERRY_PI_PICO || defined PICO_RP2040
#error Raspberry Pi Pico is not yet supported for CowPi
#else
#error Your microcontroller board is not yet supported for CowPi.
#endif //MICROCONTROLLER BOARD

#endif //COWPI_BOARDS_H

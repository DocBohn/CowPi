/**************************************************************************//**
 *
 * @file boards.h
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

#include "atmega328p.h"

#ifndef COWPI_USING_A_SUPPORTED_BOARD

#if defined (ARDUINO_AVR_NANO_EVERY)
#warning CowPi does not yet have memory-mapped I/O data structures for Arduino Nano Every

#elif defined (ARDUINO_NANO33BLE)
#warning CowPi does not yet have memory-mapped I/O data structures for Arduino Nano 33 BLE

#elif defined (ARDUINO_SAMD_NANO_33_IOT)
#warning CowPi does not yet have memory-mapped I/O data structures for Arduino Nano 33 IOT

#elif defined (ARDUINO_NANO_RP2040_CONNECT)
#warning CowPi does not yet have memory-mapped I/O data structures for Arduino Nano RP2040

#elif defined (ARDUINO_AVR_MEGA2560)
#warning CowPi does not yet have memory-mapped I/O data structures for Arduino Mega 2560

#elif defined (ARDUINO_RASPBERRY_PI_PICO) || defined (PICO_RP2040)
#warning CowPi does not yet have memory-mapped I/O data structures for Raspberry Pi Pico

// TODO: add the new Uno R4 and Nano ESP32

#else
#error Cowpi does not yet support your microcontroller board
#endif //enumerate known unsupported boards

#endif //COWPI_USING_A_SUPPORTED_BOARD

#endif //COWPI_BOARDS_H

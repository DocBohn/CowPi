/**************************************************************************//**
 *
 * @file cowpi_stdio.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Configures file streams to allow use of familiar stdio functions.
 *
 * Configures `stdout` and `stdin` `printf()` to write to, and `scanf()` to
 * read from, the serial interface between the microcontroller and the host
 * computer. Configures additional file streams to allow `fprintf()` to work
 * with the display module.
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

#ifndef COWPI_STDIO_H
#define COWPI_STDIO_H

#include <stdbool.h>
#include <stdint.h>

/* File streams for using fprintf with display modules */

extern FILE *cowpi_lcd1602_row[2];

/* Public-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configures the CowPi library to use `stdio.h` functions.
 *
 * Configures `printf()` to write to, and `scanf()` to read from, the serial
 * interface between the microcontroller and the host computer. Calls to
 * `printf()` and `scanf()` that occur before the call to `cowpi_stdio_setup()`
 * will have no effect.
 *
 * @ingroup configuration
 *
 * @param baud the USART signal rate
 */
void cowpi_stdio_setup(unsigned long baud);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_STDIO_H

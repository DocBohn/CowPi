/**************************************************************************//**
 *
 * @file cowpi_setup.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Functions, constants, and masks to configure the Cow Pi hardware and to
 * query the configuration.
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

#ifndef COWPI_SETUP_H
#define COWPI_SETUP_H

#include <stdbool.h>
#include <stdint.h>

/* Public-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configures the microcontroller's pins for the expected hardware setup,
 * configures `stdout` and `stdin` to use the USB-based serial interface between
 * the microcontroller and the host computer, and configures the library to work
 * with the specified display module and communication protocol.
 *
 * If the Morse Code "font" is available, then `stderr` will use Morse Code on
 * the right LED. Otherwise, `stderr` will be aliased to `stdout`.
 *
 * If the USB-based serial interface should not be configured, then set the
 * `console_bitrate` to 0. If there is not yet a display module, then set the
 * `display_module` to {.display_module = NO_MODULE}. If there is not yet a
 * display module (and the communication protocol's pins are not otherwise used)
 * then you may use {.protocol = NO_PROTOCOL}.
 *
 * @sa cowpi_stdio_setup in CowPi_stdio
 * @sa cowpi_add_display_module in CowPi_stdio
 *
 * @param console_bitrate the serial interface's bitrate, or `0` if the serial
 *      interface should not be configured
 * @param display_module the display module's details
 * @param communication_protocol the communication protocol's details
 * @return a pointer to a `FILE` stream for the display module, or `NULL` if a
 *      stream could not be created
 */
FILE *cowpi_setup(unsigned long console_bitrate,
                  cowpi_display_module_t display_module,
                  cowpi_display_module_protocol_t communication_protocol);

#ifdef __cplusplus
} // extern "C"
#endif


#endif //COWPI_SETUP_H

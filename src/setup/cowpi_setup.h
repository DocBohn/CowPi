/**************************************************************************//**
 *
 * @file cowpi_setup.h
 *
 * @author Christopher A. Bohn
 *
 * @brief A functions to configure the Cow Pi hardware.
 *
 ******************************************************************************/

/* CowPi (c) 2021-24 Christopher A. Bohn
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
 * `display_module` to `{.display_module = NO_MODULE}`. If there is not yet a
 * display module (and the communication protocol's pins are not otherwise used)
 * then you may assign `communication_protocol` to `{.protocol = NO_PROTOCOL}`.
 *
 * @sa `cowpi_stdio_setup()` in CowPi_stdio
 * @sa `cowpi_add_display_module()` in CowPi_stdio
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

/**
 * @brief Configures the specified pin to be output pins
 *
 * The <code>pins</code> argument is used to specify which pins will be output
 * pins. Bit0 corresponds to Pin 0, Bit1 corresponds to Pin 1, and so on. A 1 in
 * a particular bit indicates that the corresponding pin should be an output
 * pin, overriding any previous configuration for that pin. If more than one bit
 * has a 1, then each of the corresponding pins will be output pins. The
 * configuration of any pin whose corresponding bit bit is 0 will be unchanged,
 * regardless of whether that pin had been previously set as an input or output
 * pin.
 *
 * @param pins A bit vector specifying which pins will be output pins
 */
void cowpi_set_output_pins(uint32_t pins);

/**
 * @brief Configures the specified pin to be input pins with high impedance to
 * both the microprocessor's reference voltage and ground; that is, their input
 * values will float unless driven high or low by a peripheral device.
 *
 * The <code>pins</code> argument is used to specify which pins will be input
 * pins. Bit0 corresponds to Pin 0, Bit1 corresponds to Pin 1, and so on. A 1 in
 * a particular bit indicates that the corresponding pin should be a floating
 * input pin, overriding any previous configuration for that pin. If more than
 * one bit has a 1, then each of the corresponding pins will be floating input
 * pins. The configuration of any pin whose corresponding bit bit is 0 will be
 * unchanged, regardless of whether that pin had been previously set as an input
 * or output pin, and regardless of whether it had been previously set to float
 * or tied to a pullup or pulldown resistor.
 *
 * @param pins A bit vector specifying which pins will be floating input pins
 */
void cowpi_set_floating_input_pins(uint32_t pins);

/**
 * @brief Configures the specified pin to be input pins connected to a pullup
 * resistor that is internal to the microcontroller; that is, their input
 * values will be high unless driven low by a peripheral device.
 *
 * The <code>pins</code> argument is used to specify which pins will be input
 * pins. Bit0 corresponds to Pin 0, Bit1 corresponds to Pin 1, and so on. A 1 in
 * a particular bit indicates that the corresponding pin should be a pulled-up
 * input pin, overriding any previous configuration for that pin. If more than
 * one bit has a 1, then each of the corresponding pins will be pulled-up input
 * pins. The configuration of any pin whose corresponding bit bit is 0 will be
 * unchanged, regardless of whether that pin had been previously set as an input
 * or output pin, and regardless of whether it had been previously set to float
 * or tied to a pullup or pulldown resistor.
 *
 * @param pins A bit vector specifying which pins will be floating input pins
 */
void cowpi_set_pullup_input_pins(uint32_t pins);

#ifdef ARDUINO_ARCH_RP2040
/**
 * @brief Configures the specified pin to be input pins connected to a pulldown
 * resistor that is internal to the microcontroller; that is, their input
 * values will be low unless driven high by a peripheral device.
 *
 * The <code>pins</code> argument is used to specify which pins will be input
 * pins. Bit0 corresponds to Pin 0, Bit1 corresponds to Pin 1, and so on. A 1 in
 * a particular bit indicates that the corresponding pin should be a pulled-down
 * input pin, overriding any previous configuration for that pin. If more than
 * one bit has a 1, then each of the corresponding pins will be pulled-down
 * input pins. The configuration of any pin whose corresponding bit bit is 0
 * will be unchanged, regardless of whether that pin had been previously set as
 * an input or output pin, and regardless of whether it had been previously set
 * to float or tied to a pullup or pulldown resistor.
 *
 * @param pins A bit vector specifying which pins will be floating input pins
 */
void cowpi_set_pulldown_input_pins(uint32_t pins);
#endif //ARDUINO_ARCH_RP2040

#ifdef __cplusplus
} // extern "C"
#endif


#endif //COWPI_SETUP_H

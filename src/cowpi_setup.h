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
 * and configures the library to work with the specified display module and
 * communication protocol.
 *
 * @attention If a non-`COWPI_DEFAULT` dialect is used, then
 * `cowpi_set_display_dialect()` must be called *before* `cowpi_setup()`.
 *
 * @attention If the `I2C` (or `IIC` or `TWI`) protocol is used, then
 * `cowpi_set_display_i2c_address()` must be called *before* `cowpi_setup()`.
 *
 * If `printf()` and/or `scanf()` will be used, then we recommend that
 * `cowpi_stdio_setup()` be called before `cowpi_setup()`; however, this is not
 * required.
 *
 * @ingroup configuration
 *
 * @param configuration bitwise disjunction of named constants, specifying the
 *      display module and protocol
 */
void cowpi_setup(unsigned int configuration);

/**
 * @brief Sets the "dialect," or the mapping of protocol bits to display module
 * bits.
 *
 * Some display modules (*e.g.*, MAX7219-based modules) have only one possible
 * mapping, and calling this function has no effect for those modules. For other
 * display modules, the `COWPI_DEFAULT` dialect is the default; this function does
 * not need to be called if the `COWPI_DEFAULT` dialect will be used.
 *
 * @attention If this function is called, it must be called before
 * `cowpi_setup()` so that the display module can be properly configured.
 *
 * @sa cowpi_get_display_dialect
 *
 * @ingroup configuration
 *
 * @param dialect a named constant specifying which mapping of protocol bits to
 *      display module bits shall be used
 */
void cowpi_set_display_dialect(unsigned int dialect);

/**
 * @brief Identifies the "dialect," or the mapping of protocol bits to display
 * module bits, that the library has been configured to use.
 *
 * Some display modules (*e.g.*, MAX7219-based modules) have only one possible
 * mapping. For other the `COWPI_DEFAULT` dialect is the default; this will be the
 * return value if `cowpi_set_display_dialect()` was not called.
 *
 * @sa cowpi_set_display_dialect
 *
 * @ingroup query
 *
 * @return the value equal to that of the named constant corresponding to the
 *      configured dialect
 */
unsigned int cowpi_get_display_dialect(void);

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

/**
 * @brief Identifies whether the SPI hardware will send the
 * least-significant bit first.
 *
 * This function is unlikely to be called by the firmware program: there is no
 * actionable reason for the program to do so. There is, however, no harm in
 * doing so.
 *
 * This function will return `true` only when the display module is `LCD1602`
 * and the dialect is `ADAFRUIT`.
 *
 * @ingroup query
 *
 * @return `true` if the display module and dialect require that the SPI
 *      protocol sends the least-significant bit first
 */
bool cowpi_is_spi_lsbfirst(void);

/**
 * @brief Sets the I2C address for an I2C-driven display module.
 *
 * Because the I2C (aka IIC, TWI) protocol uses addresses to select the
 * peripheral that the microcontroller is communicating with, the display
 * module's address needs to be set. If the SPI protocol is being used, then
 * there is no need to call this function.
 *
 * The common PCF8574-based interfaces used with LCD1602 display modules
 * typically have an address of 0x27, but this can readily be changed.
 *
 * @attention If this function is called, it must be called before
 * `cowpi_setup()` so that the display module can be properly configured.
 *
 * @sa cowpi_get_display_i2c_address
 *
 * @ingroup configuration
 *
 * @param peripheral_address
 */
void cowpi_set_display_i2c_address(uint8_t peripheral_address);

/**
 * @brief Reports the I2C address that the library has been configured to use
 * when communicating with an I2c-driven display module.
 *
 * An illegal I2C address will be returned if `cowpi_set_i2c_address()` was not
 * called. This obviously is not problematic if the I2C protocol is not being
 * used.
 *
 * @sa cowpi_set_display_i2c_address
 *
 * @ingroup query
 *
 * @return the I2C address that the library expects a display module to be at
 */
uint8_t cowpi_get_display_i2c_address(void);
#ifdef __cplusplus
} // extern "C"
#endif


/* Use to create argument to cowpi_setup() */

/** @addtogroup configuration
 *  @{
 */
#define SPI                     0x0001u //!< Instructs `cowpi_setup()` to configure the library for the SPI protocol
#define I2C                     0x0002u //!< Instructs `cowpi_setup()` to configure the library for the I2C protocol
#define IIC                     0x0002u //!< Alias of `I2C`
#define TWI                     0x0002u //!< Alias of `I2C`
#define MAX7219                 0x0080u //!< Instructs `cowpi_setup()` to configure the library for a MAX7219-based display module and to configure the display module
#define LCD1602                 0x0040u //!< Instructs `cowpi_setup()` to configure the library for an LCD1602 display module and to configure the display module
/** @} */


/* Use as argument to cowpi_set_display_dialect() */

/** @addtogroup configuration
 * @{
 */
#define COWPI_DEFAULT           0x8000u //!< Instructs `cowpi_set_display_dialect()` to configure the library to use the common mapping of protocol bits to display module bits
#define ADAFRUIT                0x4000u //!< Instructs `cowpi_set_display_dialect()` to configure the library for [Adafruit's I2C/SPI character LCD backpack](https://www.adafruit.com/product/292)
/** @} */


/* Masks to distinguish between configuration fields */

#define PROTOCOL_MASK           0x000Fu
#define DISPLAY_DEVICE_MASK     0x00F0u
#define DISPLAY_DIALECT_MASK    0xF000u


#endif //COWPI_SETUP_H

/**************************************************************************//**
 *
 * @file cowpi_max7219.c
 *
 * @brief @copybrief cowpi_max7219.h
 *
 * @copydetails cowpi_max7219.h
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

#include <Arduino.h>
#include "cowpi_max7219.h"
#include "cowpi_internal.h"
#include "cowpi_setup.h"
#include "cowpi_dummy_pgmspace.h"


/** @private */
void cowpi_setup_max7219(unsigned int configuration) {
    if (!(configuration & SPI)) {
        char s[79];
        cowpi_error(strcpy_P(s, PSTR("MAX7219 can only be used with SPI protocol. Use `cowpi_setup(MAX7219 | SPI);`.")));
    }
    /* Clear all digit registers */
    for (int i = 1; i <= 8; i++) {
        cowpi_max7219_send(i, 0);
    }
    /* Take display out of decode mode */
    cowpi_max7219_no_decode();
    /* Intensity at 7/32 */
    cowpi_max7219_set_intensity(3);
    /* Scan all eight digits */
    cowpi_max7219_send(0xB, 7);
    /* Take display out of shutdown mode */
    cowpi_max7219_startup();
    /* Take display out of test mode */
    cowpi_max7219_send(0xF, 0);
}

void cowpi_max7219_send(uint8_t address, uint8_t data) {
    digitalWrite(SPI_CHIP_SELECT, LOW);
    shiftOut(MOSI, SCK, MSBFIRST, address);
    shiftOut(MOSI, SCK, MSBFIRST, data);
    digitalWrite(SPI_CHIP_SELECT, HIGH);
}

void cowpi_max7219_no_decode(void) {
    cowpi_max7219_send(0x9, 0);
}

void cowpi_max7219_bcd_decode(void) {
    cowpi_max7219_send(0x9, 0xFF);
}

void cowpi_max7219_set_intensity(uint8_t intensity) {
    cowpi_max7219_send(0xA, intensity & 0xF);
}

void cowpi_max7219_shutdown(void) {
    cowpi_max7219_send(0xC, 0);
}

void cowpi_max7219_startup(void) {
    cowpi_max7219_send(0xC, 1);
}

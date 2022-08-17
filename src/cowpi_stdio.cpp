/**************************************************************************//**
 *
 * @file cowpi_stdio.cpp
 *
 * @author Christopher A. Bohn
 *
 * @brief @copybrief cowpi_stdio_setup
 *
 * Configures `printf()` to write to, and `scanf()` to read from, the serial
 * interface between the microcontroller and the host computer.
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
#include <stdio.h>
#include "cowpi_setup.h"

static FILE serial_monitor;

static int cowpi_getc(FILE *stream);
static int cowpi_putc(char c, FILE *stream);


void cowpi_stdio_setup(unsigned long baud) {
    Serial.begin(baud);
    fdev_setup_stream(&serial_monitor, cowpi_putc, cowpi_getc, _FDEV_SETUP_RW);
    stdin = &serial_monitor;
    stdout = &serial_monitor;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
static int cowpi_getc(FILE *stream) {
    while (!Serial.available()) {}
    return Serial.read();
}

static int cowpi_putc(char c, FILE *stream) {
    Serial.write(c);
    if (c == '\n') {
        Serial.write('\r');
    }
    return c;
}
#pragma GCC diagnostic pop

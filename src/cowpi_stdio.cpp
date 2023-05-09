/**************************************************************************//**
 *
 * @file cowpi_stdio.cpp
 *
 * @brief @copybrief cowpi_stdio.h
 *
 * @copydetails cowpi_stdio.h
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

#include <Arduino.h>
#include <stdio.h>
#include "cowpi_stdio.h"
#include "cowpi_lcd1602.h"

static FILE serial_monitor;

static int cowpi_stdin_getc(FILE *stream);
static int cowpi_stdout_putc(char c, FILE *stream);

static FILE Lcd_Row0;
static FILE Lcd_Row1;
FILE *cowpi_lcd1602_row[2];

static int cowpi_lcd1602_row_putc(char c, FILE *stream);


void cowpi_stdio_setup(unsigned long baud) {
    // stdin, stdout
    Serial.begin(baud);
    fdev_setup_stream(&serial_monitor, cowpi_stdout_putc, cowpi_stdin_getc, _FDEV_SETUP_RW);
    stdin = &serial_monitor;
    stdout = &serial_monitor;
    // lcd1602
    cowpi_lcd1602_row[0] = &Lcd_Row0;
    cowpi_lcd1602_row[1] = &Lcd_Row1;
    fdev_setup_stream(cowpi_lcd1602_row[0], cowpi_lcd1602_row_putc, NULL, _FDEV_SETUP_WRITE);
    fdev_setup_stream(cowpi_lcd1602_row[1], cowpi_lcd1602_row_putc, NULL, _FDEV_SETUP_WRITE);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
static int cowpi_stdin_getc(FILE *stream) {
    while (!Serial.available()) {}
    return Serial.read();
}

static int cowpi_stdout_putc(char c, FILE *stream) {
    Serial.write(c);
    if (c == '\n') {
        Serial.write('\r');
    }
    return c;
}
#pragma GCC diagnostic pop

static int cowpi_lcd1602_row_putc(char c, FILE *stream) {
    static volatile uint8_t ddram_address = 0;
    uint8_t row_start = (stream == cowpi_lcd1602_row[0]) ? 0x00 : 0x40;
    if (c == '\n' || c == '\r') {
        ddram_address = row_start;
        cowpi_lcd1602_place_cursor(row_start);
    } else {
        if (ddram_address < row_start || ddram_address >= row_start + 16) {
            ddram_address = row_start;
            cowpi_lcd1602_place_cursor(row_start);
        }
        cowpi_lcd1602_send_character(c);
        ddram_address++;
    }
    return c;
}
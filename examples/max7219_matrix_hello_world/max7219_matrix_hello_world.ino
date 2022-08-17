#include "CowPi.h"

void setup() {
    cowpi_setup(MAX7219 | SPI);
}

void loop() {
    static uint8_t iteration = 0;
    static uint8_t hello_world[14 * 9];     // for this demo, the greater of 14*6 and 14*9
    static int length = 0;
    static uint8_t matrix[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    static int8_t row = 0;
    static int8_t column = 0;
    if (iteration & 0x4) {
        length = cowpi_font_string_to_vertical_dotmatrix(hello_world, "Hello, world! ", true);
        for (int i = 0; i < 7; i++) {
            matrix[i] = matrix[i + 1];
            cowpi_max7219_send(i + 1, matrix[i]);
        }
        matrix[7] = hello_world[row];
        cowpi_max7219_send(8, matrix[7]);
        row++;
        if (row == length) {
            row = 0;
            iteration++;
        }
    } else {
        length = cowpi_font_string_to_horizontal_dotmatrix(hello_world, "Hello, world! ", true);
        for (int i = 0; i < 8; i++) {
            matrix[i] <<= 1;
            matrix[i] |= (hello_world[column] >> i) & 0x1;
            cowpi_max7219_send(i + 1, matrix[i]);
        }
        column++;
        if (column == length) {
            column = 0;
            iteration++;
        }
    }
    delay(100);
}
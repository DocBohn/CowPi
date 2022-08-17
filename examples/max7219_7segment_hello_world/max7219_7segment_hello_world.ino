#include "CowPi.h"
#include "cowpi_font_7segment.h"

const int8_t length = 14;
uint8_t hello_world[length];

void setup() {
    cowpi_setup(MAX7219 | SPI);
    cowpi_font_string_to_7segment(hello_world, "Hello world!  ");
}

void loop() {
    static int8_t letter = 0;
    static uint8_t letters[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 7; i > 0; i--) {
        letters[i] = letters[i - 1];
        cowpi_max7219_send(i + 1, letters[i]);
    }
    letters[0] = hello_world[letter++];
    cowpi_max7219_send(1, letters[0]);
    if (letter == length) {
        letter = 0;
    }
    delay(150);
}

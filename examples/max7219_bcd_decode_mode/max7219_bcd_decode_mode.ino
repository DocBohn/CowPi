#include "CowPi.h"

void setup() {
    cowpi_setup(MAX7219 | SPI);
    cowpi_max7219_bcd_decode();
}

void loop() {
    static int8_t number = 0;
    static bool increment = true;
    for (int digit = 1; digit <= 8; digit++) {
        cowpi_max7219_send(digit, number);
    }
    if (number == 0) {
        increment = true;
        delay(500);
        cowpi_max7219_shutdown();
        delay(500);
        cowpi_max7219_startup();
    }
    if (number == 9) {
        increment = false;
        delay(250);
    }
    number = number + (increment ? 1 : -1);
    delay(500);
}
#include "CowPi.h"

const uint8_t runner[][8] = {
        {0x06, 0x06, 0x0c, 0x16, 0x04, 0x06, 0x09, 0x01},
        {0x06,0x06,0x0c,0x0f,0x04,0x0c,0x12,0x02},
        {0x06,0x06,0x04,0x0e,0x05,0x04,0x06,0x08}
};

const int8_t number_of_frames = 3;

void setup() {
    cowpi_stdio_setup(9600);

    unsigned int protocol;

    /* Select either the SPI protocol or the I2C protocol */
//    protocol = SPI;
    protocol = I2C;

    /* If SPI, then set the dialect (SPI-to-LCD1602 mapping) because right now
     * only the ADAFRUIT dialect is supported, but I don't want to imply that
     * there won't be another default anytime soon */
    if (protocol == SPI) {
        cowpi_set_display_dialect(ADAFRUIT);
    }

    /* If I2C, then the I2C address and possibly dialect (I2C-to-LCD1602 mapping)
     * need to be set before calling `cowpi_setup`. */
    if (protocol == I2C) {
        cowpi_set_display_i2c_address(0x27);
//        cowpi_set_display_dialect(ADAFRUIT);
    }

    cowpi_setup(LCD1602 | protocol);

    for (int i = 0; i < number_of_frames; i++) {
        cowpi_lcd1602_create_character(i, runner[i]);
    }
    cowpi_lcd1602_set_backlight(true);
    cowpi_lcd1602_place_character(0, 0);
}

void loop() {
    static uint8_t frame = 0;
    static uint8_t position = 0;
    delay(250);
    cowpi_lcd1602_place_character(position, ' ');
    if (++position == 0x10) {
        position = 0x40;
    } else if (position == 0x50) {
        position = 0;
    }
    if (++frame == number_of_frames) {
        frame = 0;
    }
    cowpi_lcd1602_place_character(position, frame);
}
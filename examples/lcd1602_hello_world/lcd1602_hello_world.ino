#include "CowPi.h"

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

    printf("You should see the backlight blinking.\n");
    printf("Adjust the contrast until you can see the \"Hello, world!\" message.\n");

    if (protocol == I2C) {
        uint8_t i2c_address = cowpi_get_display_i2c_address();
        cowpi_lcd1602_place_cursor(0x4F);
        cowpi_lcd1602_send_command(LCDENTRY_CURSORMOVESLEFT);
        cowpi_lcd1602_send_character((i2c_address & 0xF) + '0');
        cowpi_lcd1602_send_character(((i2c_address >> 4) & 0xF) + '0');
        const char backwards_message[] = "x0=sserdda c2i";
        const char *c = backwards_message;
        while (*c != '\0') {
            cowpi_lcd1602_send_character(*c++);
        }
        cowpi_lcd1602_return_home();
        cowpi_lcd1602_send_command(LCDENTRY_CURSORMOVESRIGHT);
    }
    const char hello_world[] = "Hello, world!";
    const char *c = hello_world;
    while (*c != '\0') {
        cowpi_lcd1602_send_character(*c++);
    }
}

void loop() {
    static bool backlight_is_on = false;
    backlight_is_on = !backlight_is_on;
    cowpi_lcd1602_set_backlight(backlight_is_on);
    delay(500);
}
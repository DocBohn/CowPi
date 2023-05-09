#include "CowPi.h"

const char too_long_string[] = "There are too many characters in this line!!    \n";
const uint8_t backslash = 0x01;   // ROM Code A00 has a Yen symbol instead of '\\'

void setup() {
    cowpi_stdio_setup(9600);

    unsigned int protocol;

    /* Select either the SPI protocol or the I2C protocol */
//    protocol = SPI;
    protocol = I2C;

    /* The COWPI_DEFAULT mapping from the serial adapter to the LCD1602 module does not need to be
     * explicitly set, but if a different mapping needs to be used, then uncomment this next line. */
//    cowpi_set_display_dialect(ADAFRUIT);

    /* If I2C, then the I2C address and possibly dialect (I2C-to-LCD1602 mapping)
     * need to be set before calling `cowpi_setup`. */
    if (protocol == I2C) {
        cowpi_set_display_i2c_address(0x27);
    }

    cowpi_setup(LCD1602 | protocol);

    uint8_t backslash_matrix[8];
    cowpi_font_ascii_to_5wide_dotmatrix(backslash_matrix, '\\');
    cowpi_lcd1602_create_character(backslash, backslash_matrix);

    cowpi_lcd1602_set_backlight(true);
}

void loop() {
    cowpi_lcd1602_clear_display();
    fprintf(cowpi_lcd1602_row[0], "16 chars/line\n"); delay(500);
    fprintf(cowpi_lcd1602_row[1], "0123456789ABCDEF\n"); delay(1000);
    fprintf(cowpi_lcd1602_row[1], "%16c\n", ' ');
    for (size_t i = 0; i < strlen(too_long_string); i++) {
        fprintf(cowpi_lcd1602_row[1], "%c", too_long_string[i]); delay(250);
    }
    delay(1000);
    fprintf(cowpi_lcd1602_row[1], "%16c\n", ' ');
    fprintf(cowpi_lcd1602_row[0], "End line with %cn\n", (char) backslash); delay(1000);
    fprintf(cowpi_lcd1602_row[0], "%-16s\n", "so next fprintf"); delay(1000);
    fprintf(cowpi_lcd1602_row[0], "%-16s\n", "starts on left "); delay(500);
    fprintf(cowpi_lcd1602_row[1], "One\n"); delay(1000);
    fprintf(cowpi_lcd1602_row[1], "Two\n"); delay(2000);
    fprintf(cowpi_lcd1602_row[0], "%16c\n", ' ');
    fprintf(cowpi_lcd1602_row[1], "%16c\n", ' ');
    fprintf(cowpi_lcd1602_row[0], "Without the %cn\n", (char) backslash); delay(1000);
    fprintf(cowpi_lcd1602_row[0], "next print goes \n"); delay(1000);
    fprintf(cowpi_lcd1602_row[0], "after previous  \n"); delay(500);
    fprintf(cowpi_lcd1602_row[1], "Three"); delay(1000);
    fprintf(cowpi_lcd1602_row[1], "Four\n"); delay(2000);
    fprintf(cowpi_lcd1602_row[0], "%16c\n", ' ');
    fprintf(cowpi_lcd1602_row[1], "%16c\n", ' ');
}
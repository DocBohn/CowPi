#include "CowPi.h"
#include <stdint.h>
#include <string.h>

const char too_long_string[] = "There are too many characters in this string!!\n";
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
    fprintf(cowpi_lcd1602, "\f16 chars/line\n"); delay(500);
    fprintf(cowpi_lcd1602, "0123456789ABCDEF\n"); delay(1000);
    fprintf(cowpi_lcd1602, "\v\n\v");
    for (size_t i = 0; i < strlen(too_long_string); i++) {
        fprintf(cowpi_lcd1602, "%c", too_long_string[i]); delay(250);
    }
    delay(1000);
    cowpi_lcd1602_clear_display();
    fprintf(cowpi_lcd1602, "\freturn home\n");
    fprintf(cowpi_lcd1602, "  with %cf\f", (char) backslash); delay(2000);

    fprintf(cowpi_lcd1602, "\f----------------\n----------------\n"); delay(1000);
    fprintf(cowpi_lcd1602, "Go to next row\v");
    fprintf(cowpi_lcd1602, "  with %cv\v", (char) backslash); delay(2000);

    fprintf(cowpi_lcd1602, "\f----------------\n----------------\n"); delay(1000);
    fprintf(cowpi_lcd1602, "Clear row & go\n");
    fprintf(cowpi_lcd1602, "to next row: %cn\n", (char) backslash); delay(2000);

    fprintf(cowpi_lcd1602, "\f----------------\n----------------\n"); delay(1000);
    fprintf(cowpi_lcd1602, "Advance\tcursor\n"); delay(1000);
    fprintf(cowpi_lcd1602, "\t\twith\t%ct\n", (char) backslash); delay(2000);

    cowpi_lcd1602_clear_display(); delay(500);
    fprintf(cowpi_lcd1602, "\nGo to row start\r"); delay(1000);
    fprintf(cowpi_lcd1602, "  with %cr  \r", (char) backslash); delay(2000);
}
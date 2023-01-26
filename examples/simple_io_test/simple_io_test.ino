#include "CowPi.h"

void setup() {
    cowpi_stdio_setup(9600);
    char s[83];
    printf("CowPi library version %s\n", COWPI_VERSION);
    printf("%s", strcpy_P(s, PSTR("This demonstration makes no assumptions about your CowPi's display module,\n")));
    printf("%s", strcpy_P(s, PSTR("\tso your display module may display garbage -- that's okay.\n")));
    printf("%s", strcpy_P(s, PSTR("The `cowpi_setup` function will be called with either `SPI` or `I2C` so that\n")));
    printf("%s", strcpy_P(s, PSTR("\tthe CowPi library knows where your slider switches are.\n")));
    printf("%s", strcpy_P(s, PSTR("\tYour instructor should have told you which to use.\n")));

    cowpi_setup(SPI);
//    cowpi_setup(I2C);

    printf("%s", strcpy_P(s, PSTR("The simple I/O test will print the status of the keypad and of each\n")));
    printf("%s", strcpy_P(s, PSTR("\tbutton, switch, and LED every half-second.\n")));
    printf("%s", strcpy_P(s, PSTR("Press the Enter key on your host computer's keyboard to start.\n")));
    scanf("%c", s);
}

void loop() {
    bool left_led, right_led;
    char c;
    printf("\n");
    printf("Keypad:      %c        Column pins:  %d%d%d%d    Keypad NAND: %d\n", (c = cowpi_get_keypress()) ? c : ' ',
           digitalRead(14), digitalRead(15), digitalRead(16), digitalRead(17), digitalRead(3));
    printf("Left switch: %s    Right switch: %s\n",
           cowpi_left_switch_is_in_left_position() ? "LEFT " : "RIGHT",
           cowpi_right_switch_is_in_left_position() ? "LEFT " : "RIGHT");
    printf("Left button: %s    Right button: %s",
           cowpi_left_button_is_pressed() ? "DOWN " : "UP   ",
           cowpi_right_button_is_pressed() ? "DOWN " : "UP   ");
#if defined ARDUINO_AVR_UNO || defined ARDUINO_AVR_NANO || defined ARDUINO_AVR_MEGA2560
    printf("   Button NAND: %d", digitalRead(2));
#endif
    printf("\n");
    if (cowpi_left_button_is_pressed() && cowpi_left_switch_is_in_right_position()) {
        left_led = true;
        cowpi_illuminate_left_led();
    } else {
        left_led = false;
        cowpi_deluminate_left_led();
    }
    if (cowpi_right_button_is_pressed() && cowpi_right_switch_is_in_right_position()) {
        right_led = true;
        cowpi_illuminate_right_led();
    } else {
        right_led = false;
        cowpi_deluminate_right_led();
    }
    printf("Left LED:    %s      Right LED:    %s\n", left_led ? "ON " : "OFF", right_led ? "ON " : "OFF");
    delay(500);
}

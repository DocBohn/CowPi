#include <CowPi.h>

void setup(void) {
    cowpi_setup(9600,
                (cowpi_display_module_t) {.display_module = NO_MODULE},
                (cowpi_display_module_protocol_t) {.protocol = NO_PROTOCOL}
    );

#ifdef __AVR__
    printf_P(PSTR("CowPi library version       %s\n"), COWPI_VERSION);
    printf_P(PSTR("CowPi_stdio library version %s\n"), COWPI_STDIO_VERSION);

    printf_P(PSTR("The simple I/O test will print the status of the keypad and of each\n"));
    printf_P(PSTR("\tbutton, switch, and LED every time there is a change.\n\n"));
#else
    printf("CowPi library version       %s\n", COWPI_VERSION);
    printf("CowPi_stdio library version %s\n", COWPI_STDIO_VERSION);

    printf("The simple I/O test will print the status of the keypad and of each\n");
    printf("\tbutton, switch, and LED every time there is a change.\n\n");
#endif //__AVR__
}

void loop(void) {
    static bool left_button_was_pressed = false;
    static bool right_button_was_pressed = false;
    static bool left_switch_was_in_left_position = false;
    static bool right_switch_was_in_left_position = false;
    static char previous_key = 'z';     // this is impossible and will trigger the initial status "update"
    bool left_button_is_pressed = cowpi_debounce_byte(cowpi_left_button_is_pressed(), LEFT_BUTTON_DOWN);
    bool right_button_is_pressed = cowpi_debounce_byte(cowpi_right_button_is_pressed(), RIGHT_BUTTON_DOWN);
    bool left_switch_is_in_left_position = cowpi_debounce_byte(cowpi_left_switch_is_in_left_position(),
                                                               LEFT_SWITCH_LEFT);
    bool right_switch_is_in_left_position = cowpi_debounce_byte(cowpi_right_switch_is_in_left_position(),
                                                                RIGHT_SWITCH_LEFT);
    char current_key = (char) cowpi_debounce_byte(cowpi_get_keypress(), KEYPAD);
    bool update_is_needed = ((left_button_is_pressed != left_button_was_pressed)
                             || (right_button_is_pressed != right_button_was_pressed)
                             || (left_switch_is_in_left_position != left_switch_was_in_left_position)
                             || (right_switch_is_in_left_position != right_switch_was_in_left_position)
                             || (current_key != previous_key));
    if (update_is_needed) {
        left_button_was_pressed = left_button_is_pressed;
        right_button_was_pressed = right_button_is_pressed;
        left_switch_was_in_left_position = left_switch_is_in_left_position;
        right_switch_was_in_left_position = right_switch_is_in_left_position;
        previous_key = current_key;
        bool illuminate_left_led = left_button_is_pressed && !left_switch_is_in_left_position;
        bool illuminate_right_led = right_button_is_pressed && !right_switch_is_in_left_position;
        char c;
#if (ARDUINO_AVR_UNO) || defined (ARDUINO_AVR_NANO) || defined (ARDUINO_AVR_MEGA2560)
        printf_P(PSTR("Keypad:      %-5c    Column pins:  %d%d%d%d\n"),
                 (c = current_key) ? c : '-', digitalRead(A0), digitalRead(A1), digitalRead(A2), digitalRead(A3));
        printf_P(PSTR("Left switch: %-5s    Right switch: %s\n"),
                 left_switch_is_in_left_position ? "LEFT" : "RIGHT",
                 right_switch_is_in_left_position ? "LEFT" : "RIGHT");
        printf_P(PSTR("Left button: %-5s    Right button: %s\n"),
                 left_button_is_pressed ? "DOWN" : "UP",
                 right_button_is_pressed ? "DOWN" : "UP");
        printf_P(PSTR("Left LED:    %-5s    Right LED:    %s\n\n"),
                 illuminate_left_led ? "ON" : "OFF",
                 illuminate_right_led ? "ON " : "OFF");
#elif defined (ARDUINO_RASPBERRY_PI_PICO) || defined (PICO_RP2040)
        printf("Keypad:      %-5c    Column pins:  %d%d%d%d\n",
               (c = current_key) ? c : '-', digitalRead(10), digitalRead(11), digitalRead(12), digitalRead(13));
        printf("Left switch: %-5s    Right switch: %s\n",
               left_switch_is_in_left_position ? "LEFT" : "RIGHT",
               right_switch_is_in_left_position ? "LEFT" : "RIGHT");
        printf("Left button: %-5s    Right button: %s\n",
               left_button_is_pressed ? "DOWN" : "UP",
               right_button_is_pressed ? "DOWN" : "UP");
        printf("Left LED:    %-5s    Right LED:    %s\n\n",
               illuminate_left_led ? "ON" : "OFF",
               illuminate_right_led ? "ON " : "OFF");
#else
        printf("Keypad:      %-5c    Column pins:  %d%d%d%d\n",
                 (c = current_key) ? c : '-', digitalRead(A0), digitalRead(A1), digitalRead(A2), digitalRead(A3));
        printf("Left switch: %-5s    Right switch: %s\n",
               left_switch_is_in_left_position ? "LEFT" : "RIGHT",
               right_switch_is_in_left_position ? "LEFT" : "RIGHT");
        printf("Left button: %-5s    Right button: %s\n",
               left_button_is_pressed ? "DOWN" : "UP",
               right_button_is_pressed ? "DOWN" : "UP");
        printf("Left LED:    %-5s    Right LED:    %s\n\n",
               illuminate_left_led ? "ON" : "OFF",
               illuminate_right_led ? "ON " : "OFF");
#endif //MICROCONTROLLER BOARD
        if (illuminate_left_led) {
            cowpi_illuminate_left_led();
        } else {
            cowpi_deluminate_left_led();
        }
        if (illuminate_right_led) {
            cowpi_illuminate_right_led();
        } else {
            cowpi_deluminate_right_led();
        }
    }
}

//#include "../../src/CowPi.h"
#include "CowPi.h"
#include <stdio.h>

void handle_keypad(void);
void handle_left_button(void);
void handle_right_button(void);
void handle_left_switch(void);
void handle_right_switch(void);

#define DEBOUNCE_THRESHOLD 20

#define debounce_interrupt(action)                            \
  do {                                                        \
    static unsigned long last_trigger = 0L;                   \
    unsigned long now = millis();                             \
    if (now - last_trigger > DEBOUNCE_THRESHOLD) { action; }  \
    last_trigger = now;                                       \
  } while(0)


void setup() {
    cowpi_stdio_setup(9600);
    cowpi_setup(I2C);
    cowpi_register_pin_ISR((1L << 14) | (1L <<15) | (1L << 16) | (1L << 17), handle_keypad);
    cowpi_register_pin_ISR(1L << 8, handle_left_button);
    cowpi_register_pin_ISR(1L << 9, handle_right_button);
    cowpi_register_pin_ISR(1L << 11, handle_left_switch);
    cowpi_register_pin_ISR(1L << 10, handle_right_switch);
}

void loop() {
    ;
}

void handle_keypad(void) {
    debounce_interrupt({
        static char last_key = 0xF0;  // Whether we're getting ASCII characters or (hexa)decimal values, this initial value won't occur
        char key;
        while ((key = cowpi_get_keypress()) == last_key) {}   // busy-wait through the race condition

        printf("keypad: %#4x\n", cowpi_get_keypress());

        last_key = key;
    });
}

void handle_left_button(void) {
    debounce_interrupt({
       static int8_t last_position = -1;
       int8_t this_position;
       while ((this_position = cowpi_left_button_is_pressed()) == last_position) {}     // busy-wait through the race condition

       printf("left button is %s\n", this_position? "pressed" : "released");

       last_position = this_position;
    });
}

void handle_right_button(void) {
    debounce_interrupt({
       static int8_t last_position = -1;
       int8_t this_position;
       while ((this_position = cowpi_right_button_is_pressed()) == last_position) {}    // busy-wait through the race condition

       printf("right button is %s\n", this_position? "down" : "up");

       last_position = this_position;
    });
}

void handle_left_switch(void) {
    debounce_interrupt({
       static int8_t last_position = -1;
       int8_t this_position;
       while ((this_position = cowpi_left_switch_is_in_left_position()) == last_position) {}    // busy-wait through the race condition

       printf("left switch is to the %s\n", this_position? "left" : "right");

       last_position = this_position;
    });
}

void handle_right_switch(void) {
    debounce_interrupt({
        static int8_t last_position = -1;
        int8_t this_position;
        while ((this_position = cowpi_right_switch_is_in_left_position()) == last_position) {}  // busy-wait through the race condition

        printf("right switch is in the %s position\n", this_position? "left" : "right");

        last_position = this_position;
    });
}

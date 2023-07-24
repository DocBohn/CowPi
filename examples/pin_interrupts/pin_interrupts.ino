#include <CowPi.h>

void handle_keypad(void);
void handle_left_button(void);
void handle_right_button(void);

#define DEBOUNCE_THRESHOLD 20

// using triggers for human-scale events, such as pressing buttons, is probably
// better handled with polling, but for this demonstration, the only certain
// inputs are from the keypad, pushbuttons, and slide switches. Because those
// mechanical devices will bounce, let's make sure there's only one interrupt
// fired per press/release/toggle.
#define debounce_interrupt(action)                            \
  do {                                                        \
    static unsigned long last_trigger = 0L;                   \
    unsigned long now = millis();                             \
    if (now - last_trigger > DEBOUNCE_THRESHOLD) { action; }  \
    last_trigger = now;                                       \
  } while(0)

static volatile char last_key;
static volatile uint8_t last_left_button;
static volatile uint8_t last_right_button;

void setup() {
    cowpi_setup(9600,
                (cowpi_display_module_t) {.display_module = NO_MODULE},
                (cowpi_display_module_protocol_t) {.protocol = NO_PROTOCOL}
    );
    // make sure we know what the initial conditions are, so we handle the race conditions properly (see below)
    last_key = cowpi_get_keypress();
    last_left_button = cowpi_left_button_is_pressed();
    last_right_button = cowpi_right_button_is_pressed();
    // demonstrates multiple pins using the same handler
    cowpi_register_pin_ISR((1L << 14) | (1L << 15) | (1L << 16) | (1L << 17), handle_keypad);
    // demonstrates different pins on the same I/O bank (for ATmega328P) using different handlers
    cowpi_register_pin_ISR(1L << 8, handle_left_button);
    cowpi_register_pin_ISR(1L << 9, handle_right_button);
}

void loop() {
    ;
}

void handle_keypad(void) {
    debounce_interrupt({
        char key;
        // When scanning the keypad to figure out which key was pressed, it's possible that the key bounced, and we
        // see the key in its previous (unpressed) position. Similarly, on a key release, a bounce would make us see
        // the key as pressed. So we'll just keep scanning the keypad until we see something different from what we
        // saw before (something *must* be different, or there wouldn't have been an interrupt).
        // busy-wait through the race condition
        while ((key = cowpi_get_keypress()) == last_key) {}

        // you *really* shouldn't print in an ISR! but this is for demonstration purposes
        printf("keypad: %#4x\n", cowpi_get_keypress());

        last_key = key;
    });
}

void handle_left_button(void) {
    debounce_interrupt({
        uint8_t this_position;
        // busy-wait through the race condition
        while ((this_position = cowpi_left_button_is_pressed()) == last_left_button) {}

        printf("left button is %s\n", this_position? "pressed" : "released");

        last_left_button = this_position;
    });
}

void handle_right_button(void) {
    debounce_interrupt({
        // since the new position MUST be the opposite of the old position, we could simply invert `last_right_button`
        // instead of reading the button's position
        uint8_t this_position = !last_right_button;

        printf("right button is %s\n", this_position? "down" : "up");

        last_right_button = this_position;
    });
}

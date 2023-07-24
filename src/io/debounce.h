

#ifndef COWPI_DEBOUNCE_H
#define COWPI_DEBOUNCE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum input_names {
    LEFT_BUTTON_DOWN = 0,
    RIGHT_BUTTON_DOWN,
    LEFT_SWITCH_LEFT,
    RIGHT_SWITCH_LEFT,
    LEFT_SWITCH_RIGHT,
    RIGHT_SWITCH_RIGHT,
    KEYPAD,
    INPUT_X,
    INPUT_Y,
    NUMBER_OF_INPUTS
};

uint8_t debounce_byte(uint8_t current_value, enum input_names input_name);

uint16_t debounce_short(uint16_t current_value, enum input_names input_name);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_DEBOUNCE_H

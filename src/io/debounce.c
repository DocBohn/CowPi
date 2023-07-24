
#include <Arduino.h>
#include "debounce.h"


#define DEBOUNCE_THRESHOLD 40



uint8_t debounce_byte(uint8_t current_value, enum input_names input_name) {
    static uint8_t last_actual_value[NUMBER_OF_INPUTS] = {0};
    static uint8_t last_good_value[NUMBER_OF_INPUTS] = {0};
    static unsigned long last_change[NUMBER_OF_INPUTS] = {[0 ... (NUMBER_OF_INPUTS - 1)] = 0x80000000}; // gcc extension
    unsigned long now = millis();
    /*
    // responds immediately and then ignores further changes until input stabilizes -- more responsive
    last_good_value[input_name] = (now - last_change[input_name] < DEBOUNCE_THRESHOLD) ? last_good_value[input_name]
                                                                                       : current_value;
    last_change[input_name] = (current_value == last_actual_value[input_name]) ? last_change[input_name] : now;
    */
    /* ...OR... */
    // ignores changes until input stabilizes and then responds -- more immune to transients
    last_change[input_name] = (current_value == last_actual_value[input_name]) ? last_change[input_name] : now;
    last_good_value[input_name] = (now - last_change[input_name] < DEBOUNCE_THRESHOLD) ? last_good_value[input_name]
                                                                                       : current_value;
    last_actual_value[input_name] = current_value;
    return last_good_value[input_name];
}


uint16_t debounce_short(uint16_t current_value, enum input_names input_name) {
    static uint16_t last_actual_value[NUMBER_OF_INPUTS] = {0};
    static uint16_t last_good_value[NUMBER_OF_INPUTS] = {0};
    static unsigned long last_change[NUMBER_OF_INPUTS] = {[0 ... (NUMBER_OF_INPUTS - 1)] = 0x80000000}; // gcc extension
    unsigned long now = millis();
    last_change[input_name] = (current_value == last_actual_value[input_name]) ? last_change[input_name] : now;
    last_good_value[input_name] = (now - last_change[input_name] < DEBOUNCE_THRESHOLD) ? last_good_value[input_name]
                                                                                       : current_value;
    last_actual_value[input_name] = current_value;
    return last_good_value[input_name];
}

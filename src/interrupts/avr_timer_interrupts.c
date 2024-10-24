/**************************************************************************//**
 *
 * @file avr_timer_interrupts.c
 *
 * @author Christopher A. Bohn
 *
 * @brief @copybrief timer_interrupts.h
 *
 * @details @copydetails cowpi_io.h
 *
 ******************************************************************************/

/* CowPi (c) 2021-24 Christopher A. Bohn
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined (__AVR__)

#include <avr/interrupt.h>
#include <util/atomic.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "timer_interrupts.h"

static void do_nothing(void) {}

//static unsigned int constexpr NUMBER_OF_PRESCALERS = 7;
#define NUMBER_OF_PRESCALERS (7)

struct timer_data {
    int prescalers[NUMBER_OF_PRESCALERS];
    uint32_t number_of_counter_values;
    uint8_t normal_mode_bits[2];
    uint8_t ctc_mode_bits[2];
    uint8_t clock_select_bits[2][NUMBER_OF_PRESCALERS];
    uint8_t number_of_isr_slots;
    void (*interrupt_service_routines[3])(void);
};

static struct timer_data timers[] = {
        {
                .prescalers = {1, 8, 64, 256, 1024, 0, 0},
                .number_of_counter_values = 1L << 8,
                .normal_mode_bits = {0, 0},
                .ctc_mode_bits = {1 << 1, 0},
                .clock_select_bits = {{0},
                                      {1, 2, 3, 4, 5, 0, 0}},
                .number_of_isr_slots = 0,
                .interrupt_service_routines = {do_nothing, do_nothing, do_nothing},
        },
        {
                .prescalers = {1, 8, 64, 256, 1024, 0, 0},
                .number_of_counter_values = 1L << 16,
                .normal_mode_bits = {0, 0},
                .ctc_mode_bits = {0, 1 << 3},
                .clock_select_bits = {{0},
                                      {1, 2, 3, 4, 5, 0, 0}},
                .number_of_isr_slots = 0,
                .interrupt_service_routines = {do_nothing, do_nothing, do_nothing},
        },
        {
                .prescalers = {1, 8, 32, 64, 128, 256, 1024},
                .number_of_counter_values = 1L << 8,
                .normal_mode_bits = {0, 0},
                .ctc_mode_bits = {1 << 1, 0},
                .clock_select_bits = {{0},
                                      {1, 2, 3, 4, 5, 6, 7}},
                .number_of_isr_slots = 0,
                .interrupt_service_routines = {do_nothing, do_nothing, do_nothing},
        }
};

ISR(TIMER1_OVF_vect) {
        timers[1].interrupt_service_routines[0]();
}

ISR(TIMER1_COMPA_vect) {
        timers[1].interrupt_service_routines[1]();
}

ISR(TIMER1_COMPB_vect) {
        timers[1].interrupt_service_routines[2]();
}

ISR(TIMER2_OVF_vect) {
        timers[2].interrupt_service_routines[0]();
}

ISR(TIMER2_COMPA_vect) {
        timers[2].interrupt_service_routines[1]();
}

ISR(TIMER2_COMPB_vect) {
        timers[2].interrupt_service_routines[2]();
}

float configure_timer(unsigned int timer_number, float desired_period_us) {
    if (timer_number < 1 || timer_number > 2) {
        // for now, we'll prohibit TIMER0 and assume only TIMER1 & TIMER2 exist -- later we can do uc-specific values
        return INFINITY;
    }
    if (desired_period_us < 1) {
        return INFINITY;
    }
    struct timer_data *timer = timers + timer_number;
    timer->interrupt_service_routines[0] = do_nothing;
    timer->interrupt_service_routines[1] = do_nothing;
    timer->interrupt_service_routines[2] = do_nothing;
    float const system_clock = 16.0f;   // cycles per microsecond
    float best_error = INFINITY;
    float best_period = INFINITY;
    uint32_t best_count;
    unsigned int best_index;
    // Determine the best prescaler and comparison value
    for (unsigned int i = 0; i < NUMBER_OF_PRESCALERS; i++) {
        int prescaler = timer->prescalers[i];
        if (prescaler != 0) {
            float closest_count_above = ceilf(desired_period_us * system_clock / prescaler);
            float closest_count_below = floorf(desired_period_us * system_clock / prescaler);
            float actual_period_us = closest_count_above * prescaler / system_clock;
            float error = fabsf(actual_period_us - desired_period_us);
            if (((uint32_t) closest_count_above <= timer->number_of_counter_values) && (error < best_error)) {
                best_error = error;
                best_period = actual_period_us;
                best_count = ((uint32_t) closest_count_above) - 1;
                best_index = i;
            }
            actual_period_us = closest_count_below * prescaler / system_clock;
            error = fabsf(actual_period_us - desired_period_us);
            if (((uint32_t) closest_count_below <= timer->number_of_counter_values) && (error < best_error)) {
                best_error = error;
                best_period = actual_period_us;
                best_count = ((uint32_t) closest_count_below) - 1;
                best_index = i;
            }
        }
    }
    // Configure the timer
    uint8_t *mode_bits;
    uint32_t compare_A;
    if (timer->number_of_counter_values - best_count == 1) {    // the comparison value is the maximum possible comparison value
        mode_bits = timer->normal_mode_bits;
        compare_A = 2 * best_count / 3;
        timer->number_of_isr_slots = 3;
    } else {
        mode_bits = timer->ctc_mode_bits;
        compare_A = best_count;
        timer->number_of_isr_slots = 2;
    }
    uint32_t compare_B = compare_A / 2;
    switch(timer_number) {
        case 1:
            TCCR1A = mode_bits[0] | timer->clock_select_bits[0][best_index];
            TCCR1B = mode_bits[1] | timer->clock_select_bits[1][best_index];
            TCCR1C = 0;
            TCNT1 = 0;
            OCR1A = compare_A;
            OCR1B = compare_B;
            TIMSK1 = 0;
            break;
        case 2:
            TCCR2A = mode_bits[0] | timer->clock_select_bits[0][best_index];
            TCCR2B = mode_bits[1] | timer->clock_select_bits[1][best_index];
            TCNT2 = 0;
            OCR2A = compare_A;
            OCR2B = compare_B;
            TIMSK2 = 0;
            break;
        default:
            // unreachable
            return INFINITY;
    }
    return best_period;
}

bool register_periodic_ISR(unsigned int timer_number, unsigned int isr_slot, void (*isr)(void)) {
    struct timer_data *timer = timers + timer_number;
    uint8_t number_of_isr_slots = timer->number_of_isr_slots;
    if (timer_number < 1 || timer_number > 2) {
        // for now, we'll prohibit TIMER0 and assume only TIMER1 & TIMER2 exist -- later we can do uc-specific values
        return false;
    }
    if (isr_slot >= number_of_isr_slots) {
        return false;
    }
    if (number_of_isr_slots == 2) {
        // number_of_isr_slots==2 iff the timer is in CTC mode, which means we cannot use TIMERx_OVF_VECT
        isr_slot++;
    }
    timer->interrupt_service_routines[isr_slot] = isr;
    switch(timer_number) {
        case 1:
            TIMSK1 |= 1 << isr_slot;
            break;
        case 2:
            TIMSK2 |= 1 << isr_slot;
            break;
        default:
            // unreachable
            return false;
    }
    return true;
}

void reset_timer(unsigned int timer_number) {
    // for now, we'll prohibit TIMER0 and assume only TIMER1 & TIMER2 exist -- later we can do uc-specific values
    switch(timer_number) {
        case 1:
            TCNT1 = 0;
            break;
        case 2:
            TCNT2 = 0;
            break;
        default:
            // unreachable
            return;
    }
}



static uint32_t volatile timer_overflow_count = 0;

ISR(TIMER0_COMPA_vect) {
    ++timer_overflow_count;
}

void initialize_timer0_overflow_count(void) {
    OCR0A = 0xFE;
    TIMSK0 |= 1 << 1;
}

unsigned long get_timer0_overflow_count(void) {
    uint32_t count;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        count = timer_overflow_count;
    }
    return count;
}

#endif // __AVR__
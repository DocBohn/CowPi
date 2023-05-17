/**************************************************************************//**
 *
 * @file cowpi_atmega328p_interrupts.c
 *
 * @author Christopher A. Bohn
 *
 * @brief An abstraction for pin change interrupts
 *
 * Provides functions to register and deregister functions to handle to
 * pin change interrupts. The functions allow for a function specific to each
 * pin (or combination of pins), similar to external interrupts. Unlike external
 * interrupts, there is no option for only-rising or only-falling interrupt
 * handlers.
 *
 ******************************************************************************/

/* CowPi (c) 2021-23 Christopher A. Bohn
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

#if defined ARDUINO_AVR_UNO || defined ARDUINO_AVR_NANO

#include <stdint.h>
#include <avr/interrupt.h>
#include "cowpi_interrupts.h"

static void do_nothing(void) {}

static void (*interrupt_service_routines[])(void) = {
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing,
        do_nothing
};

static volatile uint8_t inputs[3];

void cowpi_register_pin_ISR(uint32_t interrupt_mask, void (*isr)(void)) {
    PCICR = 0x0;    // disable pin change interrupts while we're making changes
    int8_t i = 0;
    do {
        if (interrupt_mask & (1L << i)) {
            interrupt_service_routines[i] = isr;
            if (i < 8) {            // D0 -- D7,   PCINT2
                PCMSK2 |= (1 << (i - 0));
                inputs[2] = PIND & PCMSK2;
                PCIFR = 0x4;  // write a 1 to *only* the relevant PCIFR bit
            } else if (i < 14) {    // D8 -- D13,  PCINT0
                PCMSK0 |= (1 << (i - 8));
                inputs[0] = PINB & PCMSK0;
                PCIFR = 0x2;
            } else {                // D14 -- D19, PCINT1
                PCMSK1 |= (1 << (i - 14));
                inputs[1] = PINC & PCMSK1;
                PCIFR = 0x1;
            }
        }
    } while (++i < 32);
    PCICR = 0x7;    // re-enable pin change interrupts
}

void cowpi_deregister_pin_ISR(uint32_t interrupt_mask) {
    PCICR = 0x0;    // disable pin change interrupts while we're making changes
    int8_t i = 0;
    do {
        if (interrupt_mask & (1 << i)) {
            interrupt_service_routines[i] = do_nothing;
            if (i < 8) {            // D0 -- D7,   PCINT2
                PCMSK2 &= ~(1 << (i - 0));
            } else if (i < 14) {    // D8 -- D13,  PCINT0
                PCMSK0 &= ~(1 << (i - 8));
            } else {                // D14 -- D19, PCINT1
                PCMSK1 &= ~(1 << (i - 14));
            }
        }
    } while (++i < 32);
    PCICR = 0x7;    // re-enable pin change interrupts
}

#define RUN_ISR(first_pin, last_pin, io_bank, new_inputs) do {  \
  uint8_t change = (new_inputs) ^ inputs[(io_bank)];            \
  int8_t i = (first_pin);                                       \
  switch (change) {                                             \
    case 0x01:                                                  \
      interrupt_service_routines[(first_pin) + 0]();            \
      break;                                                    \
    case 0x02:                                                  \
      interrupt_service_routines[(first_pin) + 1]();            \
      break;                                                    \
    case 0x04:                                                  \
      interrupt_service_routines[(first_pin) + 2]();            \
      break;                                                    \
    case 0x08:                                                  \
      interrupt_service_routines[(first_pin) + 3]();            \
      break;                                                    \
    case 0x10:                                                  \
      interrupt_service_routines[(first_pin) + 4]();            \
      break;                                                    \
    case 0x20:                                                  \
      interrupt_service_routines[(first_pin) + 5]();            \
      break;                                                    \
    case 0x40:                                                  \
      interrupt_service_routines[(first_pin) + 6]();            \
      break;                                                    \
    case 0x80:                                                  \
      interrupt_service_routines[(first_pin) + 7]();            \
      break;                                                    \
    default:                                                    \
      do {                                                      \
        if (change & 0x1) {                                     \
          interrupt_service_routines[i]();                      \
        }                                                       \
        change >>= 1;                                           \
        i++;                                                    \
      } while (i <= (last_pin));                                \
  }                                                             \
  inputs[(io_bank)] = (new_inputs);                             \
} while (0)

ISR(PCINT0_vect) {
        RUN_ISR(8, 13, 0, PINB & PCMSK0);
}

ISR(PCINT1_vect) {  // handle pin change interrupt for D14 to D19 here
        RUN_ISR(14, 19, 1, PINC & PCMSK1);
}

ISR(PCINT2_vect) {  // handle pin change interrupt for D0 to D7 here
        RUN_ISR(0, 7, 2, PIND & PCMSK2);
}

#endif // ARDUINO_AVR_UNO || ARDUINO_AVR_NANO
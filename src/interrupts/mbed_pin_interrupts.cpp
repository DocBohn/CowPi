/**************************************************************************//**
 *
 * @file mbed_pin_interrupts.cpp
 *
 * @author Christopher A. Bohn
 *
 * @brief An abstraction for pin-based input interrupts
 *
 * Provides functions to register and deregister functions to handle to
 * interrupts on input pins. The functions allow for a function specific to each
 * pin (or combination of pins). There is no option for only-rising or
 * only-falling interrupt handlers.
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

#if defined __MBED__

#include <stdint.h>
#include <InterruptIn.h>
#include "pin_interrupts.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t cowpi_floating_input_pins;
extern uint32_t cowpi_pullup_input_pins;
extern uint32_t cowpi_pulldown_input_pins;

static mbed::InterruptIn *inputs[32] = {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
};

void cowpi_register_pin_ISR(uint32_t interrupt_mask, void (*isr)(void)) {
    int8_t i = 0;
    do {
        if (interrupt_mask & (1L << i)) {
            PinMode mode;
            if (cowpi_floating_input_pins & (1L << i)) {
                mode = PullNone;
            } else if (cowpi_pullup_input_pins & (1L << i)) {
                mode = PullUp;
            } else if (cowpi_pulldown_input_pins & (1L << i)) {
                mode = PullDown;
            } else {
                // pin wasn't configured with cowpi_set_xxx_input_pins(), so we don't know what the mode should be
                mode = PullDefault;
            }
            if (inputs[i] == nullptr) {
                inputs[i] = new mbed::InterruptIn((PinName) i, mode);
            } else {
                inputs[i]->mode(mode);
            }
            inputs[i]->disable_irq();   // disable interrupts while we're making changes
            inputs[i]->rise(isr);
            inputs[i]->fall(isr);
            inputs[i]->enable_irq();   // re-enable interrupts
        }
    } while (++i < 32);
}

void cowpi_deregister_pin_ISR(uint32_t interrupt_mask) {
    int8_t i = 0;
    do {
        if (interrupt_mask & (1L << i)) {
            if (inputs[i] != nullptr) {
                inputs[i]->disable_irq();   // disable interrupts while we're making changes
                inputs[i]->rise(NULL);
                inputs[i]->fall(NULL);
                inputs[i]->enable_irq();   // re-enable interrupts
            }
        }
    } while (++i < 32);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MBED__
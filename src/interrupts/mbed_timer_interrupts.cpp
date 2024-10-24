/**************************************************************************//**
 *
 * @file mbed_timer_interrupts.cpp
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

#if defined (__MBED__)

#include <Ticker.h>
#include <stdbool.h>
#include <stdint.h>
#include "timer_interrupts.h"

#ifdef __cplusplus
extern "C" {
#endif

//static mbed::Ticker *tickers[MAXIMUM_NUMBER_OF_TICKERS] = {
//        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
//};
//
//bool register_timer_ISR(uint32_t period_us, void (*isr)(void)) {
//    static int8_t number_of_tickers = 0;
//    if (number_of_tickers >= MAXIMUM_NUMBER_OF_TICKERS) {
//        return false;
//    }
//    tickers[number_of_tickers] = new mbed::Ticker();
//    tickers[number_of_tickers]->attach(isr, std::chrono::microseconds(period_us));
//    number_of_tickers++;
//    return true;
//}

struct timer_data {
    mbed::Ticker *ticker;
    std::chrono::microseconds period;
    void (*interrupt_service_routine)(void);
};

static std::chrono::microseconds constexpr no_time = std::chrono::microseconds(0);

static struct timer_data timers[MAXIMUM_NUMBER_OF_TIMERS] = {
        {.ticker = nullptr, .period = no_time, .interrupt_service_routine = nullptr,},
        {.ticker = nullptr, .period = no_time, .interrupt_service_routine = nullptr,},
        {.ticker = nullptr, .period = no_time, .interrupt_service_routine = nullptr,},
        {.ticker = nullptr, .period = no_time, .interrupt_service_routine = nullptr,},
        {.ticker = nullptr, .period = no_time, .interrupt_service_routine = nullptr,},
        {.ticker = nullptr, .period = no_time, .interrupt_service_routine = nullptr,},
        {.ticker = nullptr, .period = no_time, .interrupt_service_routine = nullptr,},
        {.ticker = nullptr, .period = no_time, .interrupt_service_routine = nullptr,}
};

bool register_timer_ISR(unsigned int timer_number, uint32_t period_us, void (*isr)(void)) {
    if (timer_number >= MAXIMUM_NUMBER_OF_TIMERS) {
        return false;
    }
    if (period_us <= 2) {
        // I think the microcontroller will seize with even greater values, but that's on the application programmer
        // Here I'm just trying to warn them if they're trying to assign an ISR slot like the AVR version of this function
        return false;
    }
    if (timers[timer_number].ticker == nullptr) {
        timers[timer_number].ticker = new mbed::Ticker();
    }
    timers[timer_number].period = std::chrono::microseconds(period_us);
    timers[timer_number].interrupt_service_routine = isr;
    timers[timer_number].ticker->attach(timers[timer_number].interrupt_service_routine, timers[timer_number].period);
    return true;
}

void reset_timer(unsigned int timer_number) {
    if (timer_number >= MAXIMUM_NUMBER_OF_TIMERS) {
        return;
    }
    if (timers[timer_number].ticker == nullptr) {
        return;
    }
    timers[timer_number].ticker->detach();
    timers[timer_number].ticker->attach(timers[timer_number].interrupt_service_routine, timers[timer_number].period);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MBED__
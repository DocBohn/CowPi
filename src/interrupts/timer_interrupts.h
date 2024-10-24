/**************************************************************************//**
 *
 * @file timer_interrupts.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Functions to register/deregister interrupt handlers for
 * timer-based interrupts
 *
 * Provides functions to configure timers and to register and deregister
 * functions to handle to interrupts that are fired due to timer activity.
 * The particulars vary from target to target.
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

#ifndef COWPI_TIMER_INTERRUPTS_H
#define COWPI_TIMER_INTERRUPTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief Sets a timer to the beginning of its interrupt period.
 *
 * @note On AVR architectures, this affects all ISR slots for the specified
 *      timer.
 *
 * If the interrupt period is *T* microseconds, then:
 * <ul>
 * <li> On AVR architectures, the ISR in slot 0 will execute *T* microseconds
 *      after `reset_timer()` returns. ISRs in other slots will fire sooner,
 *      according to their place in the timer period's partitioning. The
 *      underlying timer's counter will reset to 0.
 * <li> On MBED systems, the ISR will execute *T* microseconds after
 *      `reset_timer()` returns. The underlying timer's counter will be
 *      unchanged.
 * </ul>
 *
 * @param timer_number The timer to be reset
 */
void reset_timer(unsigned int timer_number);

#ifdef __AVR__

/**
 * @brief Configures an AVR timer.
 *
 * The timer will be configured to reset its counter at or near the specified
 * interval. The function will select the configuration that has an actual
 * period as close as possible to the specified period.
 *
 * The timer might be configured for Normal mode or for CTC mode;
 * if a Normal mode configuration and a CTC mode configuration are
 * equally-accurate then the timer will be configured in Normal mode.
 * WGM mode is not supported.
 *
 * Any ISRs that had previously been registered for the timer will be
 * deregistered.
 *
 * This function may not be used to configure TIMER0.
 *
 * @param timer_number The timer to be configured
 * @param desired_period_us The preferred interrupt period
 * @return The actual interrupt period
 */
float configure_timer(unsigned int timer_number, float desired_period_us);

/**
 * @brief Registers a function to service periodic timer interrupts.
 *
 * Each timer has ISR slots for two or three interrupt service routines:
 * two if the timer is in CTC mode, three if the timer is in Normal mode.
 * Regardless of the timer mode, the ISR registered for slot 0 will execute
 * when the counter resets. If the timer is in CTC mode, then the ISR registered
 * for slot 1 will execute halfway between counter resets. If the timer is in
 * Normal mode, then the ISRs registered for slots 1 and 2 will partition the
 * timer period into thirds.
 *
 * The timer must have previously been registered using
 * <code>configure_timer()</code>.
 *
 * This function may not be used to register ISRs for TIMER0.
 *
 * @param timer_number The timer whose interrupt will invoke the ISR
 * @param isr_slot 0 if the ISR should be invoked when the counter resets,
 *      1 or 2 otherwise
 * @param isr The function that will service the timer's interrupts
 * @return <code>true</code> if the ISR was successfully registered;
 *      <code>false</code> otherwise
 */
bool register_periodic_ISR(unsigned int timer_number, unsigned int isr_slot, void (*isr)(void)) __attribute__ ((warn_unused_result));

/**
 * @brief Enable TIMER0 comparison interrupt to support
 *      <code>get_timer0_overflow_count()</code>
 */
void initialize_timer0_overflow_count(void);

/**
 * @brief Returns the number of times that TIMER0 has overflowed.
 *
 * <p>The library counts the number of times that TIMER0 has overflowed (the
 * Arduino core doesn't expose its own count, so CowPi has to do its own).
 * When combined with the current value of TIMER0's counter, a student can
 * compute the number of microseconds since power-up using the formula:
 * 1024 * timer_overflow_count + 4 * timer0_counter_value</p>
 *
 * <p>There are two race conditions that could result in inconsistent values
 * among the timer overflow count and the timer counter value, but we accept the
 * risk. The race condition can be minimized by calling
 * get_timer0_overflow_count() first and then reading the counter value is read,
 * then these windows partially cancel each other out, then the effective race
 * condition window will be 1.375us out of every 1024us.</p>
 *
 * @return the number of times that TIMER0 has overflowed
 */
unsigned long get_timer0_overflow_count(void);

#endif //__AVR__

#ifdef __MBED__

//static unsigned int constexpr MAXIMUM_NUMBER_OF_TICKERS = 8;
#define MAXIMUM_NUMBER_OF_TIMERS (8)    // need maintain portability with pre-C23 for now, so can't use `constexpr`
                                        // when we do switch to C23, we'll also replace `__attribute__ ((warn_unused_result))` with `[[nodiscard("explain the reason")]]`

/**
 * @brief Configures a periodic timer interrupt to fire, and assigns a function
 * to service that interrupt.
 *
 * This function supports up to `MAXIMUM_NUMBER_OF_TIMERS` timers.
 *
 * Any ISR that had previously been registered for the timer will be
 * deregistered.
 *
 * @param timer_number A unique handle for the virtual periodic timer being configured
 * @param period_us The specified interrupt period
 * @param isr The function that will service the timer's interrupts
 * @return <code>true</code> if the periodic interrupt was successfully
 *      configured and the ISR was successfully registered; <code>false</code>
 *      otherwise
 */
bool register_periodic_ISR(unsigned int timer_number, uint32_t period_us, void (*isr)(void)) __attribute__ ((warn_unused_result));

#endif //__MBED__

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_TIMER_INTERRUPTS_H

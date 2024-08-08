/**************************************************************************//**
 *
 * @file rp2040.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Type definitions for the RP2040 microcontroller (Raspberry Pi Pico,
 *      Arduino Nano RP2040 Connect)
 *
 * This header provides the base address for memory-mapped I/O and
 * data structures to conveniently access the I/O registers.
 *
 * Possibly-useful memory-mapped registers:
 * | Use                                            | Datatype              | Memory Address     |
 * |:----------------------------------------------:|:----------------------|:-------------------|
 * | External pins                                  | cowpi_ioport_t        | 0xD000'0000        |
 * | SPI protocol                                   | cowpi_spi_t           | 0x4003'C000 (SPI0) |
 * |                                                |                       | 0x4004'0000 (SPI1) |
 * | I2C protocol                                   | cowpi_i2c_t           | 0x4004'4000 (I2C0) |
 * |                                                |                       | 0x4004'8000 (I2C1) |
 * | Timer                                          | cowpi_timer_t         | 0x4005'4000        |
 * | IPC FIFO pipes, and spinlocks                  | cowpi_concurrency_t   | 0xD000'0050        |
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

#ifndef COWPI_RP2040_H
#define COWPI_RP2040_H

#ifdef ARDUINO_ARCH_RP2040
#define COWPI_USING_A_SUPPORTED_BOARD

#include <stdint.h>

/* *** SINGLE-CYCLE I/O *** (see RP2040 datasheet, section 2.3.1) *** */

/**
 * @brief Structure principally for the general-purpose I/O pins.
 * 
 * This structure also points to registers that contain the CPU ID for each of
 * the two cores.
 */
typedef struct {
    uint32_t cpu_id;                    //!< Always contains 0 when read from core 0, and 1 when read from core 1
    uint32_t input;                     //!< Read input from this field
    uint32_t :32;                       //!< padding (QSPI input)
    uint32_t :32;                       //!< padding (not described in rp2040 datasheet)
    uint32_t output;                    //!< Write outputs to this field
    uint32_t atomic_set;                //!< Perform an atomic bit-set; equivalent to     `output |= bit_vector`
    uint32_t atomic_clear;              //!< Perofrm an atomic bit-clear; equivalent to   `output &= ~bit_vector`
    uint32_t atomic_toggle;             //!< Perform an atomic bitwise XOR; equivalent to `output ^= bit_vector`
    uint32_t output_enable;             //!< Enable output on specified pins
    uint32_t atomic_set_enable;         //!< Perform an atomic bit-set; equivalent to     `output_enable |= bit_vector`
    uint32_t atomic_clear_enable;       //!< Perofrm an atomic bit-clear; equivalent to   `output_enable &= ~bit_vector`
    uint32_t atomic_toggle_enable;      //!< Perform an atomic bitwise XOR; equivalent to `output_enable ^= bit_vector`
} cowpi_ioport_t;

/**
 * @brief Structure to coordinate concurrent behavior between the two cores.
 * 
 * A 32 bit wide, 8 word deep FIFO pipe can be used to pass data/messages
 * between the cores.
 * 
 * @todo incorporate interrupts
 */
typedef struct {
    uint32_t pipe_status;               //!< FIFO Status register; see datasheet for bit descriptions
    uint32_t pipe_write;                //!< Write word in this field to send message to other core
    uint32_t pipe_read;                 //!< Read word from this field to obtain message from other core
    uint32_t spinlock_status;           //!< Status of each of the 32 mutex tokens (1=locked, 0=unlocked)
    uint32_t DO_NOT_TOUCH_1[0x20];      //!< padding (divider)
    uint32_t DO_NOT_TOUCH_2[0x80];      //!< padding (interpolators)
    uint32_t spinlocks[32];             //!< Busy-wait until reading produces non-zero value; write to release (see datasheet)
} cowpi_concurrency_t;


/* *** PERIPHERALS *** (see RP2040 datasheet, chapter 4) *** */

/**
 * @brief Structure to access the global microsecond timebase.
 * 
 * There is a single 64-bit time counter that increments every microsecond.
 * The 64-bit value can safely be assumed to never overflow unless you expect
 * your system to run for more than 584.5 thousand years.
 * The lower 32 bits, however, will overflow after about 71.6 minutes.
 * Reading from `lower_word` first will simultaneously latch the upper 32 bits
 * into `upper_word`, guaranteeing a consistent 64-bit value.
 * 
 * Reading from `raw_lower_word` and `raw_upper_word` does not offer this
 * behavior.
 */
typedef struct {
    uint32_t :32;                       //!< padding (write upper word)
    uint32_t :32;                       //!< padding (write lower word)
    uint32_t upper_word;                //!< Bits 63..32 of time (always read lower_word before upper_word)
    uint32_t lower_word;                //!< Bits 31..0 of time (always read lower_word before upper_word)
    uint32_t alarms[4];                 //!< Alarm will fire when lower_word == alarms[n]
    uint32_t alarm_status;              //!< Indicates whether alarm[n] is armed; also use to disarm alarm[n]
    uint32_t raw_upper_word;            //!< Bits 63..32 of time that can be read without side effects
    uint32_t raw_lower_word;            //!< Bits 31..0 of time that can be read without side effects
    uint32_t :32;                       //!< padding (debug pause)
    uint32_t pause;                     //!< Use to pause the counter
    // skip over the interrupt-related registers (for now?)
} cowpi_timer_t;

/**
 * @brief Structure for the SSP hardware (which we will use for SPI).
 * 
 * See RP2040 datasheet and ARM PrimeCell Synchronous Serial Port (PL022)
 * Technical Reference Manual (https://developer.arm.com/documentation/ddi0194/latest)
 * for configuration and use.
 */
typedef struct {
    uint64_t control;                   //!< SSP control register (upper word = SSPCR1; lower word = SSPCR0)
    uint16_t data;                      //!< SSP data register (SSPDR)
    uint16_t :16;                       //!< padding (unused upper half-word of SSPDR)
    uint32_t status;                    //!< SSP status register (SSPSR)
    uint32_t prescaler:8;               //!< SSP prescale register (SSPCPSR)
    uint32_t :24;                       //!< padding (unused bits 31..8 of SSPCSR)
    // skip over the interrupt-related registers (for now?)
} cowpi_spi_t;

/**
 * @brief Structure for the I2C (aka IIC) hardware.
 * 
 * See RP2040 datasheet for configuration and use.
 */
typedef struct {
    uint32_t control;                   //!< I2C control register (IC_CON)
    uint32_t target_address;            //!< I2C target address register (IC_TAR)
    uint32_t peripheral_address;        //!< I2C slave address register (IC_SAR)
    uint32_t :32;                       //!< padding (apparently unusued address)
    uint32_t data;                      //!< I2C data buffer and command register (IC_DATA_CMD)
    uint32_t standard_clock_high_count; //!< I2C standard speed SCL high Count register (IC_SS_SCL_HCNT)
    uint32_t standard_clock_low_count;  //!< I2C standard speed SCL low Count register (IC_SS_SCL_LCNT)
    uint32_t fast_clock_high_count;     //!< I2C fast speed SCL high Count register (IC_FS_SCL_HCNT)
    uint32_t fast_clock_low_count;      //!< I2C fast speed SCL low Count register (IC_FS_SCL_LCNT)
    uint32_t DO_NOT_TOUCH[0x50];        //!< padding (interrupt-related registers)
    uint32_t enable;                    //!< I2C enable register (IC_ENABLE)
    uint32_t status;                    //!< I2C status register (IC_STATUS)
    uint32_t tx_fifo_level;             //!< I2C transmit FIFO level register (IC_TXFLR)
    uint32_t rx_fifo_level;             //!< I2C receive FIFO level register (IC_RXFLR)
    // skip over the remaining registers (for now?)
} cowpi_i2c_t;

#endif //ARDUINO_ARCH_RP2040

#endif //COWPI_RP2040_H
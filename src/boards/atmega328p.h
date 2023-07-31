/**************************************************************************//**
 *
 * @file atmega328p.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Macros and constants for the ATmega328P microcontroller (Arduino Uno,
 *      Arduino Nano)
 *
 * This header provides the base address for memory-mapped I/O and
 * data structures to conveniently access the I/O registers.
 *
 * Possibly-useful memory-mapped registers:
 * | Use                                            | Datatype              | Memory Address                    |
 * |:----------------------------------------------:|:----------------------|:----------------------------------|
 * | External pins                                  | cowpi_ioport_t[3]     | 0x23 (index with named constants) |
 * | Pin-based interrupts                           | cowpi_pininterrupt_t  | 0x3B                              |
 * | SPI protocol                                   | cowpi_spi_t           | 0x4C                              |
 * | I2C protocol                                   | cowpi_i2c_t           | 0xB8                              |
 * | Timer0                                         | cowpi_timer8bit_t     | 0x44                              |
 * | Timer1                                         | cowpi_timer16bit_t    | 0x80                              |
 * | Timer2                                         | cowpi_timer8bit_t     | 0xB0                              |
 * | Timer interrupt masks (TIMSKx)                 | uint8_t[3]            | 0x6E (index with timer number)    |
 * | Timer interrupt flags (TIFRx)                  | uint8_t[3]            | 0x55 (index with timer number)    |
 * | General timer/counter control register (GTCCR) | uint8_t               | 0x43                              |
 * | Asynchronous Status Register (ASSR)            | uint8_t               | 0xB6                              |
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

#ifndef COWPI_ATMEGA328P_H
#define COWPI_ATMEGA328P_H

#ifdef __AVR_ATmega328P__

#define COWPI_USING_A_SUPPORTED_BOARD

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include "../setup/cowpi_setup.h"

/**
 * The memory address corresponding to the start of the
 * memory-mapped I/O registers.
 * 
 * @deprecated Use the absolute memory address instead of an offset from 
 * `COWPI_IO_BASE`
 */
#define COWPI_IO_BASE   ((uint8_t *) 0x20)


#define COWPI_PB  0                 //!< Index for arrays to access PINB/DDRB/PORTB and PCMSK0
#define D8_D13    0                 //!< Alias of COWPI_PB corresponding to pins D8-D13 on the Arduino Uno & Arduino Nano
#define COWPI_PC  1                 //!< Index for arrays to access PINC/DDRC/PORTC / PCMSK1
#define A0_A5     1                 //!< Alias of COWPI_PC for corresponding to pins D14-D19 (A0-A5) on the Arduino Uno & Arduino Nano
#define D14_D19   1                 //!< Alias of COWPI_PC for corresponding to pins D14-D19 (A0-A5) on the Arduino Uno & Arduino Nano
#define A0_A7     1                 //!< Alias of COWPI_PC for corresponding to pins D14-D19 (A0-A5) on the Arduino Uno & Arduino Nano
#define D14_D21   1                 //!< Alias of COWPI_PC for corresponding to pins D14-D19 (A0-A5) on the Arduino Uno & Arduino Nano
#define COWPI_PD  2                 //!< Index for arrays to access PIND/DDRD/PORTD and PCMSK2
#define D0_D7     2                 //!< Alias of COWPI_PD for corresponding to pins D0-D7 on the Arduino Uno & Arduino Nano


/**
 * @brief Structure for the general-purpose I/O pins.
 *
 * An array of these structures can be indexed using named constants
 * (COWPI_PB, etc).
 */
typedef struct {
    uint8_t input;                      //!< Read inputs from field (PINx)
    uint8_t direction;                  //!< Set the pin's direction using this field (DDRx)
    uint8_t output;                     //!< Write outputs to this field, and set/unset a pull-up resistor (PORTx)
} cowpi_ioport_t;

/**
 * @brief Structure for the SPI hardware.
 */
typedef struct {
    uint8_t control;                    //!< SPI control register (SPCR)
    uint8_t status;                     //!< SPI status register (SPSR)
    uint8_t data;                       //!< SPI data register (SPDR)
} cowpi_spi_t;

/**
 * @brief Structure for the TWI (aka I2C, IIC) hardware.
 */
typedef struct {
    uint8_t bit_rate;                   //!< TWI bit rate register, works in concert with status register (TWBR)
    uint8_t status;                     //!< TWI status register (TWSR)
    uint8_t address;                    //!< TWI peripheral address register (TWAR)
    uint8_t data;                       //!< TWI data register (TWBB)
    uint8_t control;                    //!< TWI control register(TWCR)
    uint8_t peripheral_address_mask;    //!< TWI peripheral address mask register (TWAMR)
} cowpi_i2c_t;

/**
 * @brief Structure for pin-based interrupts: pin change interrupts and external interrupts.
 */
typedef struct {
    uint8_t pci_flags;                  //!< Pin change interrupt flag register (PCIFR)
    uint8_t ei_flags;                   //!< External interrupt flag register (EIFR)
    uint8_t ei_mask;                    //!< External interrupt mask register (EIMSK)
    uint8_t DO_NOT_TOUCH[0x2A];         //!< padding
    uint8_t pci_control;                //!< Pin change interrupt control register (PCICR)
    uint8_t ei_control;                 //!< External interrupt control register (EICRA)
    uint8_t :8;                         //!< padding
    uint8_t pci_mask[3];                //!< Pin change mask registers -- index array using named constants (COWPI_PB, etc) (PCMSKx)
} cowpi_pininterrupt_t;

/**
 * @brief Structure for 8-bit timer/counter (TIMER0 or TIMER1).
 *
 * The timer/counter interrupt mask register (TIMSKx) and the timer/counter
 * interrupt flag register (TIFRx) are not part of this structure. Neither
 * are the asynchronous status register (ASSR) nor the general timer/counter
 * control register (GTCCR).
 */
typedef struct {
    uint16_t control;                   //!< Timer/counter control registers A & B; register A is the low-order byte (TCCRxB TCCRxA)
    uint8_t counter;                    //!< Timer/counter register (TCNTx)
    uint8_t compareA;                   //!< Output compare register A (OCRxA)
    uint8_t compareB;                   //!< Output compare register B (OCRxB)
} cowpi_timer8bit_t;

/**
 * @brief Structure for 16-bit timer/counter (TIMER1).
 *
 * The timer/counter interrupt mask register (TIMSKx) and the timer/counter
 * interrupt flag register (TIFRx) are not part of this structure. Does not
 * include the general timer/counter control register (GTCCR).
 */
typedef struct {
    uint32_t control;                 //!< Timer/counter control registers A, B, & C; register A is the low-order byte (Reserved TCCRxC TCCRxB TCCRxA)
    uint16_t counter;                 //!< Timer/counter register (TCNTxH TCNTxL, aka TCNTx)
    uint16_t capture;                 //!< Input capture register (ICRxH ICRxL, aka ICRx)
    uint16_t compareA;                //!< Output compare register A (OCRxAH OCRxAL, aka OCRxA)
    uint16_t compareB;                //!< Output compare register B (OCRxBH OCRxBL, aka OCRxB)
} cowpi_timer16bit_t;

#endif //__AVR_ATmega328P__

#endif //COWPI_ATMEGA328P_H

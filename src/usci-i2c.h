/** @file
 * Universal Serial Communication Interface - I2C
 *
 */

#ifndef MDL_MSP430_USCII2C_H
#define MDL_MSP430_USCII2C_H

#include <stdint.h>

#include "usci.h"

namespace mardev::msp430::usci::i2c
{
    namespace usci = mardev::msp430::usci;

    namespace registers
    {
        volatile uint16_t* const UCB0I2COA = (volatile uint16_t* const) 0x0118;
        volatile uint16_t* const UCB0I2CSA = (volatile uint16_t* const) 0x011A;

        namespace masks
        {
            // UCBxCTL0 control register 0
            const uint8_t UCA10   = 0b10000000;
            const uint8_t UCSLA10 = 0b01000000;
            const uint8_t UCMM    = 0b00100000;
            const uint8_t UCMST   = 0b00001000;
            const uint8_t UCMODE  = 0b00000110;
            const uint8_t UCSYNC  = 0b00000001;

            // UCBxCTL1 control register 1
            const uint8_t UCSSEL   = 0b11000000;
            const uint8_t UCTR     = 0b00010000;
            const uint8_t UCTXNACK = 0b00001000;
            const uint8_t UCTXSTP  = 0b00000100;
            const uint8_t UCTXSTT  = 0b00000010;
            const uint8_t UCSWRST  = 0b00000001;

            // UCBxSTAT status register
            const uint8_t UCSCLLOW  = 0b01000000;
            const uint8_t UCGC      = 0b00100000;
            const uint8_t UCBBUSTY  = 0b00010000;
            const uint8_t UCNACKIFG = 0b00001000;
            const uint8_t UCSTPIFG  = 0b00000100;
            const uint8_t UCSTTIFG  = 0b00000010;
            const uint8_t UCALIFG   = 0b00000001;
        }
    }

    enum class UCSSEL : uint8_t
    {
        UCLKI = 0,
        ACLK  = 1,
        SMCLK = 2
    };

    /** Reset the UCB0 module.
     */
    inline void reset()
    {
        *usci::registers::UCB0CTL0 |= registers::masks::UCSWRST;
        return;
    }

    /** Enable the UCB0 module for I2C.
     */
    inline void enable()
    {
        *usci::registers::UCB0CTL0 ^= 0b110;
        return;
    }

    /** Set the clock source.
     */
    inline void set_clock_source(const UCSSEL source)
    {
        *usci::registers::UCB0CTL1 =
            (*usci::registers::UCB0CTL1 ^ registers::masks::UCSSEL)
            | (uint8_t) source;

        return;
    }

    /** Use I2C transmitter mode.
     */
    inline void set_transmitter_mode()
    {
        *usci::registers::UCB0CTL1 |= registers::masks::UCTR;
        return;
    }

    /** Use I2C receiver mode.
     */
    inline void set_receiver_mode()
    {
        *usci::registers::UCB0CTL1 ^= registers::masks::UCTR;
        return;
    }

    void __send_signal(const uint8_t signal_mask);

    /** Synchronously send a NACK.
     */
    inline void nack() { __send_signal(registers::masks::UCTXNACK); }

    /** Synchronously send a STOP condition.
     */
    inline void stop() { __send_signal(registers::masks::UCTXSTP); }

    /** Synchronously send a START condition.
     */
    inline void start() { __send_signal(registers::masks::UCTXSTT); }
}

#endif

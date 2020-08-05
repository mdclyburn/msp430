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
            const uint8_t UCBBUSY  = 0b00010000;
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
     *
     * Readies the UCB0 module for I2C operation.
     * All configuration should be performed prior to calling this function.
     */
    inline void enable()
    {
        *usci::registers::UCB0CTL0 ^= 0b110;
        *usci::registers::UCB0CTL0 ^= registers::masks::UCSWRST;
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

    /** Set the divider for the bit clock.
     *
     * \param val Bit clock prescaler value.
     */
    inline void set_baud_control(const uint16_t val)
    {
        *usci::registers::UCB0BR0 = val & 0xFF;
        *usci::registers::UCB0BR1 = val >> 8;

        return;
    }

    /** Set the address of the peripheral.
     *
     * Sets the address of the peripheral to communicate with.
     * This should be done prior to initiating a read or write.
     *
     * \param address Address of the peripheral.
     */
    inline void set_periph_address(const uint8_t address)
    {
        *usci::registers::UCB0CTL0 ^= registers::masks::UCSLA10;
        *registers::UCB0I2CSA = address;
    }

    /** Set the 10-bit address of the peripheral.
     *
     * Sets the 10-bit address of the peripheral to communicate with.
     * This should be done prior to inititating a read or write.
     *
     * \param address Address of the peripheral.
     */
    inline void set_periph_address10(const uint16_t address)
    {
        *usci::registers::UCB0CTL0 |= registers::masks::UCSLA10;
        *registers::UCB0I2CSA = address;
    }

    inline void __send_signal(const uint8_t signal_mask) { *usci::registers::UCB0CTL1 |= signal_mask; }

    inline void __nack() { __send_signal(registers::masks::UCTXNACK); }

    /** Issue a stop condition.
     */
    inline void __stop() { __send_signal(registers::masks::UCTXSTP); }

    /** Issue a start condition.
     */
    inline void __start() { __send_signal(registers::masks::UCTXSTT); }

    /** Change to transmitter mode.
     */
    inline void __tx_mode() { *usci::registers::UCB0CTL1 |= registers::masks::UCTR; }

    /** Change to receiver mode.
     */
    inline void __rx_mode() { *usci::registers::UCB0CTL1 ^= registers::masks::UCTR; }

    /** Returns true if the I2C clock signal is held low.
     */
    inline bool __clock_is_low() { return *usci::registers::UCB0STAT & registers::masks::UCSCLLOW; }

    /** Returns true if the general call address is received.
     */
    inline bool __general_addr_called() { return *usci::registers::UCB0STAT & registers::masks::UCGC; }

    /** Returns true if the I2C bus is busy.
     */
    inline bool __is_busy() { return *usci::registers::UCB0STAT & registers::masks::UCBBUSY; }

    /** Returns true if a NACK was received.
     */
    inline bool __nack_received() { return *usci::registers::UCB0STAT & registers::masks::UCNACKIFG; }

    /** Returns true if a stop condition was received.
     */
    inline bool __stop_received() { return *usci::registers::UCB0STAT & registers::masks::UCSTPIFG; }

    /** Returns true if a start condition was received.
     */
    inline bool __start_received() { return *usci::registers::UCB0STAT & registers::masks::UCSTTIFG; }

    /** Returns true if arbitration process was lost.
     */
    inline bool __arbitration_lost() { return *usci::registers::UCB0STAT & registers::masks::UCALIFG; }

    /** Returns true if the start condition is being generated.
     */
    inline bool __generating_start() { return *usci::registers::UCB0CTL1 & registers::masks::UCTXSTT; }

    /** Returns true if the transmission buffer is empty.
     */
    inline bool __tx_buffer_empty() { return *interrupt::registers::IFG2 & usci::registers::masks::UCB0TXIFG; }

    /** Returns true if the reception buffer is holding a byte.
     */
    inline bool __rx_buffer_full() { return *interrupt::registers::IFG2 & usci::registers::masks::UCB0RXIFG; }

    /** Start a read from a peripheral.
     *
     * The peripheral address needs to be set prior.
     * See set_periph_address() or set_periph_address10().
     *
     * \returns True if reception is ready to begin.
     */
    bool read_begin();

    /** Read a byte from the peripheral.
     *
     * Synchronously reads a byte from the peripheral.
     * A read must have been started with read_begin() before calling this function.
     *
     * \returns Byte read from the peripheral.
     */
    uint8_t read();

    /** End a read from a peripheral.
     *
     * Generates a stop condition to end a read.
     * \returns The last byte read from the peripheral.
     */
    uint8_t read_end();

    /** Start a write to a peripheral.
     *
     * The peripheral address needs to be set.
     * See set_periph_address() and set_periph_address10().
     *
     * \returns True if transmission is ready to begin.
     */
    bool write_begin();

    /** Write a byte to the peripheral.
     *
     * Synchronously writes a byte to the peripheral.
     * A write must have been started with write_begin() before calling this function.
     */
    void write(const uint8_t data);

    /** End a write from a peripheral.
     */
    inline void write_end() { __stop(); }
}

#endif

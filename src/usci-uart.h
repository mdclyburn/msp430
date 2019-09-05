/** @file
 *
 * Universal Serial Communication Interface - Universal Asynchronous Receiver-Transmitter (UART)
 */

#ifndef MDL_MSP430_USCI_UART_H
#define MDL_MSP430_USCI_UART_H

#include "digital-io.h"
#include "usci.h"

namespace mardev::msp430::usci::uart
{
    namespace dio = mardev::msp430::digital_io;
    namespace usci = mardev::msp430::usci;

    namespace registers::masks
    {
        // Control register 0
        const uint8_t UCPEN   = 0b10000000;
        const uint8_t UCPAR   = 0b01000000;
        const uint8_t UCMSB   = 0b00100000;
        const uint8_t UC7BIT  = 0b00010000;
        const uint8_t UCSPB   = 0b00001000;
        const uint8_t UCMODEx = 0b00000110;
        const uint8_t UCSYNC  = 0b00000001;

        // Control register 1
        const uint8_t UCSSELx  = 0b11000000;
        const uint8_t UCRXEIE  = 0b00100000;
        const uint8_t UCBRKIE  = 0b00010000;
        const uint8_t UCDORM   = 0b00001000;
        const uint8_t UCTXADDR = 0b00000100;
        const uint8_t UCTXBRK  = 0b00000010;
        const uint8_t UCSWRST  = 0b00000001;

        // UCAxSTAT Status register masks
        const uint8_t UCLISTEN = 0b10000000;
        const uint8_t UCFE     = 0b01000000;
        const uint8_t UCOE     = 0b00100000;
        const uint8_t UCPE     = 0b00010000;
        const uint8_t UCBRK    = 0b00001000;
        const uint8_t UCRXERR  = 0b00000100;
        const uint8_t UCADDR   = 0b00000010;
        const uint8_t UCIDLE   = 0b00000010;
        const uint8_t UCBUSY   = 0b00000001;

        // Modulation control register
        const uint8_t UCBRFx = 0b11110000;
        const uint8_t UCBRSx = 0b00001110;
        const uint8_t UCOS16 = 0b00000001;
    }

    /** USCI UART Modules */
    enum class Module : uint8_t
    {
        A0 = 0
    };

    /** Asynchronous USCI mode select */
    enum class UCMODE : uint8_t
    {
        UART                     = 0x00,
        IdleLineMultiprocessor   = 0x01 << 1,
        AddressBitMultiprocessor = 0x02 << 1,
        UARTAutoBaud             = 0x03 << 1
    };

    /** USCI clock source select */
    enum class UCSSELx : uint8_t
    {
        UCLK  = 0x00,
        ACLK  = 0x01 << 6,
        SMCLK = 0x02 << 6
    };

    // Mapping module -> pin number
    extern const uint8_t RXD[];
    extern const uint8_t TXD[];

    /** Reset the USCI module.
     *
     * \param module USCI module to reset.
     */
    inline void reset(const Module module)
    {
        volatile uint8_t* const ctl1 = usci::registers::CTL1[(uint8_t) module];
        *ctl1 |= usci::registers::masks::UCSWRST;
    }

    /** Enable the USCI module for use as a UART.
     *
     * Performs final configuration of the USCI module to be use as a UART.
     * Configures the module's pins in the correct pin function and resets the software reset bit.
     * This function should only be called once other configurations have been performed.
     *
     * \param module USCI module to enable for UART.
     */
    inline void enable(const Module module)
    {
        volatile uint8_t* const ctl0 = usci::registers::CTL0[(uint8_t) module];
        *ctl0 &= ~usci::registers::masks::UCSYNC;

        const uint8_t pin_rxd = RXD[(uint8_t) module];
        const uint8_t pin_txd = TXD[(uint8_t) module];
        dio::set_pin_mode(pin_rxd, dio::IO::Input, dio::Function::Secondary);
        dio::set_pin_mode(pin_txd, dio::IO::Output, dio::Function::Secondary);

        volatile uint8_t* const ctl1 = usci::registers::CTL1[(uint8_t) module];
        *ctl1 &= ~usci::registers::masks::UCSWRST;
    }

    /** Sets the UART mode.
     *
     * \param module USCI module the configure.
     * \param mode Desired UART mode.
     */
    inline void set_mode(const Module module,
                         const UCMODE mode)
    {
        volatile uint8_t* r = usci::registers::CTL0[(uint8_t) module];
        *r = *r & ~(0x03 << 1) | (uint8_t) mode;
    }

    /** Set the UART bit clock source.
     *
     * \param module USCI module to configure.
     * \param source Clock to use for the bit clock.
     */
    inline void set_clock_source(const Module module,
                                 const UCSSELx source)
    {
        volatile uint8_t* r = usci::registers::CTL1[(uint8_t) module];
        *r = *r & ~(0x03 << 6) | (uint8_t) source;
    }

    /** Enable or disable the use of the parity bit.
     *
     * Turns on or off the use of a parity bit in UART communications.
     * By default (and if enabled), the parity is odd parity.
     * Use enable_even_parity() to use even parity.
     *
     * \param module USCI module to configure.
     * \param enabled Whether to use a parity bit.
     */
    inline void enable_parity(const Module module,
                              const bool enabled)
    {
        volatile uint8_t* r = usci::registers::CTL0[(uint8_t) module];
        *r = *r & ~registers::masks::UCPEN;
        if (enabled) *r |= registers::masks::UCPEN;
    }

    /** Use even parity.
     *
     * This function will be necessary if the peripheral uses even parity.
     * \param module USCI module to configure.
     */
    inline void enable_even_parity(const Module module)
    {
        volatile uint8_t* r = usci::registers::CTL0[(uint8_t) module];
        *r |= registers::masks::UCPAR;
    }

    /** Use odd parity.
     *
     * This function is only necessary if the parity was set to even parity prior without a call to reset().
     *
     * \param module USCI module to configure.
     */
    inline void enable_odd_parity(const Module module)
    {
        volatile uint8_t* r = usci::registers::CTL0[(uint8_t) module];
        *r &= ~registers::masks::UCPAR;
    }

    /** Set the divider for the bit clock.
     *
     * See documentation for the correct value to use.
     *
     * \param module USCI module to configure.
     * \param val Divider value to use.
     */
    inline void set_baud_control(const Module module,
                                 const uint16_t val)
    {
        volatile uint8_t* br = usci::registers::BR0[(uint8_t) module];

        // This assumption holds until it doesn't.
        br[0] = (uint8_t) (val & 0xFF);
        br[1] = (uint8_t) (val >> 8);
    }

    /** Set bit clock modulation parameters.
     *
     * See documentation for the correct values to use.
     * The first_stage value is only used when enable_oversampling is true.
     *
     * \param module USCI module to configure.
     * \param first_stage First stage value.
     * \param second_stage Second stage value.
     * \param enable_oversampling Use oversampling.
     */
    inline void set_modulation(const Module module,
                                  const uint8_t first_stage,
                                  const uint8_t second_stage,
                                  const bool enable_oversampling)
    {
        volatile uint8_t* const mctl = usci::registers::MCTL[(uint8_t) module];
        uint8_t config = (first_stage << 4) | (second_stage << 1);
        if(enable_oversampling)
            config |= 1;
        *mctl = config;
    }

    /** Returns true if an error bit is set.
     *
     * Returns true if a read encountered a parity, framing, or overrun error or a break condition.
     * \param module USCI module to check.
     */
    inline bool errors(const Module module)
    {
        volatile uint8_t* const stat = usci::registers::STAT[(uint8_t) module];
        return *stat
            & (registers::masks::UCFE
               | registers::masks::UCPE
               | registers::masks::UCBRK
               | registers::masks::UCOE);
    }

    /** Clear status errors.
     *
     * \param module USCI module to clear errors for.
     */
    inline void clear_errors(const Module module)
    {
        volatile uint8_t* const stat = usci::registers::STAT[(uint8_t) module];
        volatile const uint8_t* const rx = usci::registers::RXBUF[(uint8_t) module];

        *stat ^=
            registers::masks::UCFE
            | registers::masks::UCPE
            | registers::masks::UCBRK;
        if (*stat & registers::masks::UCOE)
            *rx;
    }

    /** Returns true if the receive buffer has a new character.
     *
     * \param module USCI module to query.
     */
    inline bool has_data(const Module module)
    {
        return *interrupt::registers::IFG2 & usci::registers::masks::RXIFG[(uint8_t) module];
    }

    /** Synchronously read a character from UART.
     *
     * Read a character from the UART receive buffer.
     * If no character is ready to be retrieved, this function blocks until one is.
     * It is more likely to be convenient to use the overload of this function only requiring the USCI module.
     *
     * \param status_register Address of the USCI module's status register.
     * \param rx_buffer Address of the USCI module's status register.
     * \param rx_flag_mask Interrupt flag mask signalling a character is ready.
     */
    inline uint8_t read(volatile const uint8_t* const status_register,
                        volatile const uint8_t* const rx_buffer,
                        const uint8_t rx_flag_mask)
    {
        while(!(*status_register & registers::masks::UCRXERR)
              && !(*interrupt::registers::IFG2 & rx_flag_mask));
        return *rx_buffer;
    }

    /** Synchronously read a character from UART.
     *
     * Read a character from the UART receive buffer.
     * If no character is ready to be retrieved, this function blocks until one is.
     *
     * \param module USCI module to read a character from.
     */
    uint8_t read(const Module module);

    /** Synchronously read a number of characters from UART.
     *
     * Reads the specified number of characters from the UART.
     * Blocks until the max_length is reached.
     *
     * \param module USCI module to read a character from.
     * \param buffer Buffer to write read characters to.
     * \param max_length Number of characters to read into the buffer.
     */
    uint16_t read(const Module module,
                  uint8_t* const buffer,
                  const uint16_t max_length);

    /** Synchronously write characters to the UART.
     *
     * \param module USCI module to write characters to.
     * \param data Data to be written.
     * \param length Number of bytes to write.
     */
    void write(const Module module,
               const uint8_t* const data,
               const uint16_t length);

    /** Indefinitely wait until UART is idle.
     *
     * Waits for the specified delay and checks for errors in the UART.
     * If errors are detected (peripheral transmitted something), clears them and restarts the wait.
     *
     * \param module USCI module to await an idle state for.
     * \param delay Milliseconds of idle time necessary to satisfy the condition.
     */
    void wait_for_idle(const Module module,
                       const uint16_t delay);
}

#endif

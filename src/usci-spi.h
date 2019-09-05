/** @file
 *
 * Universal Serial Communication Interface - Serial Peripheral Interface (SPI)
 */

#ifndef MDL_MSP430_USCISPI_H
#define MDL_MSP430_USCISPI_H

#include <stdint.h>

#include "usci.h"

namespace mardev::msp430::usci::spi
{
    namespace usci = mardev::msp430::usci;

    namespace registers::masks
    {
        const uint8_t UCCKPH = 0b10000000;
        const uint8_t UCCKPL = 0b01000000;
        const uint8_t UCMSB  = 0b00100000;
        const uint8_t UC7BIT = 0b00010000;
        const uint8_t UCMST  = 0b00001000;
        const uint8_t UCMODE = 0b00000110;
        const uint8_t UCSYNC = 0b00000001;

        const uint8_t UCSSEL  = 0b11000000;
        const uint8_t UCSWRST = 0b00000001;
    }

    /** SPI module */
    enum class Module : uint8_t
    {
        A0 = 0,
        B0 = 1
    };

    /** USCI mode select */
    enum class UCMODE : uint8_t
    {
        SPI3     = 0x00,
        SPI4High = 0x01 << 1,
        SPI4Low  = 0x02 << 1,
        I2C      = 0x03 << 1
    };

    /** Clock phase select
     *
     * This is backwards from the spec.
     */
    enum class UCCKPH : uint8_t
    {
        P0 = 0x80,
        P1 = 0x00
    };

    /** Clock polarity select */
    enum class UCCKPL : uint8_t
    {
        P0 = 0x00,
        P1 = 0x40
    };

    /** Endianness select */
    enum class UCMSB : uint8_t
    {
        LSBFirst = 0x00,
        MSBFirst = 0x20
    };

    /** Character length select
     *
     * Currently, this enum's values get translated into 0x12.
     * Not sure if this is a bug, but it isn't wholly important right now.
     */
    enum class UC7BIT : uint8_t
    {
        L8 = 0x00,
        L7 = 0x10
    };

    /** Master/Slave mode select */
    enum class UCMST : uint8_t
    {
        Slave =  0x00,
        Master = 0x08
    };

    /** Clock source select */
    enum class UCSSEL : uint8_t
    {
        NA     = 0x00,
        ACLK   = 0x40,
        SMCLK  = 0x80
    };

    // Mapping module -> pin number
    extern const uint8_t SCLK[];
    extern const uint8_t MOSI[];
    extern const uint8_t MISO[];

    inline volatile uint8_t* const get_ctl0(const Module m)
    {
        return usci::registers::CTL0[(uint8_t) m];
    }

    inline volatile uint8_t* const get_ctl1(const Module m)
    {
        return usci::registers::CTL1[(uint8_t) m];
    }

    inline void reset(const Module m)
    {
        *get_ctl1(m) |= usci::UCSWRST;
        return;
    }

    void enable(const Module m);

    inline void set_mode(const Module m,
                         const UCMODE spi_mode)
    {
        auto ctl0 = get_ctl0(m);
        *ctl0 = (*ctl0 & ~registers::masks::UCMODE) | (uint8_t) spi_mode;

        return;
    }

    inline void set_clock_source(const Module m,
                                 const UCSSEL source)
    {
        volatile uint8_t* const ctl0 = get_ctl0(m);
        *ctl0 = (*ctl0 & ~registers::masks::UCSSEL) | (uint8_t) source;

        return;
    }

    inline void set_clock_phase(const Module m,
                                const UCCKPH phase)
    {
        volatile uint8_t* const ctl0 = get_ctl0(m);
        *ctl0 = (*ctl0 & ~registers::masks::UCCKPH) | (uint8_t) phase;

        return;
    }

    inline void set_clock_polarity(const Module m,
                                   const UCCKPL polarity)
    {
        volatile uint8_t* const ctl0 = get_ctl0(m);
        *ctl0 = (*ctl0 & ~registers::masks::UCCKPL) | (uint8_t) polarity;

        return;
    }

    inline void set_bit_endianness(const Module m,
                                   const UCMSB endianness)
    {
        volatile uint8_t* const ctl0 = get_ctl0(m);
        *ctl0 = (*ctl0 & ~registers::masks::UCMSB) | (uint8_t) endianness;

        return;
    }

    /** Send data over SPI.
     *
     * Sends a byte over the SPI interface.
     * An empty transmit buffer will be awaited and written to once empty.
     * A received character will be awaited.
     *
     * \param module SPI module to send data with.
     * \param data Data to be sent over SPI.
     */
    uint8_t write(const Module module,
                  const uint8_t data);
}

#endif

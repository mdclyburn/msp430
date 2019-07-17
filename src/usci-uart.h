#ifndef MDL_MSP430_USCI_UART_H
#define MDL_MSP430_USCI_UART_H

#include "usci.h"

namespace mardev::msp430::usci::uart
{
    namespace usci = mardev::msp430::usci;

    const uint8_t UCSSEL = 0x03 << 6;

    /** Parity enable */
    enum class UCPEN : uint8_t
    {
        Disabled = 0x00,
        Enabled  = 0x80
    };

    /** Parity select */
    enum class UCPAR : uint8_t
    {
        Odd  = 0x00,
        Even = 0x40
    };

    /** Bit-endianness select */
    enum class UCMSB : uint8_t
    {
        LSBFirst = 0x00,
        MSBFirst = 0x20
    };

    /** Character length */
    enum class UC7BIT : uint8_t
    {
        L8 = 0x00,
        L7 = 0x10
    };

    /** Number of stop bits */
    enum class UCSPB : uint8_t
    {
        B1 = 0x00,
        B2 = 0x08
    };

    /** Asynchronous USCI mode select */
    enum class UCMODE0 : uint8_t
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

    inline void reset(const usci::Module module)
    {
        volatile uint8_t* const ctl1 = usci::registers::CTL1[(uint8_t) module];
        *ctl1 |= usci::UCSWRST;
    }

    inline void enable(const usci::Module module)
    {
        volatile uint8_t* const ctl1 = usci::registers::CTL1[(uint8_t) module];
        *ctl1 &= ~usci::UCSWRST;
    }

    void initialize(const usci::Module module,
                    const UCMODE0 mode,
                    const UCSSELx clock_source,
                    const UCPEN parity_enable,
                    const UCPAR parity,
                    const UCMSB first_bit,
                    const UC7BIT character_length,
                    const UCSPB stop_bits);
}

#endif

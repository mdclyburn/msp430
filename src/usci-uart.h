#ifndef MDL_MSP430_USCI_UART_H
#define MDL_MSP430_USCI_UART_H

namespace mardev::msp430::usci::uart
{
    namespace usci = mardev::msp430::usci;

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
}

#endif

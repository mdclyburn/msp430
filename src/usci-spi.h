#ifndef MDL_MSP430_USCISPI_H
#define MDL_MSP430_USCISPI_H

#include <stdint.h>

#include "usci.h"

using namespace mardev::msp430::usci;

namespace mardev::msp430::usci::spi
{
    // USCI control register 0 masks for SPI
    const uint8_t _UCCKPH  = 0x80;
    const uint8_t _UCCKPL  = 0x40;
    const uint8_t _UCMSB   = 0x20;
    const uint8_t _UC7BIT  = 0x10;
    const uint8_t _UCMST   = 0x08;
    const uint8_t _UCSYNC  = 0x01;

    /** Clock phase select */
    enum class UCCKPH : uint8_t
    {
        P0 = 0x00,
        P1 = 0x80
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

    /** Character length select */
    enum class UC7BIT : uint8_t
    {
        L8 = 0x00,
        L7 = 0x10
    };

    /** Master/Slave mode select */
    enum class UCMST : uint8_t
    {
        Slave =  0x00,
        Master = 0x04
    };

    /* initialize()
     * optionally set 3- or 4-pin mode?
     * set clock phase
     * set clock polarity
     * set bit direction
     * set character length: 7- or 8-bit
     * enable synchronous mode (required = 1)
     * set clock
     * clear the software reset enable bit
     */
}

#endif

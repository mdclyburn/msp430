/** @file
 *
 * USCI Serial Peripheral Interface functions
 */

#ifndef MDL_MSP430_USCISPI_H
#define MDL_MSP430_USCISPI_H

#include <stdint.h>

#include "usci.h"

namespace mardev::msp430::usci::spi
{
    namespace usci = mardev::msp430::usci;

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
        Master = 0x08
    };

    /** Clock source select */
    enum class UCSSELx : uint8_t
    {
        NA     = 0x00,
        ACLK   = 0x40,
        SMCLK  = 0x80
    };

    // Mapping module -> pin number
    extern const uint8_t SCLK[];
    extern const uint8_t MOSI[];
    extern const uint8_t MISO[];

    void initialize(const usci::Module module,
                    const usci::UCMODE spi_mode,
                    const UCSSELx clock_source,
                    const UCCKPH clock_phase,
                    const UCCKPL clock_polarity,
                    const UCMSB first_bit,
                    const UC7BIT character_length);

    uint8_t write(const usci::Module,
                  const uint8_t data);
}

#endif

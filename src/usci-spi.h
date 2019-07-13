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

    /** Initialize an SPI module.
     *
     * Perform initialization steps to prepare an SPI module for use.
     * This includes configuring the pins correctly.
     *
     * \param module USCI module to set up for SPI.
     * \param spi_mode SPI mode to set up (3-pin, 4-pin).
     * \param clock_source Where to source the clock signal from.
     * \param clock_polarity SPI clock's idle state.
     *                       See documentation for the peripheral being interfaced with for the correct value.
     * \param clock_phase SPI interface bit capture and change setting.
     *                       See documentation for the peripheral being interfaced with for the correct value.
     *                       Note that UCCKPH uses CPHA = 0 for UCCKPH::P0 (correcting MSP430's setting).
     * \param first_bit Set the bit orientation of data.
     */
    void initialize(const usci::Module module,
                    const usci::UCMODE spi_mode,
                    const UCSSELx clock_source,
                    const UCCKPH clock_phase,
                    const UCCKPL clock_polarity,
                    const UCMSB first_bit);

    /** Reset the SPI module settings.
     *
     * After this function is called, initialize() must be called to use the provided SPI module again.
     * An SPI module cannot be used after it is placed in the reset state.
     *
     * \param module SPI module to reset.
     */
    inline void reset(const usci::Module module)
    {
        *usci::registers::CTL1[(uint8_t) module] |= usci::UCSWRST;
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
    uint8_t write(const usci::Module module,
                  const uint8_t data);
}

#endif

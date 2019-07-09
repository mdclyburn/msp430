#ifndef MDL_MSP430_CLOCK_H
#define MDL_MSP430_CLOCK_H

#include <stdint.h>

namespace mardev::msp430::clock
{
    namespace registers
    {
        volatile uint8_t* const DCOCTL  = (volatile uint8_t* const) 0x0056;
        volatile uint8_t* const BCSCTL1 = (volatile uint8_t* const) 0x0057;
        volatile uint8_t* const BCSCTL2 = (volatile uint8_t* const) 0x0058;
        volatile uint8_t* const BCSCTL3 = (volatile uint8_t* const) 0x0053;
    }

    const uint8_t BCSCTL1_XT2OFF  = 0x80;
    const uint8_t BCSCTL1_XTS     = 0x40;
    const uint8_t BCSCTL1_DIVAx   = 0x30;

    const uint8_t BCSCTL3_LFXT1Sx = 0x30;

    /** Divider for ACLK (BCSCTL1) */
    enum class DIVAx : uint8_t
    {
        D1 = 0x00, // /1
        D2 = 0x10, // /2
        D3 = 0x20, // /4
        D4 = 0x30  // /8
    };

    /** Low-frequency clock select (BCSCTL3) */
    enum class LFXT1S : uint8_t
    {
        Crystal32768 = 0x00, // Crystal on LFXT1
        VLOCLK       = 0x20, // VLOCLK, low-frequency oscillator
        External     = 0x30  // Digital, external clock source
    };

    /** Calibration data addresses for the DCO and BCS+.
     *
     * This data is available for all 2xx devices at the same addresses in the TLV in information memory.
     */
    enum class DCOPreset : uint16_t
    {
        C16 = 0x10F6 + 2,
        C12 = 0x10F6 + 4,
        C8 =  0x10F6 + 6,
        C1 =  0x10F6 + 8
    };

    /** Load a preset for the DCO and BCS+.
     *
     * \param preset Preset to use.
     */
    inline void apply_dco_preset(const DCOPreset preset)
    {
        const uint16_t* const loc = (const uint16_t*) preset;
        *registers::DCOCTL = *loc;
        *registers::BCSCTL1 = *(loc + 1);
    }

    /** Set the source for the auxiliary clock signal.
     *
     * \param selected_clock Clock source to use.
     */
    inline void set_auxiliary_source(const LFXT1S source)
    {
        *registers::BCSCTL3 =
            *registers::BCSCTL3
            & ~BCSCTL3_LFXT1Sx
            | ((uint8_t) source);
    }

    /** Divide the auxiliary clock.
     *
     * \param divider Divider value to use.
     */
    inline void set_auxiliary_divider(const DIVAx divider)
    {
        *registers::BCSCTL1 =
            *registers::BCSCTL1
            & ~BCSCTL1_DIVAx
            | ((uint8_t) divider);
    }

    /** Configure the auxiliary clock.
     *
     * \param source Clock signal source.
     * \param divider Divider to divide the source signal.
     */
    inline void configure_auxiliary_clock(const LFXT1S source,
                                          const DIVAx divider)
    {
        set_auxiliary_source(source);
        set_auxiliary_divider(divider);
    }
}

#endif

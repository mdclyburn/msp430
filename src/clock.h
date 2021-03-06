/** @file
 *
 * Basic Clock Module+
 */

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

        namespace masks
        {
            // BCSCTL1
            const uint8_t XT2OFF  = 0b10000000;
            const uint8_t XTS     = 0b01000000;
            const uint8_t DIVAx   = 0b00110000;

            // BCSCTL2
            const uint8_t SELS    = 0b00001000;
            const uint8_t DIVSx   = 0b00000110;
            const uint8_t LFXT1Sx = 0b00110000;
        }
    }

    /** Divider for ACLK (BCSCTL1) */
    enum class DIVAx : uint8_t
    {
        D1 = 0b00000000, // /1
        D2 = 0b00010000, // /2
        D3 = 0b00100000, // /4
        D4 = 0b00110000  // /8
    };

    /** Sub-system master clock select (BCSCTL2) */
    enum class SELS : uint8_t
    {
        DCOCLK     = 0b00000000, // Source from DCO.
        XT2_LFXT1S = 0b00000001  // XT2CLK if XT2 osc., otherwise, whatever LFXT1S selects.
    };

    /** Sub-system master clock divider (BCSCTL2) */
    enum class DIVS : uint8_t
    {
        D1 = 0b00000000,
        D2 = 0b00000010,
        D4 = 0b00000100,
        D8 = 0b00000110
    };

    /** Low-frequency clock select (BCSCTL3) */
    enum class LFXT1S : uint8_t
    {
        Crystal32768 = 0b00000000, // Crystal on LFXT1
        VLOCLK       = 0b00100000, // VLOCLK, low-frequency oscillator
        External     = 0b00110000  // Digital, external clock source
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
        const uint8_t* const preset_tlv_loc = (const uint8_t*) preset;
        const uint8_t dco_preset_calibration = preset_tlv_loc[0];
        const uint8_t bcs_preset_calibration = preset_tlv_loc[1];

        *registers::DCOCTL = dco_preset_calibration;
        *registers::BCSCTL1 = bcs_preset_calibration;
    }

    /** Set the source for the sub-system master clock signal.
     *
     * \param source Source to use.
     */
    inline void set_smclock_source(const SELS source)
    {
        *registers::BCSCTL2 =
            *registers::BCSCTL2
            & ~registers::masks::SELS
            | ((uint8_t) source);
    }

    /** Divide the sub-system main clock.
     *
     * \param divider Divider value to use.
     */
    inline void set_smclock_divider(const DIVS divider)
    {
        *registers::BCSCTL2 =
            *registers::BCSCTL2
            & ~registers::masks::DIVSx
            | ((uint8_t) divider);
    }

    /** Configure the sub-system main clock.
     *
     * \param source Source to use.
     * \param divider Divider value to use.
     */
    inline void configure_smclock(const SELS source,
                                  const DIVS divider)
    {
        set_smclock_source(source);
        set_smclock_divider(divider);
    }

    /** Set the source for the auxiliary clock signal.
     *
     * \param selected_clock Clock source to use.
     */
    inline void set_auxiliary_source(const LFXT1S source)
    {
        *registers::BCSCTL3 =
            *registers::BCSCTL3
            & ~registers::masks::LFXT1Sx
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
            & ~registers::masks::DIVAx
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

    inline bool lfxt1_oscillator_fault()
    {
        return *registers::BCSCTL3 & 1;
    }
}

#endif

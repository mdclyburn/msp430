#ifndef MDL_MSP430_CLOCK_H
#define MDL_MSP430_CLOCK_H

namespace mardev
{
    namespace msp430
    {
        namespace clock
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

            // Calibration data for the DCO and BCS+ is available for all 2xx devices
            // at the same addresses in the TLV in information memory.
            enum class dco_preset : uint16_t
            {
                c16 = 0x10F6 + 2,
                c12 = 0x10F6 + 4,
                c8 =  0x10F6 + 6,
                c1 =  0x10F6 + 8
            };

            enum class lfxt1s : uint8_t
            {
                crystal32768 = 0x00,
                vlo_clock    = 0x20,
                external     = 0x30
            };

            enum class diva : uint8_t
            {
                d1 = 0x00,
                d2 = 0x10,
                d3 = 0x20,
                d4 = 0x30
            };

            inline void apply_dco_preset(const dco_preset p)
            {
                const uint8_t* const preset_location = (const uint8_t* const) p;
                *registers::DCOCTL = *preset_location;
                *registers::BCSCTL1 = *(preset_location + 1);
            }

            inline void set_auxiliary_source(const lfxt1s s)
            {
                const uint8_t val = (uint8_t) s;
                *registers::BCSCTL3 &= ~BCSCTL3_LFXT1Sx | ((uint8_t) s);
            }

            inline void set_auxiliary_divider(const diva d)
            {
                *registers::BCSCTL1 &= ~BCSCTL1_DIVAx | ((uint8_t) d);
            }
        }
    }
}

#endif

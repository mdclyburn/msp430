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

            // Calibration data for the DCO and BCS+ is available for all 2xx devices
            // at the same addresses in the TLV in information memory.
            const uint8_t* const preset_16mhz = (const uint8_t* const) 0x10F6 + 2;
            const uint8_t* const preset_12mhz = (const uint8_t* const) 0x10F6 + 4;
            const uint8_t* const preset_8mhz  = (const uint8_t* const) 0x10F6 + 6;
            const uint8_t* const preset_1mhz  = (const uint8_t* const) 0x10F6 + 8;

            enum class preset : uint16_t
            {
                c16 = 0x10F6 + 2,
                c12 = 0x10F6 + 4,
                c8 =  0x10F6 + 6,
                c1 =  0x10F6 + 8
            };

            inline void use_preset(const preset p)
            {
                const uint8_t* const preset_location = (const uint8_t* const) p;
                *registers::DCOCTL = *preset_location;
                *registers::BCSCTL1 = *(preset_location + 1);
            }
        }
    }
}

#endif

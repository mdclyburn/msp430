#ifndef MDL_MSP430_DIGITAL_IO_H
#define MDL_MSP430_DIGITAL_IO_H

#include <stdint.h>

namespace mardev
{
    namespace msp430
    {
        extern const uint8_t* pin_port;
        extern const uint8_t* pin_port_mask;

        enum class pin_mode : uint8_t
        {
            output = 0,
            input_pullup = 1,
            input_pulldown = 2
        };

        void set_pin_mode(const uint8_t pin_number,
                          const pin_mode mode);
    }
}


#endif

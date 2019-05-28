#ifndef MDL_MSP430_DIGITAL_IO_H
#define MDL_MSP430_DIGITAL_IO_H

#include <stdint.h>

namespace mardev
{
    namespace msp430
    {
        extern const uint8_t* pin_port;
        extern const uint8_t* pin_port_mask;

        void set_digital_input(const uint8_t pin_number);
    }
}


#endif

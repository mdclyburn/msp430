#include "digital-io.h"

namespace mardev
{
    namespace msp430
    {
        namespace digital_io
        {
            // Pin number to IO port.
            // 0 = pin is not attached to a digital IO port.
            #ifdef MDL_MSP430G2553
            uint8_t* const port_input[]            = { (uint8_t* const) 0x20, (uint8_t* const) 0x28 };
            uint8_t* const port_output[]           = { (uint8_t* const) 0x21, (uint8_t* const) 0x29 };
            uint8_t* const port_direction[]        = { (uint8_t* const) 0x22, (uint8_t* const) 0x2A };
            uint8_t* const port_interrupt_flag[]   = { (uint8_t* const) 0x23, (uint8_t* const) 0x2B };
            uint8_t* const port_interrupt_edge[]   = { (uint8_t* const) 0x24, (uint8_t* const) 0x2C };
            uint8_t* const port_interrupt_enable[] = { (uint8_t* const) 0x25, (uint8_t* const) 0x2D };
            uint8_t* const port_select[]           = { (uint8_t* const) 0x26, (uint8_t* const) 0x2E };
            uint8_t* const port_select_2[]         = { (uint8_t* const) 0x41, (uint8_t* const) 0x42 };
            uint8_t* const port_resistor_enable[]  = { (uint8_t* const) 0x27, (uint8_t* const) 0x2F };

            const uint8_t pin_port[] = {
                0, 1, 1, 1, 1,
                1, 1, 2, 2, 2,
                2, 2, 2, 1, 1,
                0, 0, 2, 2, 0
            };

            const uint8_t pin_port_mask[] = {
                0,
                1,
                2,
                4,
                8,
                16,
                32,
                1,
                2,
                4,

                8,
                16,
                32,
                64,
                128,
                0,
                0,
                128,
                64,
                0
            };
            #endif

            void set_pin_mode(const uint8_t pin_number,
                              const pin_mode mode)
            {
                const uint8_t port = pin_port[pin_number];
                const uint8_t port_mask = pin_port_mask[pin_number];

                // Set input or output.
                if(mode == pin_mode::output)
                    *port_direction[port] |= port_mask;
                else
                    *port_direction[port] &= ~port_mask;

                // Enable the internal resistor.
                if(mode != pin_mode::output)
                    *port_resistor_enable[port] |= port_mask;

                // Select the digital IO function.
                *port_select[port] &= ~port_mask;
                *port_select_2[port] &= ~port_mask;

                // Set output value.
                if(mode == pin_mode::input_pullup)
                    *port_output[port] |= port_mask;
                else // Pull-down or set output to low.
                    *port_output[port] &= ~port_mask;

                return;
            }
        }
    }
}

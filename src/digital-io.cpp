#include "digital-io.h"

namespace mardev
{
    namespace msp430
    {
        namespace digital_io
        {
            // Pin number to IO port.
            volatile uint8_t* const port_input[]            = { registers::P1IN,   registers::P2IN };
            volatile uint8_t* const port_output[]           = { registers::P1OUT,  registers::P2OUT };
            volatile uint8_t* const port_direction[]        = { registers::P1DIR,  registers::P2DIR };
            volatile uint8_t* const port_interrupt_flag[]   = { registers::P1IFG,  registers::P2IFG };
            volatile uint8_t* const port_interrupt_edge[]   = { registers::P1IES,  registers::P2IES };
            volatile uint8_t* const port_interrupt_enable[] = { registers::P1IE,   registers::P2IES };
            volatile uint8_t* const port_select[]           = { registers::P1SEL,  registers::P2SEL };
            volatile uint8_t* const port_select_2[]         = { registers::P1SEL2, registers::P2SEL2 };
            volatile uint8_t* const port_resistor_enable[]  = { registers::P1REN,  registers::P2REN };

            // 0 = pin is not attached to a digital IO port.
            const uint8_t pin_port[] = {
                0, 1, 1, 1, 1, 1, 1, 2, 2, 2,
                2, 2, 2, 1, 1, 0, 0, 2, 2, 0
            };

            // 0 = pin is not attached to a digital IO port.
            const uint8_t pin_port_mask[] = {
                0,
                1 << 0,
                1 << 1,
                1 << 2,
                1 << 3,
                1 << 4,
                1 << 5,
                1 << 0,
                1 << 1,
                1 << 2,

                1 << 3,
                1 << 4,
                1 << 5,
                1 << 6,
                1 << 7,
                0,
                0,
                1 << 7,
                1 << 6,
                0
            };

            void set_pin_mode(const uint8_t pin_number,
                              const pin_mode mode)
            {
                const uint8_t port = pin_port[pin_number-1] - 1;
                const uint8_t port_mask = pin_port_mask[pin_number-1];

                if(port == 0) return;

                // Set input or output.
                if(mode == pin_mode::output)
                    *port_direction[port] |= port_mask;
                else
                    *port_direction[port] &= ~port_mask;

                // Enable the internal resistor.
                if(mode != pin_mode::output)
                    *port_resistor_enable[port] |= port_mask;
                else
                    *port_resistor_enable[port] &= ~port_mask;

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

            bool read(const uint8_t pin_number)
            {
                return *port_input[pin_port[pin_number]] &= pin_port_mask[pin_number];
            }

            void write(const uint8_t pin_number,
                       const logic level)
            {
                const uint8_t port = pin_port[pin_number-1] - 1;
                const uint8_t port_mask = pin_port_mask[pin_number-1];
                if(level == logic::high)
                    *port_output[port] |= port_mask;
                else
                    *port_output[port] &= ~port_mask;

                return;
            }
        }
    }
}

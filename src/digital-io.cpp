#include "digital-io.h"

namespace mardev::msp430::digital_io
{
    // Pin number to IO port.
    volatile uint8_t* const port_input[]            = { registers::P1IN,   registers::P2IN };
    volatile uint8_t* const port_output[]           = { registers::P1OUT,  registers::P2OUT };
    volatile uint8_t* const port_direction[]        = { registers::P1DIR,  registers::P2DIR };
    volatile uint8_t* const port_interrupt_flag[]   = { registers::P1IFG,  registers::P2IFG };
    volatile uint8_t* const port_interrupt_edge[]   = { registers::P1IES,  registers::P2IES };
    volatile uint8_t* const port_interrupt_enable[] = { registers::P1IE,   registers::P2IE };
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
                      const IO direction,
                      const Function func)
    {
        const uint8_t port = get_pin_port(pin_number);
        if(port == 0) // Guard against not-a-pin.
        {
            return;
        }
        const uint8_t port_mask = get_pin_port_mask(pin_number);

        if(port_mask == 0)
        {
            /** Sanity check against incorrect pin number to port mask mapping.
             * Something is wrong with the library code if this gets hit.
             */
            return;
        }

        // Set input or output.
        if(direction == IO::Output)
            *port_direction[port] |= port_mask;
        else
            *port_direction[port] &= ~port_mask;

        // Set pin function.
        switch(func)
        {
        case Function::IO: // Select the digital IO function.
            *port_select[port] &= ~port_mask;
            *port_select_2[port] &= ~port_mask;
            break;
        case Function::Primary: // Select primary peripheral module function.
            *port_select[port] |= port_mask;
            *port_select_2[port] &= ~port_mask;
            break;
        case Function::Special: // Reserved. This is a device-specific setting.
            *port_select[port] &= ~port_mask;
            *port_select_2[port] |= port_mask;
            break;
        case Function::Secondary: // Select secondary peripheral module function.
            *port_select[port] |= port_mask;
            *port_select_2[port] |= port_mask;
            break;
        }

        return;
    }

    void configure_resistor(const uint8_t pin_number, const bool enabled)
    {
        const uint8_t port = get_pin_port(pin_number);
        const uint8_t mask = get_pin_port_mask(pin_number);

        if(enabled)
            *port_resistor_enable[port] |= mask;
        else
            *port_resistor_enable[port] &= ~mask;

        return;
    }

    void enable_interrupts(const uint8_t pin_number, const Logic trigger)
    {
        const uint8_t port = get_pin_port(pin_number);
        const uint8_t mask = get_pin_port_mask(pin_number);

        if(trigger == Logic::Low) // Falling edge.
            *port_interrupt_edge[port] |= mask;
        else
            *port_interrupt_edge[port] &= ~mask;

        *port_interrupt_enable[port] |= mask;

        return;
    }

    void disable_interrupts(const uint8_t pin_number)
    {
        const uint8_t port = get_pin_port(pin_number);
        const uint8_t mask = get_pin_port_mask(pin_number);

        *port_interrupt_enable[port] &= ~mask;

        return;
    }

    bool read(const uint8_t pin_number)
    {
        return *port_input[get_pin_port(pin_number)] &= get_pin_port_mask(pin_number);
    }

    void write(const uint8_t pin_number,
               const Logic level)
    {
        const uint8_t port = get_pin_port(pin_number);
        const uint8_t port_mask = get_pin_port_mask(pin_number);
        if(level == Logic::High)
            *port_output[port] |= port_mask;
        else
            *port_output[port] &= ~port_mask;

        return;
    }
}

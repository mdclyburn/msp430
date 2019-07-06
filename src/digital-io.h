#ifndef MDL_MSP430_DIGITAL_IO_H
#define MDL_MSP430_DIGITAL_IO_H

#include <stdint.h>

namespace mardev::msp430::digital_io
{
    namespace registers
    {
        // Port 1
        volatile uint8_t* const P1IN =   (volatile uint8_t* const) 0x20;
        volatile uint8_t* const P1OUT =  (volatile uint8_t* const) 0x21;
        volatile uint8_t* const P1DIR =  (volatile uint8_t* const) 0x22;
        volatile uint8_t* const P1IFG =  (volatile uint8_t* const) 0x23;
        volatile uint8_t* const P1IES =  (volatile uint8_t* const) 0x24;
        volatile uint8_t* const P1IE  =  (volatile uint8_t* const) 0x25;
        volatile uint8_t* const P1SEL =  (volatile uint8_t* const) 0x26;
        volatile uint8_t* const P1SEL2 = (volatile uint8_t* const) 0x41;
        volatile uint8_t* const P1REN =  (volatile uint8_t* const) 0x27;

        // Port 2
        volatile uint8_t* const P2IN =   (volatile uint8_t* const) 0x28;
        volatile uint8_t* const P2OUT =  (volatile uint8_t* const) 0x29;
        volatile uint8_t* const P2DIR =  (volatile uint8_t* const) 0x2A;
        volatile uint8_t* const P2IFG =  (volatile uint8_t* const) 0x2B;
        volatile uint8_t* const P2IES =  (volatile uint8_t* const) 0x2C;
        volatile uint8_t* const P2IE  =  (volatile uint8_t* const) 0x2D;
        volatile uint8_t* const P2SEL =  (volatile uint8_t* const) 0x2E;
        volatile uint8_t* const P2SEL2 = (volatile uint8_t* const) 0x42;
        volatile uint8_t* const P2REN =  (volatile uint8_t* const) 0x2F;
    }

    /** Mapping from pin number to port number */
    extern const uint8_t pin_port[];

    /** Mapping from pin number to bit mask. */
    extern const uint8_t pin_port_mask[];

    enum class pin_mode
    {
        output,
        input_pullup,
        input_pulldown
    };

    enum class logic
    {
        high,
        low
    };

    /** Set the mode for a pin.
     *
     * \param pin_number Pin number.
     * \param mode Desired mode.
     */
    void set_pin_mode(const uint8_t pin_number,
                      const pin_mode mode);

    /** Read the digital signal on a pin.
     *
     * \param pin_number Pin number.
     */
    bool read(const uint8_t pin_number);

    /** Output a high or low signal on a pin.
     *
     * \param pin_number Pin number.
     * \param level Signal to output.
     */
    void write(const uint8_t pin_number,
               const logic level);
}

#endif

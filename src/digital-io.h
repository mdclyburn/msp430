/**
 * @file
 *
 * Digital I/O
 *
 * Manipulates digital I/O.
 * Each pin can be configured for input or output with set_pin_mode().
 * Many pins are multiplexed with other modules and can be manually set to support those modules here as well.
 */

#ifndef MDL_MSP430_DIGITAL_IO_H
#define MDL_MSP430_DIGITAL_IO_H

#include <stdint.h>

namespace mardev::msp430::digital_io
{
    namespace registers
    {
        // ===== Port 1
        volatile uint8_t* const P1IN =   (volatile uint8_t* const) 0x20;
        volatile uint8_t* const P1OUT =  (volatile uint8_t* const) 0x21;
        volatile uint8_t* const P1DIR =  (volatile uint8_t* const) 0x22;
        volatile uint8_t* const P1IFG =  (volatile uint8_t* const) 0x23;
        volatile uint8_t* const P1IES =  (volatile uint8_t* const) 0x24;
        volatile uint8_t* const P1IE  =  (volatile uint8_t* const) 0x25;
        volatile uint8_t* const P1SEL =  (volatile uint8_t* const) 0x26;
        volatile uint8_t* const P1SEL2 = (volatile uint8_t* const) 0x41;
        volatile uint8_t* const P1REN =  (volatile uint8_t* const) 0x27;

        // ===== Port 2
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

    /** Mapping from pin number to port number. */
    extern const uint8_t pin_port[];

    /** Mapping from pin number to bit mask. */
    extern const uint8_t pin_port_mask[];

    /** Pin digital input or output specifier. */
    enum class IO
    {
        Input,
        Output
    };

    /** Pin function specifier.
     * IO is for digital I/O.
     * Primary is for the pin's primary function.
     * Special is either a reserved setting or specific to the microcontroller.
     * Secondary is for the pin's secondary function.
     */
    enum class Function : uint8_t
    {
        IO = 0,
        Primary = 1,
        Special = 2,
        Secondary = 3
    };

    /** Digital high and low. */
    enum class Logic
    {
        High,
        Low
    };

    /** Return port number mapping index for a pin.
     *
     * Returns the index of the port number in the pin to port number mapping.
     *
     * \param pin_number Pin number.
     */
    inline uint8_t get_pin_port(const uint8_t pin_number)
    {
        return pin_port[pin_number-1] - 1;
    }

    /** Return the port mask mapping index for a pin.
     *
     * Returns the index of the port mask in the pin to port mask mapping.
     *
     * \param pin_number Pin number.
     */
    inline uint8_t get_pin_port_mask(const uint8_t pin_number)
    {
        return  pin_port_mask[pin_number-1];
    }

    /** Set the mode for a pin.
     *
     * \param pin_number Pin number.
     * \param direction Desired mode.
     * \param func Selected module function.
     */
    void set_pin_mode(const uint8_t pin_number,
                      const IO mode,
                      const Function func);

    /** Set the mode for a pin.
     *
     * \param pin_number Pin number.
     * \param direction Desired mode.
     */
    inline void set_pin_mode(const uint8_t pin_number,
                             const IO direction)
    {
        set_pin_mode(pin_number, direction, Function::IO);
    }

    /** Enable or disable pin's internal resistor.
     *
     * \param pin_number Pin number.
     * \param enabled Whether the internal resistor is enabled.
     */
    void configure_resistor(const uint8_t pin_number,
                            const bool enabled);

    /** Enable interrupts for a pin.
     *
     * \param pin_number Pin number.
     * \param Edge select; Logic::High is triggered on a rising edge, Logic::Low on a falling edge
     */
    void enable_interrupts(const uint8_t pin_number,
                           const Logic trigger);

    /** Disable interrupts for a pin.
     *
     * \param pin_number Pin number.
     */
    void disable_interrupts(const uint8_t pin_number);

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
               const Logic level);
}

#endif

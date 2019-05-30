#ifndef MDL_MSP430_DIGITAL_IO_H
#define MDL_MSP430_DIGITAL_IO_H

#include <stdint.h>

namespace mardev
{
    namespace msp430
    {
        namespace digital_io
        {
            extern const uint8_t pin_port[];
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
    }
}


#endif

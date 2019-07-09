#include "usci.h"
#include "usci-spi.h"

namespace mardev::msp430::usci::spi
{
    void initialize(const usci::Module module,
                    const usci::UCMODE spi_mode,
                    const UCSSELx clock_source,
                    const UCCKPH clock_phase,
                    const UCCKPL clock_polarity,
                    const UCMSB first_bit,
                    const UC7BIT character_length)
    {
        volatile  uint8_t* const ctl0 = usci::registers::CTL0[(uint8_t)module],
            * ctl1 = usci::registers::CTL1[(uint8_t)module];

        *ctl0 = (uint8_t) clock_phase
            | (uint8_t) clock_polarity
            | (uint8_t) first_bit
            | (uint8_t) character_length
            | 1 << 4 // Assume master mode
            | (uint8_t) spi_mode
            | 1; // Synchronous mode enable

        *ctl1 = (uint8_t) clock_source
            | usci::UCSWRST;

        return;
    }
}

#include "digital-io.h"
#include "usci-uart.h"

namespace mardev::msp430::usci::uart
{
    namespace dio = mardev::msp430::digital_io;

    const uint8_t RXD[] = { 3 };
    const uint8_t TXD[] = { 4 };

    void initialize(const usci::Module module,
                    const UCMODE0 mode,
                    const UCSSELx clock_source,
                    const UCPEN parity_enable,
                    const UCPAR parity,
                    const UCMSB first_bit,
                    const UC7BIT character_length,
                    const UCSPB stop_bits,
                    const uint16_t baud_control,
                    const uint8_t modulation_setting)
    {
        volatile uint8_t* const ctl0 = usci::registers::CTL0[(uint8_t) module];
        volatile uint8_t* const ctl1 = usci::registers::CTL1[(uint8_t) module];
        volatile uint8_t* const br0  = usci::registers::BR0[(uint8_t) module];
        volatile uint8_t* const br1  = usci::registers::BR1[(uint8_t) module];
        volatile uint8_t* const mctl = usci::registers::MCTL[(uint8_t) module];

        reset(module);

        *ctl0 = (uint8_t) parity_enable
            | (uint8_t) parity
            | (uint8_t) first_bit
            | (uint8_t) character_length
            | (uint8_t) stop_bits
            | (uint8_t) mode;
        *ctl1 = (*ctl1 & ~UCSSEL) | (uint8_t) clock_source;
        *br0 = (uint8_t) (baud_control >> 8);
        *br1 = (uint8_t) (baud_control & 0xFF);
        *mctl = modulation_setting;

        const uint8_t pin_rxd = RXD[(uint8_t) module];
        const uint8_t pin_txd = TXD[(uint8_t) module];
        dio::set_pin_mode(pin_rxd, dio::IO::Input, dio::Function::Secondary);
        dio::set_pin_mode(pin_txd, dio::IO::Output, dio::Function::Secondary);

        enable(module);

        return;
    }
}

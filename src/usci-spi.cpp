#include "digital-io.h"
#include "interrupt.h"
#include "usci.h"
#include "usci-spi.h"

namespace dio = mardev::msp430::digital_io;
namespace interrupt = mardev::msp430::interrupt;

namespace mardev::msp430::usci::spi
{
    const uint8_t SCLK[] = { 6, 7 };
    const uint8_t MOSI[] = { 4, 15 };
    const uint8_t MISO[] = { 3, 14 };

    void initialize(const usci::Module module,
                    const usci::UCMODE spi_mode,
                    const UCSSELx clock_source,
                    const UCCKPH clock_phase,
                    const UCCKPL clock_polarity,
                    const UCMSB first_bit,
                    const UC7BIT character_length)
    {
        volatile uint8_t* const
            ctl0 = usci::registers::CTL0[(uint8_t)module],
            * ctl1 = usci::registers::CTL1[(uint8_t)module];

        *ctl1 |= usci::UCSWRST;

        const uint8_t pin_clock = SCLK[(uint8_t) module],
            pin_mosi = MOSI[(uint8_t) module],
            pin_miso = MISO[(uint8_t) module];

        // Configure pins.
        dio::set_pin_mode(pin_clock, dio::pin_mode::output, dio::Function::Secondary);
        dio::set_pin_mode(pin_mosi, dio::pin_mode::output, dio::Function::Secondary);
        dio::set_pin_mode(pin_miso, dio::pin_mode::input, dio::Function::Secondary);

        *ctl1 |= (uint8_t) clock_source;

        *ctl0 = (uint8_t) clock_phase
            | (uint8_t) clock_polarity
            | (uint8_t) first_bit
            // | (uint8_t) character_length // <- something about this sets the wrong bits
            | (uint8_t) UCMST::Master // Assume master mode
            | (uint8_t) spi_mode
            | 1; // Synchronous mode enable

        *ctl1 &= ~usci::UCSWRST;

        return;
    }

    uint8_t write(const usci::Module module,
                  const uint8_t data)
    {
        // Wait for the buffer to be ready.
        const uint8_t tx_flag = usci::TXIFG[(uint8_t) module];
        while(!(*interrupt::registers::IFG2 & tx_flag));

        // Write data out.
        volatile uint8_t* const tx_buffer = usci::registers::TXBUF[(uint8_t) module];
        *tx_buffer = data;

        // Wait for data to be ready.
        const uint8_t rx_flag = usci::RXIFG[(uint8_t) module];
        while(!(*interrupt::registers::IFG2 & rx_flag));
        volatile const uint8_t* const rx_buffer = usci::registers::RXBUF[(uint8_t) module];
        return *rx_buffer;
    }
}
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

    void enable(const Module m)
    {
        // Configure pins.
        dio::set_pin_mode(SCLK[(uint8_t) m], dio::IO::Output, dio::Function::Secondary);
        dio::set_pin_mode(MOSI[(uint8_t) m], dio::IO::Output, dio::Function::Secondary);
        dio::set_pin_mode(MISO[(uint8_t) m], dio::IO::Output, dio::Function::Secondary);

        auto ctl0 = get_ctl0(m);
        auto ctl1 = get_ctl1(m);

        // Assume master mode, ensure synchronous mode.
        *ctl0 |= (uint8_t) UCMST::Master | (uint8_t) usci::UCSYNC;
        *ctl1 &= ~usci::UCSWRST;

        return;
    }

    uint8_t write(const Module module,
                  const uint8_t data)
    {
        volatile const uint8_t tx_flag = usci::TXIFG[(uint8_t) module];
        volatile const uint8_t rx_flag = usci::RXIFG[(uint8_t) module];
        volatile uint8_t* const tx_buffer = usci::registers::TXBUF[(uint8_t) module];
        volatile const uint8_t* const rx_buffer = usci::registers::RXBUF[(uint8_t) module];

        // Wait for the buffer to be ready.
        while(!(*interrupt::registers::IFG2 & tx_flag));

        // Write data out.
        *tx_buffer = data;

        // Wait for data to be ready.
        while(!(*interrupt::registers::IFG2 & rx_flag));

        return *rx_buffer;
    }
}

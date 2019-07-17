#include "digital-io.h"
#include "interrupt.h"
#include "usci-uart.h"

namespace mardev::msp430::usci::uart
{
    namespace dio = mardev::msp430::digital_io;

    const uint8_t UCBRK  = 0x08;
    const uint8_t UCIDLE = 0x02;

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

        *ctl0 = 0;
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

    void write(const usci::Module module,
               const uint8_t* const data,
               const uint16_t length)
    {
        volatile uint8_t* const tx_buffer = usci::registers::TXBUF[(uint8_t) module];
        const uint8_t tx_flag = usci::TXIFG[(uint8_t) module];

        uint16_t transmitted_bytes = 0;
        while(transmitted_bytes < length)
        {
            // Wait for buffer to empty.
            while(!(*interrupt::registers::IFG2 & tx_flag));
            *tx_buffer = data[transmitted_bytes++];
        }

        return;
    }

    uint16_t read(const usci::Module module,
                  uint8_t* const buffer,
                  const uint16_t max_length)
    {
        volatile const uint8_t* const status = usci::registers::STAT[(uint8_t) module];
        volatile const uint8_t* const rx_buffer = usci::registers::RXBUF[(uint8_t) module];
        const uint8_t rx_flag = usci::RXIFG[(uint8_t) module];

        // Receive data until idle.
        uint16_t len = 0;
        uint8_t* out = buffer;
        do
        {
            // Wait for input from peripheral.
            while(!(*interrupt::registers::IFG2 & rx_flag));

            *(out + len) = *rx_buffer;
            len++;
        } while(!(*status & UCBRK));

        return len;
    }
}

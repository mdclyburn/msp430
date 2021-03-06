#include "digital-io.h"
#include "interrupt.h"
#include "timer.h"
#include "usci-uart.h"

namespace mardev::msp430::usci::uart
{
    namespace dio = mardev::msp430::digital_io;

    // USCI UART pin mapping
    const uint8_t RXD[] = { 3 };
    const uint8_t TXD[] = { 4 };

    uint8_t read(const Module module)
    {
        volatile const uint8_t* const status = usci::registers::STAT[(uint8_t) module];
        volatile const uint8_t* const rx_buffer = usci::registers::RXBUF[(uint8_t) module];
        const uint8_t rx_flag = usci::registers::masks::RXIFG[(uint8_t) module];

        read(status, rx_buffer, rx_flag);

        return *rx_buffer;
    }

    uint16_t read(const uart::Module module,
                  uint8_t* const buffer,
                  const uint16_t max_length)
    {
        volatile const uint8_t* const status = usci::registers::STAT[(uint8_t) module];
        volatile const uint8_t* const rx_buffer = usci::registers::RXBUF[(uint8_t) module];
        const uint8_t rx_flag = usci::registers::masks::RXIFG[(uint8_t) module];

        uint16_t len = 0;
        do
        {
            buffer[len++] = read(status, rx_buffer, rx_flag);
        } while(len < max_length);

        return len;
    }

    void write(const uart::Module module,
               const uint8_t* const data,
               const uint16_t length)
    {
        volatile uint8_t* const tx_buffer = usci::registers::TXBUF[(uint8_t) module];
        const uint8_t tx_flag = usci::registers::masks::TXIFG[(uint8_t) module];

        uint16_t transmitted_bytes = 0;
        while(transmitted_bytes < length)
        {
            // Wait for buffer to empty.
            while(!(*interrupt::registers::IFG2 & tx_flag));
            *tx_buffer = data[transmitted_bytes++];
        }

        return;
    }

    void wait_for_idle(const uart::Module module,
                       const uint16_t count,
                       const uint16_t ticks_per_count)
    {
        while(true)
        {
            timer::delay(count, ticks_per_count, timer::TASSEL::ACLK);
            if(errors(module))
                clear_errors(module);
            else
                break;
        }

        return;
    }
}

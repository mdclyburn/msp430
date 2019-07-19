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

    void write(const uart::Module module,
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

    uint16_t read(const uart::Module module,
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
        } while(len < max_length);

        return len;
    }
}

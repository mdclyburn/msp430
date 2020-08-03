#include "usci-i2c.h"

namespace mardev::msp430::usci::i2c
{
    namespace usci = mardev::msp430::usci;

    void __send_signal(const uint8_t signal_mask)
    {
        *usci::registers::UCB0CTL1 |= signal_mask;
        while(*usci::registers::UCB0CTL1 & signal_mask);

        return;
    }

    void __send(const uint8_t* const buffer,
                const uint8_t length)
    {
        for(uint8_t i = 0; i < length; i++)
        {
            *usci::registers::UCB0TXBUF = buffer[i];
            // TODO: transmission error handling
            while(!(*interrupt::registers::IFG2 & usci::registers::masks::UCB0TXIFG));
        }
    }
}

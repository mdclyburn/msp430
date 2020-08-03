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
}

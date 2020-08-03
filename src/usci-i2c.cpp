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

    void read_begin()
    {
        set_receiver_mode();
        start();

        return;
    }

    uint8_t read()
    {
        while(!(*interrupt::registers::IFG2
                & usci::registers::masks::UCB0RXIFG));
        return *usci::registers::UCB0RXBUF;
    }

    void write_begin()
    {
        set_transmitter_mode();
        start();

        return;
    }

    void write(const uint8_t data)
    {
        *usci::registers::UCB0TXBUF = data;
        while(!(*interrupt::registers::IFG2
                & usci::registers::masks::UCB0TXIFG));

        return;
    }
}

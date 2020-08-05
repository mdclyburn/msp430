#include "usci-i2c.h"

namespace mardev::msp430::usci::i2c
{
    namespace usci = mardev::msp430::usci;

    bool read_begin()
    {
        __rx_mode();
        __start();
        while(__generating_start());

        // Reception starts without any other intervention.
        // Checking UCTXNACK will discern an issue with communication.
        if(__nack_received())
        {
            __stop();
            return false;
        }
        else
        {
            return true;
        }
    }

    uint8_t read()
    {
        while(!__rx_buffer_full());
        return *usci::registers::UCB0RXBUF;
    }

    uint8_t read_end()
    {
        __stop();
        return read();
    }

    bool write_begin()
    {
        // Set transmit mode and generate the start condition.
        __tx_mode();
        __start();

        // Wait to be ACKed or NACKed.
        while(__generating_start());

        if(*interrupt::registers::IFG2 & usci::registers::masks::UCB0TXIFG)
        {
            return true;
        }
        else
        {
            __stop();
            return false;
        }
    }

    void write(const uint8_t data)
    {
        *usci::registers::UCB0TXBUF = data;
        while(!__tx_buffer_empty());

        return;
    }
}

#include "usci-i2c.h"

namespace mardev::msp430::usci::i2c
{
    namespace usci = mardev::msp430::usci;

    bool read_begin()
    {
        // Set receive mode and generate the start condition.
        *usci::registers::UCB0CTL1 ^= registers::masks::UCTR;
        __start();

        // Wait to be ACKed or NACKed.
        while(*usci::registers::UCB0CTL1 & registers::masks::UCTXSTT);

        // Read starts without any other intervention.
        // Checking UCTXNACK will discern an issue with communication.
        if(*usci::registers::UCB0STAT ^ registers::masks::UCNACKIFG)
        {
            return true;
        }
        else
        {
            __stop();
            return false;
        }
    }

    uint8_t read()
    {
        while(!(*interrupt::registers::IFG2
                & usci::registers::masks::UCB0RXIFG));
        return *usci::registers::UCB0RXBUF;
    }

    uint8_t read_end()
    {
        __stop();
        return *usci::registers::UCB0RXBUF;
    }

    bool write_begin()
    {
        // Set transmit mode and generate the start condition.
        *usci::registers::UCB0CTL1 |= registers::masks::UCTR;
        __start();

        // Wait to be ACKed or NACKed.
        while(*usci::registers::UCB0CTL1 & registers::masks::UCTXSTT);

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
        while(!(*interrupt::registers::IFG2
                & usci::registers::masks::UCB0TXIFG));

        return;
    }
}

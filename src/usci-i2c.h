#ifndef MDL_MSP430_USCII2C_H
#define MDL_MSP430_USCII2C_H

#include <stdint.h>

#include "usci.h"

namespace mardev::msp430::usci::i2c
{
    namespace usci = mardev::msp430::usci;

    namespace registers
    {
        const uint16_t* UCB0I2COA = (const uint16_t*) 0x0118;
        const uint16_t* UCB0I2CSA = (const uint16_t*) 0x011A;

        namespace masks
        {
            // UCBxCTL0 control register 0
            const uint8_t UCA10   = 0b10000000;
            const uint8_t UCSLA10 = 0b01000000;
            const uint8_t UCMM    = 0b00100000;
            const uint8_t UCMST   = 0b00001000;
            const uint8_t UCMODE  = 0b00000110;
            const uint8_t UCSYNC  = 0b00000001;

            // UCBxCTL1 control register 1
            const uint8_t UCSSEL   = 0b11000000;
            const uint8_t UCTR     = 0b00010000;
            const uint8_t UCTXNACK = 0b00001000;
            const uint8_t UCTXSTP  = 0b00000100;
            const uint8_t UCTXSTT  = 0b00000010;
            const uint8_t UCSWRST  = 0b00000001;

            // UCBxSTAT status register
            const uint8_t UCSCLLOW  = 0b01000000;
            const uint8_t UCGC      = 0b00100000;
            const uint8_t UCBBUSTY  = 0b00010000;
            const uint8_t UCNACKIFG = 0b00001000;
            const uint8_t UCSTPIFG  = 0b00000100;
            const uint8_t UCSTTIFG  = 0b00000010;
            const uint8_t UCALIFG   = 0b00000001;
        }
    }
}

#endif

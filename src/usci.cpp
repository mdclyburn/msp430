#include "usci.h"

namespace mardev::msp430::usci
{
    namespace registers
    {
        uint8_t* const CTL0[] =  { UCA0CTL0, UCB0CTL0 };
        uint8_t* const CTL1[] =  { UCA0CTL1, UCB0CTL1 };

        uint8_t* const BR0[]  =  { UCA0BR0, UCB0BR0 };
        uint8_t* const BR1[]  =  { UCA0BR1, UCB0BR1 };

        uint8_t* const STAT[] =  { UCA0STAT, UCB0STAT };

        const uint8_t* const RXBUF[] = { UCA0RXBUF, UCB0RXBUF };
        uint8_t* const TXBUF[] =       { UCA0TXBUF, UCB0TXBUF };
    }
}

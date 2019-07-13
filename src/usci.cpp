#include "usci.h"

namespace mardev::msp430::usci
{
    namespace registers
    {
        volatile uint8_t* const CTL0[] =  { UCA0CTL0, UCB0CTL0 };
        volatile uint8_t* const CTL1[] =  { UCA0CTL1, UCB0CTL1 };

        volatile uint8_t* const BR0[]  =  { UCA0BR0, UCB0BR0 };
        volatile uint8_t* const BR1[]  =  { UCA0BR1, UCB0BR1 };

        volatile uint8_t* const STAT[] =  { UCA0STAT, UCB0STAT };

        const volatile uint8_t* const RXBUF[] = { UCA0RXBUF, UCB0RXBUF };
        volatile uint8_t* const TXBUF[] =       { UCA0TXBUF, UCB0TXBUF };
    }

    const uint8_t RXIE[]  = { UCA0RXIE, UCB0RXIE };
    const uint8_t TXIE[]  = { UCA0TXIE, UCB0TXIE };
    const uint8_t RXIFG[] = { UCA0RXIFG, UCB0RXIFG };
    const uint8_t TXIFG[] = { UCA0TXIFG, UCB0TXIFG };
}

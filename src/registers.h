#ifndef MDL_MSP430_REGISTERS_H
#define MDL_MSP430_REGISTERS_H

namespace mardev
{
    namespace msp430
    {
        namespace reg
        {
            // ===== SFR
            volatile uint8_t* const IE1  = (volatile uint8_t* const) 0x00;
            volatile uint8_t* const IFG1 = (volatile uint8_t* const) 0x02;

            // ===== Clock
            volatile uint8_t* const DCOCTL  = (volatile uint8_t* const) 0x0056;
            volatile uint8_t* const BCSCTL1 = (volatile uint8_t* const) 0x0057;
            volatile uint8_t* const BCSCTL2 = (volatile uint8_t* const) 0x0058;
            volatile uint8_t* const BCSCTL3 = (volatile uint8_t* const) 0x0053;

            // ===== Digital I/O
            // Port 1
            volatile uint8_t* const P1IN =   (volatile uint8_t* const) 0x20;
            volatile uint8_t* const P1OUT =  (volatile uint8_t* const) 0x21;
            volatile uint8_t* const P1DIR =  (volatile uint8_t* const) 0x22;
            volatile uint8_t* const P1IFG =  (volatile uint8_t* const) 0x23;
            volatile uint8_t* const P1IES =  (volatile uint8_t* const) 0x24;
            volatile uint8_t* const P1IE  =  (volatile uint8_t* const) 0x25;
            volatile uint8_t* const P1SEL =  (volatile uint8_t* const) 0x26;
            volatile uint8_t* const P1SEL2 = (volatile uint8_t* const) 0x41;
            volatile uint8_t* const P1REN =  (volatile uint8_t* const) 0x27;

            // Port 2
            volatile uint8_t* const P2IN =   (volatile uint8_t* const) 0x28;
            volatile uint8_t* const P2OUT =  (volatile uint8_t* const) 0x29;
            volatile uint8_t* const P2DIR =  (volatile uint8_t* const) 0x2A;
            volatile uint8_t* const P2IFG =  (volatile uint8_t* const) 0x2B;
            volatile uint8_t* const P2IES =  (volatile uint8_t* const) 0x2C;
            volatile uint8_t* const P2IE  =  (volatile uint8_t* const) 0x2D;
            volatile uint8_t* const P2SEL =  (volatile uint8_t* const) 0x2E;
            volatile uint8_t* const P2SEL2 = (volatile uint8_t* const) 0x42;
            volatile uint8_t* const P2REN =  (volatile uint8_t* const) 0x2F;

            // ===== Watchdog Timer+
            volatile uint16_t* const WDTCTL = (volatile uint16_t* const) 0x0120;
        }
    }
}

#endif

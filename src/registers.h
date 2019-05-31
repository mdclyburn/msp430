#ifndef MDL_MSP430_REGISTERS_H
#define MDL_MSP430_REGISTERS_H

namespace mardev
{
    namespace msp430
    {
        namespace reg
        {
            // ===== Digital I/O
            // Port 1
            uint16_t* const P1IN =   (uint16_t* const) 0x0020;
            uint16_t* const P1OUT =  (uint16_t* const) 0x0021;
            uint16_t* const P1DIR =  (uint16_t* const) 0x0022;
            uint16_t* const P1IFG =  (uint16_t* const) 0x0023;
            uint16_t* const P1IES =  (uint16_t* const) 0x0024;
            uint16_t* const P1IE  =  (uint16_t* const) 0x0025;
            uint16_t* const P1SEL =  (uint16_t* const) 0x0026;
            uint16_t* const P1SEL2 = (uint16_t* const) 0x0041;
            uint16_t* const P1REN =  (uint16_t* const) 0x0027;

            // Port 2
            uint16_t* const P2IN =   (uint16_t* const) 0x0028;
            uint16_t* const P2OUT =  (uint16_t* const) 0x0029;
            uint16_t* const P2DIR =  (uint16_t* const) 0x002A;
            uint16_t* const P2IFG =  (uint16_t* const) 0x002B;
            uint16_t* const P2IES =  (uint16_t* const) 0x002C;
            uint16_t* const P2IE  =  (uint16_t* const) 0x002D;
            uint16_t* const P2SEL =  (uint16_t* const) 0x002E;
            uint16_t* const P2SEL2 = (uint16_t* const) 0x0042;
            uint16_t* const P2REN =  (uint16_t* const) 0x002F;

            // ===== Watchdog Timer+
            uint16_t* const WDTCTL = (uint16_t* const) 0x0120;
        }
    }
}

#endif

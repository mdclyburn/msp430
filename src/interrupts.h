#ifndef MDL_MSP430_INTERRUPTS_H
#define MDL_MSP430_INTERRUPTS_H

namespace mardev
{
    namespace msp430
    {
        namespace interrupts
        {
            // Interrupt vector offsets
            enum class offset : uint16_t
            {
                // Digital I/O
                port_1 = 0x0004, // P1IFG
                port_2 = 0x0006, // P2IFG

                // Analog-Digital Converter
                adc   = 0x000A, // ADC10IFG

                // USCI
                usci_tx = 0x000C, // UCA0TXIFG, UCB0TXIFG
                usci_rx = 0x000E, // UCA0RXIFG, UCB0RXIFG

                // Timer_A
                timera_0 = 0x0010, // TA0CCR0/TA0CCR1 CCIFG, TAIFG
                timera_1 = 0x0012, // TA0CCR0 CCIFG
                timera_2 = 0x0018, // TA1CCR1/TA1CCR2 CCIFG, TAIFG
                timera_3 = 0x001A, // TA1CCR0 CCIFG

                // Watchdog
                watchdog = 0x0014, // WDTIFG

                // Comparator
                comparator = 0x0016, // CAIFG

                // Non-maskable
                nmi = 0x001C, // NMIIFG, OFIFG, ACCVIFG

                // Reset
                reset = 0x001E // PORIFG, RSTIFG, WDTIFG, KEYV
            };
        }
    }
}

#endif

/** @file
 *
 * Universal Serial Communication Interface
 */

#ifndef MDL_MSP430_USCI_H
#define MDL_MSP430_USCI_H

#include <stdint.h>

#include "interrupt.h"

namespace mardev::msp430::usci
{
    namespace registers
    {
        // ===== USCI_A0 Control and Status Registers
        // Control
        volatile uint8_t* const UCA0CTL0 = (uint8_t* const) 0x60;
        volatile uint8_t* const UCA0CTL1 = (uint8_t* const) 0x61;

        // Baud rate control
        volatile uint8_t* const UCA0BR0 =  (uint8_t* const) 0x62;
        volatile uint8_t* const UCA0BR1 =  (uint8_t* const) 0x63;

        // Modulation control
        volatile uint8_t* const UCA0MCTL = (uint8_t* const) 0x64;

        // Status
        volatile uint8_t* const UCA0STAT = (uint8_t* const) 0x65;

        // Buffers
        volatile const uint8_t* const UCA0RXBUF = (const uint8_t* const) 0x66;
        volatile uint8_t* const       UCA0TXBUF = (uint8_t* const) 0x67;

        // Auto baud control
        volatile uint8_t* const UCA0BCTL = (uint8_t* const) 0x5D;

        // ===== USCI_B0 Control and Status Registers
        // Control
        volatile uint8_t* const UCB0CTL0 = (uint8_t* const) 0x68;
        volatile uint8_t* const UCB0CTL1 = (uint8_t* const) 0x69;

        // Baud rate control
        volatile uint8_t* const UCB0BR0 =  (uint8_t* const) 0x6A;
        volatile uint8_t* const UCB0BR1 =  (uint8_t* const) 0x6B;

        // Status
        volatile uint8_t* const UCB0STAT = (uint8_t* const) 0x6D;

        // Buffers
        volatile const uint8_t* const UCB0RXBUF = (const uint8_t* const) 0x6E;
        volatile uint8_t* const       UCB0TXBUF = (uint8_t* const) 0x6F;

        // ===== Module-Register mapping
        extern volatile uint8_t* const CTL0[];
        extern volatile uint8_t* const CTL1[];

        extern volatile uint8_t* const BR0[];
        extern volatile uint8_t* const BR1[];

        extern volatile uint8_t* const MCTL[];

        extern volatile uint8_t* const STAT[];

        extern volatile const uint8_t* const RXBUF[];
        extern volatile uint8_t* const       TXBUF[];

        namespace masks
        {
            // USCI control register 0 masks
            const uint8_t UCMODE = 0x06;
            const uint8_t UCSYNC  = 0x01;

            // USCI control register 1 masks
            const uint8_t UCSSEL = 0xC0;
            const uint8_t UCSWRST = 0x01;

            // Interrupt Enable register masks
            const uint8_t UCB0TXIE = 0x08;
            const uint8_t UCB0RXIE = 0x04;
            const uint8_t UCA0TXIE = 0x02;
            const uint8_t UCA0RXIE = 0x01;

            // Interrupt Flag 2 register masks
            const uint8_t UCB0TXIFG = 0x08;
            const uint8_t UCB0RXIFG = 0x04;
            const uint8_t UCA0TXIFG = 0x02;
            const uint8_t UCA0RXIFG = 0x01;
        }
    }

    // Mapping USCI module -> register mask
    extern uint8_t const RXIE[];
    extern uint8_t const TXIE[];
    extern uint8_t const RXIFG[];
    extern uint8_t const TXIFG[];

    // USCI control register 0 masks
    const uint8_t UCMODEx = 0x06;
    const uint8_t UCSYNC  = 0x01;

    // USCI control register 1 masks
    const uint8_t UCSSELx = 0xC0;
    const uint8_t UCSWRST = 0x01;

    // Interrupt Enable register masks
    const uint8_t UCB0TXIE = 0x08;
    const uint8_t UCB0RXIE = 0x04;
    const uint8_t UCA0TXIE = 0x02;
    const uint8_t UCA0RXIE = 0x01;

    // Interrupt Flag 2 register masks
    const uint8_t UCB0TXIFG = 0x08;
    const uint8_t UCB0RXIFG = 0x04;
    const uint8_t UCA0TXIFG = 0x02;
    const uint8_t UCA0RXIFG = 0x01;

    /** USCI module */
    enum class Module : uint8_t
    {
        A0 = 0,
        B0 = 1
    };
}

#endif

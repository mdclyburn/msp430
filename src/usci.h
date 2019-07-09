#ifndef MDL_MSP430_USCI_H
#define MDL_MSP430_USCI_H

#include <stdint.h>

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
        volatile uint8_t* const       UCA0TXBUF = (uint8_t* const) 0x6F;

        // ===== Module-Register mapping
        extern uint8_t* const CTL0[] =  { UCA0CTL0, UCB0CTL0 };
        extern uint8_t* const CTL1[] =  { UCA0CTL1, UCB0CTL1 };

        extern uint8_t* const BR0[]  =  { UCA0BR0, UCB0BR0 };
        extern uint8_t* const BR1[]  =  { UCA0BR1, UCB0BR1 };

        extern uint8_t* const STAT[] =  { UCA0STAT, UCB0STAT };

        extern uint8_t* const       RXBUF[] = { UCA0RXBUF, UCB0RXBUF };
        extern const uint8_t* const TXBUF[] = { UCA0TXBUF, UCB0TXBUF };
    }

    // USCI control register 0 masks
    const uint8_t UCMODEx = 0x06;

    // USCI control register 1 masks
    const uint8_t UCSSELx = 0xC0;
    const uint8_t UCSWRST = 0x01;

    enum class Module : uint8_t
    {
        A0 = 0,
        B0 = 1
    };

    /** USCI mode select */
    enum class UCMODE : uint8_t
    {
        SPI3     = 0x00,
        SPI4High = 0x01 << 1,
        SPI4Low  = 0x02 << 1,
        I2C      = 0x03 << 1
    };
}

#endif

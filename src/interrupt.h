/** @file
 *
 * Interrupts
 *
 * Code to support utilizing the interrupt functionality of the MSP430.
 */

#ifndef MDL_MSP430_INTERRUPT_H
#define MDL_MSP430_INTERRUPT_H

#include <stdint.h>

namespace mardev::msp430::interrupt
{
    namespace registers
    {
        volatile uint8_t* const IE2 =  (uint8_t* const) 0x01;
        volatile uint8_t* const IFG2 = (uint8_t* const) 0x03;
    }

    // Digital I/O
    const uint16_t* const digital_io_port_1 = (uint16_t* const) 0xFFE4; // P1IFG
    const uint16_t* const digital_io_port_2 = (uint16_t* const) 0xFFE6; // P2IFG

    // Analog-Digital Converter
    const uint16_t* const adc = (uint16_t* const) 0xFFEA; // ADC10IFG

    // USCI
    const uint16_t* const usci_tx = (uint16_t* const) 0xFFEC; // UCA0TXIFG, UCB0TXIFG
    const uint16_t* const usci_rx = (uint16_t* const) 0xFFEE; // UCA0RXIFG, UCB0RXIFG

    // Timer_A
    const uint16_t* const timera_0 = (uint16_t* const) 0xFFF0; // TA0CCR2/TA0CCR1 CCIFG, TAIFG
    const uint16_t* const timera_1 = (uint16_t* const) 0xFFF2; // TA0CCR0 CCIFG
    const uint16_t* const timera_2 = (uint16_t* const) 0xFFF8; // TA1CCR1/TA1CCR2 CCIFG/ TAIFG
    const uint16_t* const timera_3 = (uint16_t* const) 0xFFFA; // TA1CCR0 CCIFG

    // Watchdog
    const uint16_t* const watchdog = (uint16_t* const) 0xFFF4;

    // Comparator
    const uint16_t* const comparator = (uint16_t* const) 0xFFF6;

    // Non-maskable
    const uint16_t* const nmi = (uint16_t* const) 0xFFFC;

    // Reset
    const uint16_t* const reset = (uint16_t* const) 0xFFFC;

    /** Enable general interrupts.
     */
    inline void enable() { __asm__ __volatile__ ("eint"); }

    /** Disable general interrupts.
     *
     * This function incurs a NOP after disabling interrupts to better protect against an emergent interrupt.
     */
    inline void disable() { __asm__ __volatile__ ("dint { nop"); }

    /** Return from an interrupt service routine.
     *
     * Uses the RETI instruction to restore CPU registers' states (SP, PC, as well as the SR).
     * This should be preferred over using a lone `return' statement to restore the status register,
     * but not more than getting GCC to generate the RETI by marking the function with the 'interrupt' attribute.
     */
    __attribute__((always_inline))
    inline void return_from_interrupt() { __asm__ __volatile__ ("reti"); }
}

#endif

/** @file
 *
 * CPU functions
 */

#ifndef MDL_MSP430_CPU_H
#define MDL_MSP430_CPU_H

namespace mardev::msp430::cpu
{
    /** Enable general interrupts.
     */
    inline void enable_interrupts() { __asm__ __volatile__ ("eint"); }

    /** Disable general interrupts.
     *
     * This function incurs a NOP after disabling interrupts to better protect against an emergent interrupt.
     */
    inline void disable_interrupts() { __asm__ __volatile__ ("dint { nop"); }
}

#endif

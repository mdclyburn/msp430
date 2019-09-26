/** @file
 *
 * CPU functions
 */

#ifndef MDL_MSP430_CPU_H
#define MDL_MSP430_CPU_H

namespace mardev::msp430::cpu
{
    inline void enable_interrupts() { __asm__("eint"); }

    inline void disable_interrupts() { __asm__("dint"); }
}

#endif

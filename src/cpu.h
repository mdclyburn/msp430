/** @file
 *
 * CPU functions
 */

#ifndef MDL_MSP430_CPU_H
#define MDL_MSP430_CPU_H

namespace mardev::msp430::cpu
{
    inline void enter_lpm0()
    {
        __asm__ __volatile__ ("bis #24, SR");
    }

    inline void enter_lpm1()
    {
        __asm__ __volatile__ ("bis #88, SR");
    }

    inline void enter_lpm2()
    {
        __asm__ __volatile__ ("bis #152, SR");
    }

    inline void enter_lpm3()
    {
        __asm__ __volatile__ ("bis #216, SR");
    }

    inline void enter_lpm4()
    {
        __asm__ __volatile__ ("bis #248, SR");
    }
}

#endif

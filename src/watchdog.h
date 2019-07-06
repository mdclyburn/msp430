#ifndef MDL_MSP430_WATCHDOG_H
#define MDL_MSP430_WATCHDOG_H

#include <stdint.h>

namespace mardev::msp430::watchdog
{
    namespace registers
    {
        volatile uint16_t* const WDTCTL = (volatile uint16_t* const) 0x0120;
    }

    const uint16_t WDTPW    = 0x5A00;
    const uint16_t WDTHOLD  = 0x0080;
    const uint16_t WDTNMIES = 0x0040;
    const uint16_t WDTNMI   = 0x0020;
    const uint16_t WDTTMSEL = 0x0010;
    const uint16_t WDTCNTCL = 0x0008;
    const uint16_t WDTSSEL  = 0x0004;

    // WDTTISx = clock source / x
    const uint8_t WDTTIS64    = 3;
    const uint8_t WDTTIS512   = 2;
    const uint8_t WDTTIS8192  = 1;
    const uint8_t WDTTIS32768 = 0;

    inline void disable() { *registers::WDTCTL = WDTPW | WDTHOLD; }

    inline void enable_interval_mode() { *registers::WDTCTL = *registers::WDTCTL | WDTTMSEL; }
}

#endif
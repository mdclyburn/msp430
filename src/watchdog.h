#ifndef MDL_MSP430_WATCHDOG_H
#define MDL_MSP430_WATCHDOG_H

#include <stdint.h>

#include "registers.h"

namespace mardev
{
    namespace msp430
    {
        namespace watchdog
        {
            namespace reg = mardev::msp430::reg;

            const uint8_t WDTPW = 0x5A;
            const uint8_t WDTHOLD = 1 << 7;
            const uint8_t WDTNMIES = 1 << 6;
            const uint8_t WDTNMI = 1 << 5;
            const uint8_t WDTTMSEL = 1 << 4;
            const uint8_t WDTCNTCL = 1 << 3;
            const uint8_t WDTSSEL = 1 << 2;

            // WDTTISx = clock source / x
            const uint8_t WDTTIS64 =    3;
            const uint8_t WDTTIS512 =   2;
            const uint8_t WDTTIS8192 =  1;
            const uint8_t WDTTIS32768 = 0;

            void disable() { *reg::WDTCTL = WDTPW + WDTHOLD; }
        }
    }
}

#endif

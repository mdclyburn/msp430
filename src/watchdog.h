/** @file
 *
 * Watchdog+ functions
 */

#ifndef MDL_MSP430_WATCHDOG_H
#define MDL_MSP430_WATCHDOG_H

#include <stdint.h>

namespace mardev::msp430::watchdog
{
    namespace registers
    {
        volatile uint16_t* const WDTCTL = (volatile uint16_t* const) 0x0120;

        namespace masks
        {
            const uint16_t WDTPW    = 0x5A00;
            const uint16_t WDTHOLD  = 0b00000000'10000000;
            const uint16_t WDTNMIES = 0b00000000'01000000;
            const uint16_t WDTNMI   = 0b00000000'00100000;
            const uint16_t WDTTMSEL = 0b00000000'00010000;
            const uint16_t WDTCNTCL = 0b00000000'00001000;
            const uint16_t WDTSSEL  = 0b00000000'00000100;
        }
    }

    inline void disable()
    {
        *registers::WDTCTL =
            registers::masks::WDTPW
            | registers::masks::WDTHOLD;
    }

    inline void enable_interval_mode()
    {
        *registers::WDTCTL =
            (*registers::WDTCTL & 0b11111111)
            | registers::masks::WDTPW
            | registers::masks::WDTTMSEL;
    }
}

#endif

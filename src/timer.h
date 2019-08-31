/** @file
 *
 * Timer
 */

#ifndef MDL_MSP430_TIMER_H
#define MDL_MSP430_TIMER_H

#include <stdint.h>

#include "clock.h"

namespace clock = mardev::msp430::clock;

namespace mardev::msp430::timer
{
    namespace registers
    {
        volatile uint16_t* const TACTL   = (volatile uint16_t* const) 0x0160;
        volatile uint16_t* const TAR     = (volatile uint16_t* const) 0x0170;

        volatile uint16_t* const TACCTL0 = (volatile uint16_t* const) 0x0162;
        volatile uint16_t* const TACCR0  = (volatile uint16_t* const) 0x0172;

        volatile uint16_t* const TACCTL1 = (volatile uint16_t* const) 0x0164;
        volatile uint16_t* const TACCR1  = (volatile uint16_t* const) 0x0174;

        volatile uint16_t* const TACCTL2 = (volatile uint16_t* const) 0x0166;
        volatile uint16_t* const TACCR2  = (volatile uint16_t* const) 0x0176;

        volatile const uint16_t* const TAIV    = (volatile const uint16_t* const) 0x012E;
    }

    // TACTL register masks
    const uint16_t TASSELx = 3 << 8;
    const uint16_t IDx     = 3 << 6;
    const uint16_t MCx     = 3 << 4;
    const uint16_t TACLR   = 1 << 2;
    const uint16_t TAIE    = 1 << 1;
    const uint16_t TAIFG   = 1;

    /** Timer clock source */
    enum class TASSEL : uint16_t
    {
        TACLK = 0,
        ACLK  = 1 << 8,
        SMCLK = 2 << 8,
        INCLK = 3 << 8
    };

    /** Input divider */
    enum class ID : uint16_t
    {
        D1 = 0,
        D2 = 1 << 6,
        D4 = 2 << 6,
        D8 = 3 << 6
    };

    /** Mode control */
    enum class MC : uint16_t
    {
        Stop       = 0,
        Up         = 1 << 4,
        Continuous = 2 << 4,
        UpDown     = 3 << 4
    };

    inline void start(const MC mode,
                      const TASSEL source,
                      const ID divider)
    {
        *registers::TACTL =
            (uint16_t) mode
            | (uint16_t) source
            | (uint16_t) divider;
    }

    inline void reset()
    {
        *registers::TACTL |= TACLR;
    }

    inline uint16_t count()
    {
        return *registers::TAR;
    }

    inline void reset_count()
    {
        *registers::TAR = 0;
    }

    inline void set_signal_source(const TASSEL s)
    {
        *registers::TACTL &= ~TASSELx | (uint16_t) s;
    }

    inline void enable_interrupts()
    {
        *registers::TACTL ^= TAIE;
    }

    inline void disable_interrupts()
    {
        *registers::TACTL |= TAIE;
    }

    // ===== Timer Capture/Control

    const uint16_t CMx     = 3 << 14;
    const uint16_t CCISx   = 3 << 12;
    const uint16_t SCS     = 1 << 11;
    const uint16_t SCCI    = 1 << 10;
    const uint16_t CAP     = 1 << 8;
    const uint16_t OUTMODx = 7 << 5;
    const uint16_t CCIE    = 1 << 4;
    const uint16_t CCI     = 1 << 3;
    const uint16_t OUT     = 1 << 2;
    const uint16_t COV     = 1 << 1;
    const uint16_t CCIFG   = 1;

    enum class CM : uint16_t
    {
        Disabled = 0,
        Rising   = 0x4000, // GCC warns of enum value too large for (<< 14).
        Falling  = 0x8000,
        Both     = 0xC000
    };

    enum class CCIS : uint16_t
    {
        CCIxA = 0,
        CCIxB = 1 << 12,
        GND   = 2 << 12,
        Vcc   = 3 << 12
    };

    /** Configure a capture/compare register.
     */
    void configure_compare(const uint8_t instance,
                           const uint16_t count_max,
                           const bool enable_interrupts);

    /** Use TACCR0 to wait a specified amount of time.
     */
    void delay(const uint16_t milliseconds);

    /** Use TACCR0 to wait a specified amount of time.
     */
    void delay(const uint16_t count,
               const uint16_t ticks_per_count,
               const TASSEL source);
}

#endif

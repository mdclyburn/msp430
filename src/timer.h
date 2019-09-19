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

        namespace masks
        {
            // TACTL
            const uint16_t TASSELx = 0b00000011'00000000;
            const uint16_t IDx     = 0b00000000'11000000;
            const uint16_t MCx     = 0b00000000'00110000;
            const uint16_t TACLR   = 0b00000000'00000100;
            const uint16_t TAIE    = 0b00000000'00000010;
            const uint16_t TAIFG   = 0b00000000'00000001;

            // Timer Capture/Control
            const uint16_t CMx     = 0b11000000'00000000;
            const uint16_t CCISx   = 0b00110000'00000000;
            const uint16_t SCS     = 0b00001000'00000000;
            const uint16_t SCCI    = 0b00000100'00000000;
            const uint16_t CAP     = 0b00000001'00000000;
            const uint16_t OUTMODx = 0b00000000'11100000;
            const uint16_t CCIE    = 0b00000000'00010000;
            const uint16_t CCI     = 0b00000000'00001000;
            const uint16_t OUT     = 0b00000000'00000100;
            const uint16_t COV     = 0b00000000'00000010;
            const uint16_t CCIFG   = 0b00000000'00000001;
        }
    }

    /** Timer clock source */
    enum class TASSEL : uint16_t
    {
        TACLK = 0b00000000'00000000,
        ACLK  = 0b00000001'00000000,
        SMCLK = 0b00000010'00000000,
        INCLK = 0b00000011'00000000
    };

    /** Input divider */
    enum class ID : uint16_t
    {
        D1 = 0b00000000'00000000,
        D2 = 0b00000000'01000000,
        D4 = 0b00000000'10000000,
        D8 = 0b00000000'11000000
    };

    /** Mode control */
    enum class MC : uint16_t
    {
        Stop       = 0b00000000'00000000,
        Up         = 0b00000000'00010000,
        Continuous = 0b00000000'00100000,
        UpDown     = 0b00000000'00110000
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
        *registers::TACTL |= registers::masks::TACLR;
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
        *registers::TACTL &= ~registers::masks::TASSELx | (uint16_t) s;
    }

    inline void enable_interrupts()
    {
        *registers::TACTL |= registers::masks::TAIE;
    }

    inline void disable_interrupts()
    {
        *registers::TACTL ^= registers::masks::TAIE;
    }

    enum class CM : uint16_t
    {
        Disabled = 0b00000000'00000000,
        Rising   = 0b01000000'00000000,
        Falling  = 0b10000000'00000000,
        Both     = 0b11000000'00000000
    };

    enum class CCIS : uint16_t
    {
        CCIxA = 0b00000000'00000000,
        CCIxB = 0b00010000'00000000,
        GND   = 0b00100000'00000000,
        Vcc   = 0b00110000'00000000
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

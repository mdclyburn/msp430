#include "clock.h"
#include "timer.h"

namespace mardev::msp430::timer
{
    /** Capture/Compare value instance registers */
    volatile uint16_t* const CCV[] =
    {
        registers::TACCR0,
        registers::TACCR1,
        registers::TACCR2
    };

    /** Capture/Compare control instance registers */
    volatile uint16_t* const CCCTL[] =
    {
        registers::TACCTL0,
        registers::TACCTL1,
        registers::TACCTL2
    };

    void configure_compare(const uint8_t instance,
                           const uint16_t count_max,
                           const bool enable_interrupts)
    {
        // None have any more than 3 instances.
        if(instance > 2)
            return;

        uint16_t settings =
            (uint16_t) CM::Disabled
            & ~registers::masks::CAP; // 0 = compare mode

        if(enable_interrupts)
            settings |= registers::masks::CCIE;

        *CCCTL[instance] = settings;

        return;
    }

    void delay(const uint16_t milliseconds)
    {
        // TODO: disable interrupts

        using namespace mardev::msp430::clock;
        configure_auxiliary_clock(LFXT1S::VLOCLK, DIVAx::D1);

        *registers::TACCR0 = 65535;

        uint16_t counted = 0;
        while(counted <= milliseconds)
        {
            uint16_t ticks = 0;
            if(milliseconds - counted < 1000)
            {
                ticks = 12 * (milliseconds - counted);
            }
            else
            {
                ticks = 12000;
            }

            start(MC::Up, TASSEL::ACLK, ID::D1);
            while(*registers::TAR < ticks);
            reset();

            counted += ticks;
        }

        return;
    }

    void delay(const uint16_t counts,
               const uint16_t ticks_per_count,
               const TASSEL source)
    {
        reset();
        *registers::TACCR0 = 65535;

        for(uint16_t i = 0; i < counts; i++)
        {
            start(MC::Up, source, ID::D1);
            while(*registers::TAR < ticks_per_count);
            reset();
        }

        return;
    }
}

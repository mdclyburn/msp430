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
            & ~CAP; // 0 = compare mode

        if(enable_interrupts)
            settings |= CCIE;

        *CCCTL[instance] = settings;

        return;
    }
}

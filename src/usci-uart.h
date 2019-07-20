#ifndef MDL_MSP430_USCI_UART_H
#define MDL_MSP430_USCI_UART_H

#include "digital-io.h"
#include "usci.h"

namespace mardev::msp430::usci::uart
{
    namespace dio = mardev::msp430::digital_io;
    namespace usci = mardev::msp430::usci;

    // Control register 0
    const uint8_t UCSSEL = 0x03 << 6;

    // UCAxSTAT Status register masks
    const uint8_t UCLISTEN = 0x40;
    const uint8_t UCFE     = 0x30;
    const uint8_t UCOE     = 0x20;
    const uint8_t UCPE     = 0x10;
    const uint8_t UCBRK    = 0x08;
    const uint8_t UCRXERR  = 0x04;
    const uint8_t UCADDR   = 0x02;
    const uint8_t UCIDLE   = 0x02;
    const uint8_t UCBUSY   = 0x01;

    // Modulation control register
    const uint8_t UCBRFx = 0x80;
    const uint8_t UCBRSx = 0x07 << 1;
    const uint8_t UCOS16 = 0x01;

    /** USCI UART Modules */
    enum class Module : uint8_t
    {
        A0 = 0
    };

    /** Asynchronous USCI mode select */
    enum class UCMODE : uint8_t
    {
        UART                     = 0x00,
        IdleLineMultiprocessor   = 0x01 << 1,
        AddressBitMultiprocessor = 0x02 << 1,
        UARTAutoBaud             = 0x03 << 1
    };

    /** USCI clock source select */
    enum class UCSSELx : uint8_t
    {
        UCLK  = 0x00,
        ACLK  = 0x01 << 6,
        SMCLK = 0x02 << 6
    };

    // Mapping module -> pin number
    extern const uint8_t RXD[];
    extern const uint8_t TXD[];

    inline void reset(const Module module)
    {
        volatile uint8_t* const ctl1 = usci::registers::CTL1[(uint8_t) module];
        *ctl1 |= usci::UCSWRST;
    }

    inline void enable(const Module module)
    {
        volatile uint8_t* const ctl0 = usci::registers::CTL0[(uint8_t) module];
        *ctl0 &= ~usci::UCSYNC;

        const uint8_t pin_rxd = RXD[(uint8_t) module];
        const uint8_t pin_txd = TXD[(uint8_t) module];
        dio::set_pin_mode(pin_rxd, dio::IO::Input, dio::Function::Secondary);
        dio::set_pin_mode(pin_txd, dio::IO::Output, dio::Function::Secondary);

        volatile uint8_t* const ctl1 = usci::registers::CTL1[(uint8_t) module];
        *ctl1 &= ~usci::UCSWRST;
    }

    inline void set_mode(const Module module,
                         const UCMODE mode)
    {
        volatile uint8_t* r = usci::registers::CTL0[(uint8_t) module];
        *r = *r & ~(0x03 << 1) | (uint8_t) mode;
    }

    inline void set_clock_source(const Module module,
                                 const UCSSELx source)
    {
        volatile uint8_t* r = usci::registers::CTL1[(uint8_t) module];
        *r = *r & ~(0x03 << 6) | (uint8_t) source;
    }

    inline void enable_parity(const Module module,
                              const bool enabled)
    {
        volatile uint8_t* r = usci::registers::CTL0[(uint8_t) module];
        const uint8_t UCPEN = 0x80;
        *r = *r & ~UCPEN;
        if (enabled) *r |= UCPEN;
    }

    inline void enable_even_parity(const Module module)
    {
        volatile uint8_t* r = usci::registers::CTL0[(uint8_t) module];
        const uint8_t UCPAR = 0x40;
        *r |= UCPAR;
    }

    inline void enable_odd_parity(const Module module)
    {
        volatile uint8_t* r = usci::registers::CTL0[(uint8_t) module];
        const uint8_t UCPAR = 0x40;
        *r &= ~UCPAR;
    }

    inline void set_baud_control(const Module module,
                                 const uint16_t val)
    {
        volatile uint8_t* br = usci::registers::BR0[(uint8_t) module];

        // This assumption holds until it doesn't.
        br[0] = (uint8_t) (val & 0xFF);
        br[1] = (uint8_t) (val >> 8);
    }

    inline void set_modulation(const Module module,
                                  const uint8_t first_stage,
                                  const uint8_t second_stage,
                                  const bool enable_oversampling)
    {
        volatile uint8_t* const mctl = usci::registers::MCTL[(uint8_t) module];
        uint8_t config = (first_stage << 4) | (second_stage << 1);
        if(enable_oversampling)
            config |= 1;
        *mctl = config;
    }

    inline void clear_errors(const Module module)
    {
        volatile uint8_t* const stat = usci::registers::STAT[(uint8_t) module];
        *stat &= 254;
    }

    inline uint8_t read(volatile const uint8_t* const status_register,
                        volatile const uint8_t* const rx_buffer,
                        const uint8_t rx_flag_mask)
    {
        while(!(*status_register & UCRXERR)
              && !(*interrupt::registers::IFG2 & rx_flag_mask));
        return *rx_buffer;
    }

    uint8_t read(const Module module);

    uint16_t read(const Module module,
                  uint8_t* const buffer,
                  const uint16_t max_length);

    void write(const Module module,
               const uint8_t* const data,
               const uint16_t length);
}

#endif

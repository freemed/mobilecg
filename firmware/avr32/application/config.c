#include <avr32/io.h>
#include "config.h"
#include <intc.h>
#include <power_clocks_lib.h>
#include <sysclk.h>
#include <tc.h>

#define false 0

#define EXAMPLE_TC                 (&AVR32_TC)
#define EXAMPLE_TC_CHANNEL         0
#define EXAMPLE_TC_IRQ             AVR32_TC_IRQ0
#define EXAMPLE_TC_IRQ_GROUP       AVR32_TC_IRQ_GROUP
#define EXAMPLE_TC_IRQ_PRIORITY    AVR32_INTC_INT0

void clear_timer_interrupt()
{
	// Clear the interrupt flag. This is a side effect of reading the TC SR.
	tc_read_sr(EXAMPLE_TC, EXAMPLE_TC_CHANNEL);
}

void setup_timer_controller(__int_handler handler)
{
		// Options for waveform generation.
	static const tc_waveform_opt_t waveform_opt = {
		// Channel selection.
		.channel  = EXAMPLE_TC_CHANNEL,
		// Software trigger effect on TIOB.
		.bswtrg   = TC_EVT_EFFECT_NOOP,
		// External event effect on TIOB.
		.beevt    = TC_EVT_EFFECT_NOOP,
		// RC compare effect on TIOB.
		.bcpc     = TC_EVT_EFFECT_NOOP,
		// RB compare effect on TIOB.
		.bcpb     = TC_EVT_EFFECT_NOOP,
		// Software trigger effect on TIOA.
		.aswtrg   = TC_EVT_EFFECT_NOOP,
		// External event effect on TIOA.
		.aeevt    = TC_EVT_EFFECT_NOOP,
		// RC compare effect on TIOA.
		.acpc     = TC_EVT_EFFECT_NOOP,
		/*
		 * RA compare effect on TIOA.
		 * (other possibilities are none, set and clear).
		 */
		.acpa     = TC_EVT_EFFECT_NOOP,
		/*
		 * Waveform selection: Up mode with automatic trigger(reset)
		 * on RC compare.
		 */
		.wavsel   = TC_WAVEFORM_SEL_UP_MODE_RC_TRIGGER,
		// External event trigger enable.
		.enetrg   = false,
		// External event selection.
		.eevt     = 0,
		// External event edge selection.
		.eevtedg  = TC_SEL_NO_EDGE,
		// Counter disable when RC compare.
		.cpcdis   = false,
		// Counter clock stopped with RC compare.
		.cpcstop  = false,
		// Burst signal selection.
		.burst    = false,
		// Clock inversion.
		.clki     = false,
		// Internal source clock 3, connected to fPBA / 8.
		.tcclks   = TC_CLOCK_SOURCE_TC3
	};

	// Options for enabling TC interrupts
	static const tc_interrupt_t tc_interrupt = {
		.etrgs = 0,
		.ldrbs = 0,
		.ldras = 0,
		.cpcs  = 1, // Enable interrupt on RC compare alone
		.cpbs  = 0,
		.cpas  = 0,
		.lovrs = 0,
		.covfs = 0
	};

	sysclk_enable_peripheral_clock((&AVR32_TC));
	cpu_irq_disable();
	INTC_init_interrupts();
	INTC_register_interrupt(handler, EXAMPLE_TC_IRQ, EXAMPLE_TC_IRQ_PRIORITY);
	cpu_irq_enable();

	// Initialize the timer/counter.
	tc_init_waveform((&AVR32_TC), &waveform_opt);

	/*
	 * Set the compare triggers.
	 * We configure it to count every 1 milliseconds.
	 * We want: (1 / (fPBA / 8)) * RC = 1 ms, hence RC = (fPBA / 8) / 1000
	 * to get an interrupt every 10 ms.
	 */
//	tc_write_rc((&AVR32_TC), EXAMPLE_TC_CHANNEL, (sysclk_get_pba_hz() / 8 / 1000));
//	tc_write_rc((&AVR32_TC), EXAMPLE_TC_CHANNEL, (sysclk_get_pba_hz() / 8 / 2000));
	tc_write_rc((&AVR32_TC), EXAMPLE_TC_CHANNEL, (12 * MHz / 8 / 325));
	// configure the timer interrupt
	tc_configure_interrupts((&AVR32_TC), EXAMPLE_TC_CHANNEL, &tc_interrupt);
	// Start the timer/counter.
	tc_start((&AVR32_TC), EXAMPLE_TC_CHANNEL);
}

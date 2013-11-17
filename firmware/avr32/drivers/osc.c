
 #include <osc.h>

 #ifdef BOARD_OSC0_HZ
 void osc_priv_enable_osc0(void)
 {
     irqflags_t flags;

     flags = cpu_irq_save();
     AVR32_SCIF.unlock = 0xaa000000 | AVR32_SCIF_OSCCTRL;
     AVR32_SCIF.oscctrl[0] =
             (OSC0_STARTUP_VALUE << AVR32_SCIF_OSCCTRL_STARTUP)
             | (OSC0_GAIN_VALUE << AVR32_SCIF_OSCCTRL_GAIN)
             | (OSC0_MODE_VALUE << AVR32_SCIF_OSCCTRL_MODE)
             | (1U << AVR32_SCIF_OSCCTRL_OSCEN);
     cpu_irq_restore(flags);
 }

 void osc_priv_disable_osc0(void)
 {
     irqflags_t flags;

     flags = cpu_irq_save();
     AVR32_SCIF.unlock = 0xaa000000 | AVR32_SCIF_OSCCTRL;
     AVR32_SCIF.oscctrl[0] = 0;
     cpu_irq_restore(flags);
 }
 #endif /* BOARD_OSC0_HZ */

 #ifdef BOARD_OSC32_HZ
 void osc_priv_enable_osc32(void)
 {
     irqflags_t flags;

     flags = cpu_irq_save();
     AVR32_SCIF.unlock = 0xaa000000 | AVR32_SCIF_OSCCTRL32;
     AVR32_SCIF.oscctrl32 =
             (OSC32_STARTUP_VALUE << AVR32_SCIF_OSCCTRL32_STARTUP)
             | (OSC32_MODE_VALUE << AVR32_SCIF_OSCCTRL32_MODE)
             | (1U << AVR32_SCIF_OSCCTRL32_OSC32EN);
     cpu_irq_restore(flags);
 }

 void osc_priv_disable_osc32(void)
 {
     irqflags_t flags;

     flags = cpu_irq_save();
     AVR32_SCIF.unlock = 0xaa000000 | AVR32_SCIF_OSCCTRL32;
     AVR32_SCIF.oscctrl32 = 0;
     cpu_irq_restore(flags);
 }
 #endif /* BOARD_OSC32_HZ */

 void osc_priv_enable_rc120m(void)
 {
     irqflags_t flags;

     flags = cpu_irq_save();
     AVR32_SCIF.unlock = 0xaa000000 | AVR32_SCIF_RC120MCR;
     AVR32_SCIF.rc120mcr = 1U << AVR32_SCIF_RC120MCR_EN;
     cpu_irq_restore(flags);
 }

 void osc_priv_disable_rc120m(void)
 {
     irqflags_t flags;

     flags = cpu_irq_save();
     AVR32_SCIF.unlock = 0xaa000000 | AVR32_SCIF_RC120MCR;
     AVR32_SCIF.rc120mcr = 0;
     cpu_irq_restore(flags);
 }

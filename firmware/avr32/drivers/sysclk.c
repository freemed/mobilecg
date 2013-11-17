
 #include <avr32/io.h>
 #include <compiler.h>
 #include <stdbool.h>
 #include <sysclk.h>
 #include "flashcdw.h"


 #define AVR32_PM_PBADIV 7
 #define AVR32_PM_PBBDIV 7

 #if ((CONFIG_SYSCLK_CPU_DIV > CONFIG_SYSCLK_PBA_DIV) || \
      (CONFIG_SYSCLK_CPU_DIV > CONFIG_SYSCLK_PBB_DIV))
 # error CONFIG_SYSCLK_PBx_DIV must be equal to or more than CONFIG_SYSCLK_CPU_DIV.
 #endif



 #define SYSCLK_INIT_MINIMAL_CPUMASK                                \
     ((1 << SYSCLK_OCD)                                             \
     |(1 << SYSCLK_SYSTIMER))


 #define SYSCLK_INIT_MINIMAL_HSBMASK                                \
     ((1 << SYSCLK_FLASHCDW_DATA)                                   \
     | (1 << SYSCLK_PBA_BRIDGE)                                     \
         | (1 << SYSCLK_PBB_BRIDGE)                                 \
     | (1 << SYSCLK_USBC_DATA)                                      \
     | (1 << SYSCLK_PDCA_HSB))


 #define SYSCLK_INIT_MINIMAL_PBAMASK                                \
      ((1 << SYSCLK_INTC)                                           \
     | (1 << SYSCLK_GPIO)                                           \
     | (1 << SYSCLK_SCIF)                                           \
     | (1 << SYSCLK_PM))


 #define SYSCLK_INIT_MINIMAL_PBBMASK     0


 #if defined(CONFIG_SYSCLK_DEFAULT_RETURNS_SLOW_OSC)

 bool sysclk_initialized = false;
 #endif

 void sysclk_priv_enable_module(unsigned int bus_id, unsigned int module_index)
 {
     irqflags_t flags;
     uint32_t   mask;

     flags = cpu_irq_save();

     /* Enable the clock */
     mask = *(&AVR32_PM.cpumask + bus_id);
     mask |= 1U << module_index;
     AVR32_PM.unlock = 0xaa000020 + (4 * bus_id);
     *(&AVR32_PM.cpumask + bus_id) = mask;

     cpu_irq_restore(flags);
 }

 void sysclk_priv_disable_module(unsigned int bus_id, unsigned int module_index)
 {
     irqflags_t flags;
     uint32_t   mask;

     flags = cpu_irq_save();

     /* Disable the clock */
     mask = *(&AVR32_PM.cpumask + bus_id);
     mask &= ~(1U << module_index);
     AVR32_PM.unlock = 0xaa000020 + (4 * bus_id);
     *(&AVR32_PM.cpumask + bus_id) = mask;

     cpu_irq_restore(flags);
 }


 void sysclk_set_prescalers(unsigned int cpu_shift,
         unsigned int pba_shift, unsigned int pbb_shift)
 {
     irqflags_t flags;
     uint32_t   cpu_cksel = 0;
     uint32_t   pba_cksel = 0;
     uint32_t   pbb_cksel = 0;

     Assert(cpu_shift <= pba_shift);
     Assert(cpu_shift <= pbb_shift);

     if (cpu_shift > 0)
         cpu_cksel = ((cpu_shift - 1) << AVR32_PM_CPUSEL_OFFSET)
                 | (1U << AVR32_PM_CPUDIV);

     if (pba_shift > 0)
         pba_cksel = ((pba_shift - 1) << AVR32_PM_PBASEL_OFFSET)
                 | (1U << AVR32_PM_PBADIV);

     if (pbb_shift > 0)
         pbb_cksel = ((pbb_shift - 1) << AVR32_PM_PBBSEL_OFFSET)
                 | (1U << AVR32_PM_PBBDIV);

     flags = cpu_irq_save();
     AVR32_PM.unlock = 0xaa000000 | AVR32_PM_CPUSEL;
     AVR32_PM.cpusel = cpu_cksel;
     AVR32_PM.unlock = 0xaa000000 | AVR32_PM_PBASEL;
     AVR32_PM.pbasel = pba_cksel;
     AVR32_PM.unlock = 0xaa000000 | AVR32_PM_PBBSEL;
     AVR32_PM.pbbsel = pbb_cksel;
     cpu_irq_restore(flags);
 }

 void sysclk_set_source(uint_fast8_t src)
 {
     irqflags_t flags;

     Assert(src <= SYSCLK_SRC_PLL1);

     flags = cpu_irq_save();
     AVR32_PM.unlock = 0xaa000000 | AVR32_PM_MCCTRL;
     AVR32_PM.mcctrl = src;
     cpu_irq_restore(flags);
 }

 #if defined(CONFIG_USBCLK_SOURCE) || defined(__DOXYGEN__)

 void sysclk_enable_usb(void)
 {
     struct genclk_config gcfg;

     genclk_config_defaults(&gcfg, AVR32_USBC_GCLK_NUM);

     /*
      * Switch to the system clock selected by the user.
      */
     switch (CONFIG_USBCLK_SOURCE) {
 #ifdef BOARD_OSC0_HZ
     case USBCLK_SRC_OSC0:
         osc_enable(OSC_ID_OSC0);
         osc_wait_ready(OSC_ID_OSC0);
         genclk_config_set_source(&gcfg, GENCLK_SRC_OSC0);
         break;
 #endif

 #ifdef CONFIG_PLL0_SOURCE
     case USBCLK_SRC_PLL0: {
         struct pll_config pllcfg;
         pll_enable_source(CONFIG_PLL0_SOURCE);
         pll_config_defaults(&pllcfg, 0);
         pll_enable(&pllcfg, 0);
         pll_wait_for_lock(0);
         genclk_config_set_source(&gcfg, GENCLK_SRC_PLL0);
         break;
     }
 #endif

 #ifdef CONFIG_PLL1_SOURCE
     case USBCLK_SRC_PLL1: {
         struct pll_config pllcfg;
         pll_enable_source(CONFIG_PLL1_SOURCE);
         pll_config_defaults(&pllcfg, 1);
         pll_enable(&pllcfg, 1);
         pll_wait_for_lock(1);
         genclk_config_set_source(&gcfg, GENCLK_SRC_PLL1);
         break;
     }
 #endif

     default:
         /* unhandled_case(CONFIG_SYSCLK_SOURCE); */
         break;
     }

     genclk_config_set_divider(&gcfg, CONFIG_USBCLK_DIV);
     genclk_enable(&gcfg, AVR32_USBC_GCLK_NUM);
 }

 void sysclk_disable_usb(void)
 {
    genclk_disable(AVR32_USBC_GCLK_NUM);
 }
 #endif // CONFIG_USBCLK_SOURCE


 void sysclk_init(void)
 {
		
		     /* Set up system clock dividers if different from defaults */
     if ((CONFIG_SYSCLK_CPU_DIV > 0) || (CONFIG_SYSCLK_PBA_DIV > 0) ||
             (CONFIG_SYSCLK_PBB_DIV > 0)) {
	         sysclk_set_prescalers(CONFIG_SYSCLK_CPU_DIV,
                 CONFIG_SYSCLK_PBA_DIV,
                 CONFIG_SYSCLK_PBB_DIV);
     }
     /* Switch to system clock selected by user */
     switch (CONFIG_SYSCLK_SOURCE) {
     case SYSCLK_SRC_RCSYS:
         /* Already running from RCSYS */
         break;

 #ifdef BOARD_OSC0_HZ
     case SYSCLK_SRC_OSC0:

		osc_enable(OSC_ID_OSC0);

		osc_wait_ready(OSC_ID_OSC0);

         sysclk_set_source(SYSCLK_SRC_OSC0);
         break;
 #endif




 #ifdef CONFIG_PLL0_SOURCE
     case SYSCLK_SRC_PLL0: {
         struct pll_config pllcfg;

         pll_enable_source(CONFIG_PLL0_SOURCE);
         pll_config_defaults(&pllcfg, 0);
         pll_enable(&pllcfg, 0);
         pll_wait_for_lock(0);
         // Set a flash wait state depending on the new cpu frequency.
         flash_set_bus_freq(sysclk_get_main_hz());
         sysclk_set_source(SYSCLK_SRC_PLL0);
         break;
     }
 #endif

 #ifdef CONFIG_PLL1_SOURCE
     case SYSCLK_SRC_PLL1: {
         struct pll_config pllcfg;

         pll_enable_source(CONFIG_PLL1_SOURCE);
         pll_config_defaults(&pllcfg, 1);
         pll_enable(&pllcfg, 1);
         pll_wait_for_lock(1);
         // Set a flash wait state depending on the new cpu frequency.
         flash_set_bus_freq(sysclk_get_main_hz());
         sysclk_set_source(SYSCLK_SRC_PLL1);
         break;
     }
 #endif
     case SYSCLK_SRC_RC120M:
         osc_enable(OSC_ID_RC120M);
         osc_wait_ready(OSC_ID_RC120M);
         // Set a flash wait state depending on the new cpu frequency.
         flash_set_bus_freq(sysclk_get_cpu_hz());
         sysclk_set_source(SYSCLK_SRC_RC120M);
     break;

     }

     /* If the user has specified clock masks, enable only requested clocks */
 #if defined(CONFIG_SYSCLK_INIT_CPUMASK)
     AVR32_PM.cpumask = SYSCLK_INIT_MINIMAL_CPUMASK | CONFIG_SYSCLK_INIT_CPUMASK;
 #endif
 #if defined(CONFIG_SYSCLK_INIT_PBAMASK)
     AVR32_PM.pbamask = SYSCLK_INIT_MINIMAL_PBAMASK | CONFIG_SYSCLK_INIT_PBAMASK;
 #endif
 #if defined(CONFIG_SYSCLK_INIT_PBBMASK)
     AVR32_PM.pbbmask = SYSCLK_INIT_MINIMAL_PBBMASK | CONFIG_SYSCLK_INIT_PBBMASK;
 #endif
 #if defined(CONFIG_SYSCLK_INIT_HSBMASK)
     AVR32_PM.hsbmask = SYSCLK_INIT_MINIMAL_HSBMASK | CONFIG_SYSCLK_INIT_HSBMASK;
 #endif

 #if (defined CONFIG_SYSCLK_DEFAULT_RETURNS_SLOW_OSC)
     /* Signal that the internal frequencies are setup */
     sysclk_initialized = true;
 #endif
 }


 #ifndef CHIP_SYSCLK_H_INCLUDED
 #define CHIP_SYSCLK_H_INCLUDED

 #include <board.h>

 #ifdef __cplusplus
 extern "C" {
 #endif


 #if !defined(AVR32_TWIS_ADDRESS) && defined(AVR32_TWIS0_ADDRESS)
 # define AVR32_TWIS_ADDRESS     AVR32_TWIS0_ADDRESS
 #endif

 #if !defined(AVR32_IISC_CLK_PBA) && defined(AVR32_I2SC_CLK_PBA)
 # define AVR32_IISC_CLK_PBA     AVR32_I2SC_CLK_PBA
 #endif



 #ifndef CONFIG_SYSCLK_SOURCE
 # define CONFIG_SYSCLK_SOURCE   SYSCLK_SRC_RCSYS
 #endif
 #ifndef CONFIG_SYSCLK_CPU_DIV
 # define CONFIG_SYSCLK_CPU_DIV  0
 #endif
 #ifndef CONFIG_SYSCLK_PBA_DIV
 # define CONFIG_SYSCLK_PBA_DIV  0
 #endif



 #define SYSCLK_SRC_RCSYS        0       //!< System RC oscillator
 #define SYSCLK_SRC_OSC0         1       //!< Oscillator 0
 #define SYSCLK_SRC_PLL0         2       //!< Phase Locked Loop 0
 #define SYSCLK_SRC_PLL1         3       //!< Phase Locked Loop 1
 #define SYSCLK_SRC_RC120M       4       //!< 120 MHz RC oscillator



 #define USBCLK_SRC_OSC0         1       //!< Use OSC0
 #define USBCLK_SRC_PLL0         2       //!< Use PLL0
 #define USBCLK_SRC_PLL1         3       //!< Use PLL1




 #define SYSCLK_OCD              AVR32_OCD_CLK_CPU

 #define SYSCLK_SYSTIMER         AVR32_SYSTIMER_CLK_CPU




 #define SYSCLK_FLASHCDW_DATA    (AVR32_FLASHCDW_CLK_HSB % 32)

 #define SYSCLK_PBA_BRIDGE       (AVR32_PBA_CLK_HSB % 32)

 #define SYSCLK_PBB_BRIDGE       (AVR32_PBB_CLK_HSB % 32)

 #define SYSCLK_USBC_DATA        (AVR32_USBC_CLK_HSB % 32)

 #define SYSCLK_PDCA_HSB         (AVR32_PDCA_CLK_HSB % 32)




 #define SYSCLK_PDCA_PBA         (AVR32_PDCA_CLK_PBA % 32)

 #define SYSCLK_INTC             (AVR32_INTC_CLK_PBA % 32)

 #define SYSCLK_PM               (AVR32_PM_CLK_PBA % 32)

 #define SYSCLK_AST              (AVR32_AST_CLK_PBA % 32)

 #define SYSCLK_WDT              (AVR32_WDT_CLK_PBA % 32)

 #define SYSCLK_EIC              (AVR32_EIC_CLK_PBA % 32)

 #define SYSCLK_GPIO             (AVR32_GPIO_CLK_PBA % 32)

 #define SYSCLK_USART0           (AVR32_USART0_CLK_PBA % 32)

 #define SYSCLK_USART1           (AVR32_USART1_CLK_PBA % 32)

 #define SYSCLK_USART2           (AVR32_USART2_CLK_PBA % 32)

 #define SYSCLK_SPI              (AVR32_SPI_CLK_PBA % 32)

 #define SYSCLK_TWIM             (AVR32_TWIM_CLK_PBA % 32)

 #define SYSCLK_TWIS             (AVR32_TWIS_CLK_PBA % 32)

 #define SYSCLK_PWMA             (AVR32_PWMA_CLK_PBA % 32)

 #define SYSCLK_IISC             (AVR32_IISC_CLK_PBA % 32)

 #define SYSCLK_TC               (AVR32_TC_CLK_PBA % 32)

 #define SYSCLK_ADCIFD           (AVR32_ADCIFD_CLK_PBA % 32)

 #define SYSCLK_SCIF             (AVR32_SCIF_CLK_PBA % 32)

 #define SYSCLK_FREQM            (AVR32_FREQM_CLK_PBA % 32)

 #define SYSCLK_CAT              (AVR32_CAT_CLK_PBA % 32)

 #define SYSCLK_GLOC             (AVR32_GLOC_CLK_PBA % 32)

 #define SYSCLK_AW               (AVR32_AW_CLK_PBA % 32)




 #define SYSCLK_USBC_REGS        (AVR32_USBC_CLK_PBB % 32)

 #define SYSCLK_HMATRIX          (AVR32_HMATRIX_CLK_PBB % 32)

 #define SYSCLK_FLASHCDW_REGS    (AVR32_FLASHCDW_CLK_PBB % 32)



 #ifndef __ASSEMBLY__

 #include <assert.h>
 #include <avr32/io.h>
 #include <osc.h>
 #include <pll.h>
 #include <genclk.h>

 // Use the slow clock (RCOSC) with no prescaling if config was empty.
 #ifndef CONFIG_SYSCLK_SOURCE
 # define CONFIG_SYSCLK_SOURCE    SYSCLK_SRC_RCSYS
 #endif /* CONFIG_SYSCLK_SOURCE */

 #ifndef CONFIG_SYSCLK_CPU_DIV
 # define CONFIG_SYSCLK_CPU_DIV   0
 #endif /* CONFIG_SYSCLK_CPU_DIV */

 #ifdef __DOXYGEN__
 # define CONFIG_SYSCLK_INIT_HSBMASK
 #endif

 #ifndef CONFIG_SYSCLK_PBA_DIV
 # define CONFIG_SYSCLK_PBA_DIV   0
 #endif /* CONFIG_SYSCLK_PBA_DIV */

 #ifndef CONFIG_SYSCLK_PBB_DIV
 # define CONFIG_SYSCLK_PBB_DIV   0
 #endif /* CONFIG_SYSCLK_PBB_DIV */

 #ifdef __DOXYGEN__
 # define CONFIG_SYSCLK_INIT_CPUMASK
 #endif

 #ifdef __DOXYGEN__
 # define CONFIG_SYSCLK_INIT_PBAMASK
 #endif

 #ifdef __DOXYGEN__
 # define CONFIG_SYSCLK_INIT_PBBMASK
 #endif

 #ifdef __DOXYGEN__
 # define CONFIG_USBCLK_SOURCE
 #endif

 #ifdef __DOXYGEN__
 # define CONFIG_USBCLK_DIV
 #endif


 #if (defined CONFIG_SYSCLK_DEFAULT_RETURNS_SLOW_OSC)
 extern bool sysclk_initialized;
 #endif
 static inline uint32_t sysclk_get_main_hz(void)
 {
 #if (defined CONFIG_SYSCLK_DEFAULT_RETURNS_SLOW_OSC)
     if (!sysclk_initialized ) {
         return OSC_RCSYS_NOMINAL_HZ;
     }
 #endif

     switch (CONFIG_SYSCLK_SOURCE) {
     case SYSCLK_SRC_RCSYS:
         return OSC_RCSYS_NOMINAL_HZ;

 #ifdef BOARD_OSC0_HZ
     case SYSCLK_SRC_OSC0:
         return BOARD_OSC0_HZ;
 #endif

 #ifdef CONFIG_PLL0_SOURCE
     case SYSCLK_SRC_PLL0:
         return pll_get_default_rate(0);
 #endif

 #ifdef CONFIG_PLL1_SOURCE
     case SYSCLK_SRC_PLL1:
         return pll_get_default_rate(1);
 #endif

     case SYSCLK_SRC_RC120M:
         return OSC_RC120M_NOMINAL_HZ;

     default:
         /* unhandled_case(CONFIG_SYSCLK_SOURCE); */
         return 0;
     }
 }

 static inline uint32_t sysclk_get_cpu_hz(void)
 {
     return sysclk_get_main_hz() >> CONFIG_SYSCLK_CPU_DIV;
 }

 static inline uint32_t sysclk_get_hsb_hz(void)
 {
     return sysclk_get_main_hz() >> CONFIG_SYSCLK_CPU_DIV;
 }

 static inline uint32_t sysclk_get_pba_hz(void)
 {
     return sysclk_get_main_hz() >> CONFIG_SYSCLK_PBA_DIV;
 }

 static inline uint32_t sysclk_get_pbb_hz(void)
 {
     return sysclk_get_main_hz() >> CONFIG_SYSCLK_PBB_DIV;
 }

 static inline uint32_t sysclk_get_peripheral_bus_hz(const volatile void *module)
 {
     /* Fallthroughs intended for modules sharing the same peripheral bus. */
     switch ((uintptr_t)module) {
     case AVR32_PDCA_ADDRESS:
     case AVR32_INTC_ADDRESS:
     case AVR32_PM_ADDRESS:
     case AVR32_AST_ADDRESS:
     case AVR32_WDT_ADDRESS:
     case AVR32_EIC_ADDRESS:
     case AVR32_GPIO_ADDRESS:
     case AVR32_USART0_ADDRESS:
     case AVR32_USART1_ADDRESS:
     case AVR32_USART2_ADDRESS:
     case AVR32_SPI_ADDRESS:
     case AVR32_TWIM_ADDRESS:
     case AVR32_TWIS_ADDRESS:
     case AVR32_PWMA_ADDRESS:
     case AVR32_IISC_ADDRESS:
     case AVR32_TC_ADDRESS:
     case AVR32_ADCIFD_ADDRESS:
     case AVR32_SCIF_ADDRESS:
     case AVR32_FREQM_ADDRESS:
     case AVR32_CAT_ADDRESS:
     case AVR32_GLOC_ADDRESS:
     case AVR32_AW_ADDRESS:
         return sysclk_get_pba_hz();

     case AVR32_USBC_ADDRESS:
     case AVR32_HMATRIXB_ADDRESS:
     case AVR32_FLASHCDW_ADDRESS:
         return sysclk_get_pbb_hz();

     default:
         Assert(false);
         return 0;
     }
 }


 extern void sysclk_priv_enable_module(unsigned int bus_id,
         unsigned int module_index);
 extern void sysclk_priv_disable_module(unsigned int bus_id,
         unsigned int module_index);



 static inline void sysclk_enable_cpu_module(unsigned int index)
 {
     sysclk_priv_enable_module(AVR32_PM_CLK_GRP_CPU, index);
 }

 static inline void sysclk_disable_cpu_module(unsigned int index)
 {
     sysclk_priv_disable_module(AVR32_PM_CLK_GRP_CPU, index);
 }

 static inline void sysclk_enable_hsb_module(unsigned int index)
 {
     sysclk_priv_enable_module(AVR32_PM_CLK_GRP_HSB, index);
 }

 static inline void sysclk_disable_hsb_module(unsigned int index)
 {
     sysclk_priv_disable_module(AVR32_PM_CLK_GRP_HSB, index);
 }

 static inline void sysclk_enable_pba_module(unsigned int index)
 {
     sysclk_priv_enable_module(AVR32_PM_CLK_GRP_PBA, index);
 }

 static inline void sysclk_disable_pba_module(unsigned int index)
 {
     sysclk_priv_disable_module(AVR32_PM_CLK_GRP_PBA, index);
 }

 static inline void sysclk_enable_pbb_module(unsigned int index)
 {
     sysclk_priv_enable_module(AVR32_PM_CLK_GRP_PBB, index);
 }

 static inline void sysclk_disable_pbb_module(unsigned int index)
 {
     sysclk_priv_disable_module(AVR32_PM_CLK_GRP_PBB, index);
 }

 static inline void sysclk_enable_peripheral_clock(const volatile void *module)
 {
     switch ((uintptr_t)module) {
     case AVR32_PDCA_ADDRESS:
         sysclk_enable_hsb_module(SYSCLK_PDCA_HSB);
         sysclk_enable_pba_module(SYSCLK_PDCA_PBA);
         break;

     case AVR32_INTC_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_INTC);
         break;

     case AVR32_PM_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_PM);
         break;

     case AVR32_AST_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_AST);
         break;

     case AVR32_WDT_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_WDT);
         break;

     case AVR32_EIC_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_EIC);
         break;

     case AVR32_GPIO_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_GPIO);
         break;

     case AVR32_USART0_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_USART0);
         break;

     case AVR32_USART1_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_USART1);
         break;

     case AVR32_USART2_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_USART2);
         break;

     case AVR32_SPI_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_SPI);
         break;

     case AVR32_TWIM_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_TWIM);
         break;

     case AVR32_TWIS_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_TWIS);
         break;

     case AVR32_PWMA_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_PWMA);
         break;

     case AVR32_IISC_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_IISC);
         break;

     case AVR32_TC_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_TC);
         break;

     case AVR32_ADCIFD_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_ADCIFD);
         break;

     case AVR32_SCIF_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_SCIF);
         break;

     case AVR32_FREQM_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_FREQM);
         break;

     case AVR32_CAT_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_CAT);
         break;

     case AVR32_GLOC_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_GLOC);
         break;

     case AVR32_AW_ADDRESS:
         sysclk_enable_pba_module(SYSCLK_AW);
         break;

     case AVR32_USBC_ADDRESS:
         sysclk_enable_hsb_module(SYSCLK_USBC_DATA);
         sysclk_enable_pbb_module(SYSCLK_USBC_REGS);
         break;

     case AVR32_HMATRIXB_ADDRESS:
         sysclk_enable_pbb_module(SYSCLK_HMATRIX);
         break;

     case AVR32_FLASHCDW_ADDRESS:
         sysclk_enable_hsb_module(SYSCLK_FLASHCDW_DATA);
         sysclk_enable_pbb_module(SYSCLK_FLASHCDW_REGS);
         break;

     default:
         Assert(false);
         return;
     }
 }

 static inline void sysclk_disable_peripheral_clock(const volatile void *module)
 {
     switch ((uintptr_t)module) {
     case AVR32_PDCA_ADDRESS:
         sysclk_disable_hsb_module(SYSCLK_PDCA_HSB);
         sysclk_disable_pba_module(SYSCLK_PDCA_PBA);
         break;

     case AVR32_INTC_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_INTC);
         break;

     case AVR32_PM_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_PM);
         break;

     case AVR32_AST_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_AST);
         break;

     case AVR32_WDT_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_WDT);
         break;

     case AVR32_EIC_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_EIC);
         break;

     case AVR32_GPIO_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_GPIO);
         break;

     case AVR32_USART0_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_USART0);
         break;

     case AVR32_USART1_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_USART1);
         break;

     case AVR32_USART2_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_USART2);
         break;

     case AVR32_SPI_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_SPI);
         break;

     case AVR32_TWIM_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_TWIM);
         break;

     case AVR32_TWIS_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_TWIS);
         break;

     case AVR32_PWMA_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_PWMA);
         break;

     case AVR32_IISC_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_IISC);
         break;

     case AVR32_TC_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_TC);
         break;

     case AVR32_ADCIFD_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_ADCIFD);
         break;

     case AVR32_SCIF_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_SCIF);
         break;

     case AVR32_FREQM_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_FREQM);
         break;

     case AVR32_CAT_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_CAT);
         break;

     case AVR32_GLOC_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_GLOC);
         break;

     case AVR32_AW_ADDRESS:
         sysclk_disable_pba_module(SYSCLK_AW);
         break;

     case AVR32_USBC_ADDRESS:
         sysclk_disable_hsb_module(SYSCLK_USBC_DATA);
         sysclk_disable_pbb_module(SYSCLK_USBC_REGS);
         break;

     case AVR32_HMATRIXB_ADDRESS:
         sysclk_disable_pbb_module(SYSCLK_HMATRIX);
         break;

     case AVR32_FLASHCDW_ADDRESS:
         sysclk_disable_hsb_module(SYSCLK_FLASHCDW_DATA);
         sysclk_disable_pbb_module(SYSCLK_FLASHCDW_REGS);
         break;

     default:
         Assert(false);
         return;
     }
 }




 extern void sysclk_set_prescalers(unsigned int cpu_shift,
         unsigned int pba_shift, unsigned int pbb_shift);
 extern void sysclk_set_source(uint_fast8_t src);


 #if defined(CONFIG_USBCLK_SOURCE) || defined(__DOXYGEN__)

 #if CONFIG_USBCLK_SOURCE==USBCLK_SRC_OSC0
 #  define USBCLK_STARTUP_TIMEOUT    (OSC0_STARTUP_TIMEOUT*(1000000/AVR32_SCIF_RCOSC_FREQUENCY))
 #elif CONFIG_USBCLK_SOURCE==USBCLK_SRC_PLL0
 #  if CONFIG_PLL0_SOURCE==PLL_SRC_OSC0
 #    define USBCLK_STARTUP_TIMEOUT    (OSC0_STARTUP_TIMEOUT*(1000000/AVR32_SCIF_RCOSC_FREQUENCY))
 #  else
 #    error Unknown value for CONFIG_PLL0_SOURCE, see conf_clock.h.
 #  endif
 #elif CONFIG_USBCLK_SOURCE==USBCLK_SRC_PLL1
 #  if CONFIG_PLL1_SOURCE==PLL_SRC_OSC0
 #    define USBCLK_STARTUP_TIMEOUT    (OSC0_STARTUP_TIMEOUT*(1000000/AVR32_SCIF_RCOSC_FREQUENCY))
 #  else
 #    error Unknown value for CONFIG_PLL1_SOURCE, see conf_clock.h.
 #  endif
 #else
 #  error Unknown value for CONFIG_USBCLK_SOURCE, see conf_clock.h.
 #endif

 extern void sysclk_enable_usb(void);
 extern void sysclk_disable_usb(void);
 #endif

 extern void sysclk_init(void);

 #endif /* !__ASSEMBLY__ */


 #ifdef __cplusplus
 }
 #endif

 #endif /* CHIP_SYSCLK_H_INCLUDED */

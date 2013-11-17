
 #ifndef _PM_UC3D_H_
 #define _PM_UC3D_H_

 #ifdef __cplusplus
 extern "C" {
 #endif

 #include <avr32/io.h>
 #include "compiler.h"


 typedef enum
 {
   PM_CLK_SRC_SLOW = AVR32_PM_MCSEL_SLOW,
   PM_CLK_SRC_OSC0 = AVR32_PM_MCSEL_OSC0,
   PM_CLK_SRC_RC120M = 4, //AVR32_PM_MCSEL_RC120M,
   PM_CLK_SRC_PLL0 = 2, //AVR32_PM_MCSEL_PLL0,
   PM_CLK_SRC_PLL1 = 3, // AVR32_PM_MCSEL_PLL1,
   PM_CLK_SRC_RCRIPOSC = AVR32_PM_MCSEL_CRIPOSC,
   PM_CLK_SRC_INVALID
 } pm_clk_src_t;

 typedef enum
 {
   PM_CLK_DOMAIN_0 = AVR32_PM_CLK_GRP_CPU,
   PM_CLK_DOMAIN_1 = AVR32_PM_CLK_GRP_HSB,
   PM_CLK_DOMAIN_2 = AVR32_PM_CLK_GRP_PBA,
   PM_CLK_DOMAIN_3 = AVR32_PM_CLK_GRP_PBB,
   PM_CLK_DOMAIN_INVALID
 } pm_clk_domain_t;


 typedef enum
 {
   PM_CKSEL_DIVRATIO_2 = 0,  // Divide the main clock by 2^1
   PM_CKSEL_DIVRATIO_4,      // Divide the main clock by 2^2
   PM_CKSEL_DIVRATIO_8,      // Divide the main clock by 2^3
   PM_CKSEL_DIVRATIO_16,     // Divide the main clock by 2^4
   PM_CKSEL_DIVRATIO_32,     // Divide the main clock by 2^5
   PM_CKSEL_DIVRATIO_64,     // Divide the main clock by 2^6
   PM_CKSEL_DIVRATIO_128,    // Divide the main clock by 2^7
   PM_CKSEL_DIVRATIO_256,    // Divide the main clock by 2^8
   PM_CKSEL_DIVRATIO_ERROR
 } pm_divratio_t;

 typedef enum
 {
   PM_CPUSEL_DIVRATIO_MAX = AVR32_PM_CPUSEL_CPUSEL_MASK >> AVR32_PM_CPUSEL_CPUSEL_OFFSET,
   PM_HSBSEL_DIVRATIO_MAX = AVR32_PM_HSBSEL_HSBSEL_MASK >> AVR32_PM_HSBSEL_HSBSEL_OFFSET,
   PM_PBASEL_DIVRATIO_MAX = AVR32_PM_PBASEL_PBSEL_MASK >> AVR32_PM_PBASEL_PBSEL_OFFSET,
   PM_PBBSEL_DIVRATIO_MAX = AVR32_PM_PBBSEL_PBSEL_MASK >> AVR32_PM_PBBSEL_PBSEL_OFFSET
 } pm_divratio_max_t;

 #define PM_POLL_TIMEOUT 100000

 #define PM_NOT_SUPPORTED (-10000)


 #define PM_UNLOCK(reg)  (AVR32_PM.unlock = (unsigned long)(AVR32_PM_UNLOCK_KEY_VALUE << AVR32_PM_UNLOCK_KEY_OFFSET)|(reg))




 extern long pm_set_mclk_source(pm_clk_src_t src);

 extern long pm_config_mainclk_safety(bool cfd, bool ocp, bool final);

 extern long pm_set_clk_domain_div(pm_clk_domain_t clock_domain, pm_divratio_t divratio);

 extern long pm_disable_clk_domain_div(pm_clk_domain_t clock_domain);

 extern void pm_set_all_cksel( unsigned long main_clock_f_hz, unsigned long cpu_f_hz,
                               unsigned long pba_f_hz, unsigned long pbb_f_hz );

 extern long pm_wait_for_clk_ready(void);





 extern long pm_enable_module(unsigned long module);

 extern long pm_disable_module(unsigned long module);





 #define SLEEP(sleep_mode)  {__asm__ __volatile__ ("sleep "STRINGZ(sleep_mode));}

 #ifdef __GNUC__
 __attribute__((__always_inline__))
 #endif
 static inline unsigned long pm_get_wake_cause(void)
 {
   return AVR32_PM.wcause;
 }

 #ifdef __GNUC__
 __attribute__((__always_inline__))
 #endif
 static inline void pm_asyn_wake_up_enable(unsigned long awen_mask)
 {
   AVR32_PM.awen |= awen_mask;
 }

 #ifdef __GNUC__
 __attribute__((__always_inline__))
 #endif
 static inline void pm_asyn_wake_up_disable(unsigned long awen_mask)
 {
   AVR32_PM.awen &= ~awen_mask;
 }






 #ifdef __GNUC__
 __attribute__((__always_inline__))
 #endif
 static inline unsigned long pm_get_reset_cause(void)
 {
   return AVR32_PM.rcause;
 }






 #ifdef __GNUC__
 __attribute__((__always_inline__))
 #endif
 static inline void pm_enable_interrupts(unsigned long mask)
 {
   AVR32_PM.ier |= mask;
 }

 #ifdef __GNUC__
 __attribute__((__always_inline__))
 #endif
 static inline void pm_disable_interrupts(unsigned long mask)
 {
   AVR32_PM.idr |= mask;
 }

 #ifdef __GNUC__
 __attribute__((__always_inline__))
 #endif
 static inline unsigned long pm_get_enabled_interrupts(void)
 {
   return(AVR32_PM.imr);
 }

 #ifdef __GNUC__
 __attribute__((__always_inline__))
 #endif
 static inline unsigned long pm_get_interrupts_status(void)
 {
   return(AVR32_PM.isr);
 }

 #ifdef __GNUC__
 __attribute__((__always_inline__))
 #endif
 static inline void pm_clear_interrupt_status(unsigned long mask)
 {
   AVR32_PM.icr |= mask;
 }






 #ifdef __GNUC__
 __attribute__((__always_inline__))
 #endif
 static inline unsigned long pm_get_status(void)
 {
   return AVR32_PM.sr;
 }


 #ifdef __cplusplus
 }
 #endif

 #endif  // _PM_UC3D_H_

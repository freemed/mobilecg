
 #ifndef _SCIF_UC3D_H_
 #define _SCIF_UC3D_H_

 #ifdef __cplusplus
 extern "C" {
 #endif

 #include "compiler.h"


 #define SCIF_EXT_CRYSTAL_MIN_FREQ_HZ  4000000

 #define SCIF_EXT_CRYSTAL_MAX_FREQ_HZ  20000000

 typedef enum
 {
   SCIF_GCCTRL_SLOWCLOCK = AVR32_SCIF_GCCTRL_OSCSEL_RCSYS,
   SCIF_GCCTRL_OSC32K    = AVR32_SCIF_GCCTRL_OSCSEL_OSC32K,
   SCIF_GCCTRL_OSC0      = AVR32_SCIF_GCCTRL_OSCSEL_OSC0,
   SCIF_GCCTRL_PLL0      = AVR32_SCIF_GCCTRL_OSCSEL_PLL0,
   SCIF_GCCTRL_PLL1      = AVR32_SCIF_GCCTRL_OSCSEL_PLL1,
   SCIF_GCCTRL_CPUCLOCK  = AVR32_SCIF_GCCTRL_OSCSEL_CLK_CPU,
   SCIF_GCCTRL_HSBCLOCK  = AVR32_SCIF_GCCTRL_OSCSEL_CLK_HSB,
   SCIF_GCCTRL_PBACLOCK  = AVR32_SCIF_GCCTRL_OSCSEL_CLK_PBA,
   SCIF_GCCTRL_PBBCLOCK  = AVR32_SCIF_GCCTRL_OSCSEL_CLK_PBB,
   SCIF_GCCTRL_RC120M    = AVR32_SCIF_GCCTRL_OSCSEL_RC120M,
   SCIF_GCCTRL_OSCSEL_INVALID
 } scif_gcctrl_oscsel_t;

 #define SCIF_POLL_TIMEOUT             100000

 #define SCIF_NOT_SUPPORTED            (-10000)


 typedef enum
 {
   SCIF_OSC0  = 0,
 } scif_osc_t;

 typedef enum
 {
   SCIF_PLL0  = 0,
   SCIF_PLL1  = 1
 } scif_pll_t;

 typedef enum
 {
   SCIF_OSC_MODE_EXT_CLK = 0,            // For both OSC0 & OSC32
   SCIF_OSC_MODE_2PIN_CRYSTAL = 1,       // For both OSC0 & OSC32
   SCIF_OSC_MODE_2PIN_CRYSTAL_HICUR = 2, // For OSC32 only
 } scif_osc_mode_t;

 typedef struct
 {
   unsigned long   freq_hz;
   scif_osc_mode_t mode;
   unsigned char   startup;
   unsigned char   gain;
 } scif_osc_opt_t;

 typedef struct
 {
   unsigned char   pll_freq;
   unsigned char   pll_wbwdisable;
   unsigned char   pll_div2;
   unsigned int    mul;
   unsigned int    div;
   unsigned int    lockcount;
   unsigned char   osc;
 } scif_pll_opt_t;

 typedef struct
 {
   unsigned long   freq_hz;
   scif_osc_mode_t mode;
   unsigned char   startup;
 } scif_osc32_opt_t;


 typedef struct
 {
   scif_gcctrl_oscsel_t clock_source;
   unsigned int divider;
   unsigned int diven;
 } scif_gclk_opt_t;

 #define SCIF_UNLOCK(reg)  (AVR32_SCIF.unlock = (AVR32_SCIF_UNLOCK_KEY_VALUE << AVR32_SCIF_UNLOCK_KEY_OFFSET)|(reg))



  #if defined (__GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void scif_enable_interrupts(unsigned long mask)
 {
   AVR32_SCIF.ier = mask;
 }

 #if defined (__GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void scif_disable_interrupts(unsigned long mask)
 {
   AVR32_SCIF.idr = mask;
 }

 #if defined (__GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline unsigned long scif_get_enabled_interrupts(void)
 {
   return(AVR32_SCIF.imr);
 }

 #if defined (__GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline unsigned long scif_get_interrupts_status(void)
 {
   return(AVR32_SCIF.isr);
 }

 #if defined (__GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void scif_clear_interrupts_status(unsigned long mask)
 {
   AVR32_SCIF.icr = mask;
 }





 #if defined (__GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline unsigned long scif_get_pclk_status(void)
 {
   return(AVR32_SCIF.pclksr);
 }





 extern long int scif_start_osc(scif_osc_t osc, const scif_osc_opt_t *opt, bool wait_for_ready);

 extern bool scif_is_osc_ready(scif_osc_t osc);

 extern long int scif_stop_osc(scif_osc_t osc);

 extern long int scif_configure_osc_crystalmode(scif_osc_t osc, unsigned int fcrystal);

 extern long int scif_configure_osc_extmode(scif_osc_t osc);

 extern long int scif_enable_osc(scif_osc_t osc, unsigned int startup, bool wait_for_ready);

 extern long int scif_enable_extosc(scif_osc_t osc);





 extern long int scif_pll_setup(scif_pll_t pll, const scif_pll_opt_t opt);

 extern long int scif_pll_enable(scif_pll_t pll);

 extern long int scif_pll_disable(scif_pll_t pll);


 extern long int scif_wait_for_pll_locked(scif_pll_t pll);




 extern long int scif_start_osc32(const scif_osc32_opt_t *opt, bool wait_for_ready);

 #if defined (__GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline bool scif_is_osc32_ready()
 {
   return((AVR32_SCIF.pclksr & AVR32_SCIF_PCLKSR_OSC32RDY_MASK)>>AVR32_SCIF_PCLKSR_OSC32RDY_OFFSET);
 }


 extern long int scif_stop_osc32();





 extern void scif_bod18_enable_irq(void);


 extern void scif_bod18_disable_irq(void);


 extern void scif_bod18_clear_irq(void);


 extern unsigned long scif_bod18_get_irq_status(void);


 extern unsigned long scif_bod18_get_irq_enable_bit(void);


 extern unsigned long scif_bod18_get_level(void);




 extern void scif_start_rc120M(void);

 extern void scif_stop_rc120M(void);





 extern long int scif_start_gclk(unsigned int gclk, const scif_gclk_opt_t *opt);

 extern long int scif_stop_gclk(unsigned int gclk);

 extern long int scif_gc_setup(unsigned int gclk, scif_gcctrl_oscsel_t clk_src, unsigned int diven, unsigned int divfactor);

 extern long int scif_gc_enable(unsigned int gclk);





 extern unsigned long scif_read_gplp(unsigned long gplp);


 extern void scif_write_gplp(int gplp, unsigned long value);



 #ifdef __cplusplus
 }
 #endif

 #endif  // _SCIF_UC3D_H_

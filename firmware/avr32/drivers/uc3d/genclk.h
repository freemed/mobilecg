
 #ifndef CHIP_GENCLK_H_INCLUDED
 #define CHIP_GENCLK_H_INCLUDED

 #include <osc.h>
 #include <pll.h>



 #define GENCLK_DIV_MAX  256

 #ifndef __ASSEMBLY__

 #include <assert.h>
 #include <stdint.h>
 #include <avr32/io.h>

 enum genclk_source {
     GENCLK_SRC_RCSYS        = 0,   
     GENCLK_SRC_OSC32K       = 1,   
     GENCLK_SRC_OSC0         = 2,   
     GENCLK_SRC_PLL0         = 3,   
     GENCLK_SRC_PLL1         = 4,   
     GENCLK_SRC_CLK_CPU      = 5,   
     GENCLK_SRC_CLK_HSB      = 6,   
     GENCLK_SRC_CLK_PBA      = 7,   
     GENCLK_SRC_CLK_PBB      = 8,   
     GENCLK_SRC_RC120M       = 9    

 };


 struct genclk_config {
     uint32_t ctrl;
 };

 static inline void genclk_config_defaults(struct genclk_config *cfg,
         unsigned int id)
 {
     cfg->ctrl = 0;
 }

 static inline void genclk_config_read(struct genclk_config *cfg,
         unsigned int id)
 {
     cfg->ctrl = AVR32_SCIF.gcctrl[id];
 }

 static inline void genclk_config_write(const struct genclk_config *cfg,
         unsigned int id)
 {
     AVR32_SCIF.gcctrl[id] = cfg->ctrl;
 }

 static inline void genclk_config_set_source(struct genclk_config *cfg,
         enum genclk_source src)
 {
     cfg->ctrl = (cfg->ctrl & ~AVR32_SCIF_GCCTRL_OSCSEL_MASK)
             | (src << AVR32_SCIF_GCCTRL_OSCSEL);
 }

 static inline void genclk_config_set_divider(struct genclk_config *cfg,
         unsigned int divider)
 {
     Assert(divider > 0 && divider <= GENCLK_DIV_MAX);

     /* Clear all the bits we're about to modify */
     cfg->ctrl &= ~(AVR32_SCIF_GCCTRL_DIVEN_MASK
             | AVR32_SCIF_GCCTRL_DIV_MASK);

     if (divider > 1) {
         cfg->ctrl |= 1U << AVR32_SCIF_GCCTRL_DIVEN;
         cfg->ctrl |= (((divider + 1) / 2) - 1) << AVR32_SCIF_GCCTRL_DIV;
     }
 }

 static inline void genclk_enable(const struct genclk_config *cfg,
         unsigned int id)
 {
     AVR32_SCIF.gcctrl[id] = cfg->ctrl | (1U << AVR32_SCIF_GCCTRL_CEN);
 }

 static inline void genclk_disable(unsigned int id)
 {
     AVR32_SCIF.gcctrl[id] = 0;
 }

 static inline void genclk_enable_source(enum genclk_source src)
 {
     switch (src) {
     case GENCLK_SRC_RCSYS:
     case GENCLK_SRC_CLK_CPU:
     case GENCLK_SRC_CLK_HSB:
     case GENCLK_SRC_CLK_PBA:
     case GENCLK_SRC_CLK_PBB:
         // Nothing to do
         break;

     case GENCLK_SRC_OSC32K:
         if (!osc_is_ready(OSC_ID_OSC32)) {
             osc_enable(OSC_ID_OSC32);
             osc_wait_ready(OSC_ID_OSC32);
         }
         break;

     case GENCLK_SRC_RC120M:
         if (!osc_is_ready(OSC_ID_RC120M)) {
             osc_enable(OSC_ID_RC120M);
             osc_wait_ready(OSC_ID_RC120M);
         }
         break;

 #ifdef BOARD_OSC0_HZ
     case GENCLK_SRC_OSC0:
         if (!osc_is_ready(OSC_ID_OSC0)) {
             osc_enable(OSC_ID_OSC0);
             osc_wait_ready(OSC_ID_OSC0);
         }
         break;
 #endif

 #ifdef CONFIG_PLL0_SOURCE
     case GENCLK_SRC_PLL0: {
         pll_enable_config_defaults(0);
         break;
     }
 #endif

 #ifdef CONFIG_PLL1_SOURCE
     case GENCLK_SRC_PLL1: {
         pll_enable_config_defaults(1);
         break;
     }
 #endif

     default:
         Assert(false);
         break;
     }
 }

 #endif /* __ASSEMBLY__ */


 #endif /* CHIP_GENCLK_H_INCLUDED */

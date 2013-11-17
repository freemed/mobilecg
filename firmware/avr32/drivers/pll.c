
 #include <assert.h>
 #include <avr32/io.h>
 #include <compiler.h>
 #include <pll.h>

 void pll_config_write(const struct pll_config *cfg, unsigned int pll_id)
 {
     irqflags_t flags;

     Assert(pll_id < NR_PLLS);

     flags = cpu_irq_save();
     AVR32_SCIF.unlock = 0xaa000000 | (AVR32_SCIF_PLL + (4 * pll_id));
     AVR32_SCIF.pll[pll_id] = cfg->ctrl;
     cpu_irq_restore(flags);
 }

 void pll_enable(const struct pll_config *cfg, unsigned int pll_id)
 {
     irqflags_t flags;

     Assert(pll_id < NR_PLLS);

     flags = cpu_irq_save();
     AVR32_SCIF.unlock = 0xaa000000 | (AVR32_SCIF_PLL + (4 * pll_id));
     AVR32_SCIF.pll[pll_id] = cfg->ctrl | (1U << AVR32_SCIF_PLLEN);
     cpu_irq_restore(flags);
 }

 void pll_disable(unsigned int pll_id)
 {
     irqflags_t flags;

     Assert(pll_id < NR_PLLS);

     flags = cpu_irq_save();
     AVR32_SCIF.unlock = 0xaa000000 | (AVR32_SCIF_PLL + (4 * pll_id));
     AVR32_SCIF.pll[pll_id] = 0;
     cpu_irq_restore(flags);
 }

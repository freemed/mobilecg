
 #ifndef CLK_GENCLK_H_INCLUDED
 #define CLK_GENCLK_H_INCLUDED

 #include <parts.h>

 #if (UC3A0 || UC3A1)
 # include "uc3a0_a1/genclk.h"
 #elif UC3A3
 # include "uc3a3_a4/genclk.h"
 #elif UC3B
 # include "uc3b0_b1/genclk.h"
 #elif UC3C
 # include "uc3c/genclk.h"
 #elif UC3D
 # include "uc3d/genclk.h"
 #elif UC3L
 # include "uc3l/genclk.h"
 #else
 # error Unsupported chip type
 #endif








 static inline void genclk_enable_config(unsigned int id, enum genclk_source src, unsigned int divider)
 {
     struct genclk_config gcfg;

     genclk_config_defaults(&gcfg, id);
     genclk_enable_source(src);
     genclk_config_set_source(&gcfg, src);
     genclk_config_set_divider(&gcfg, divider);
     genclk_enable(&gcfg, id);
 }


 #endif /* CLK_GENCLK_H_INCLUDED */


 #ifndef CLK_PLL_H_INCLUDED
 #define CLK_PLL_H_INCLUDED

 #include <parts.h>
 #include "conf_clock.h"

 #if (UC3A0 || UC3A1)
 # include "uc3a0_a1/pll.h"
 #elif UC3A3
 # include "uc3a3_a4/pll.h"
 #elif UC3B
 # include "uc3b0_b1/pll.h"
 #elif UC3C
 # include "uc3c/pll.h"
 #elif UC3D
 # include "uc3d/pll.h"
 #elif (UC3L0128 || UC3L0256 || UC3L3_L4)
 # include "uc3l/pll.h"
 #elif XMEGA
 # include "xmega/pll.h"
 #else
 # error Unsupported chip type
 #endif











 static inline int pll_wait_for_lock(unsigned int pll_id)
 {
     Assert(pll_id < NR_PLLS);

     while (!pll_is_locked(pll_id)) {
         /* Do nothing */
     }

     return 0;
 }



 #endif /* CLK_PLL_H_INCLUDED */

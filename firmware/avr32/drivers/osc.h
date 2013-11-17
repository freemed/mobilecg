
 #ifndef OSC_H_INCLUDED
 #define OSC_H_INCLUDED

 #include <parts.h>
 #include "conf_clock.h"

 #if (UC3A0 || UC3A1)
 # include "uc3a0_a1/osc.h"
 #elif UC3A3
 # include "uc3a3_a4/osc.h"
 #elif UC3B
 # include "uc3b0_b1/osc.h"
 #elif UC3C
 # include "uc3c/osc.h"
 #elif UC3D
 # include "uc3d/osc.h"
 #elif UC3L
 # include "uc3l/osc.h"
 #elif XMEGA
 # include "xmega/osc.h"
 #else
 # error Unsupported chip type
 #endif




 #ifndef __ASSEMBLY__

 static inline void osc_wait_ready(uint8_t id)
 {
     while (!osc_is_ready(id)) {
         /* Do nothing */
     }
 }

 #endif /* __ASSEMBLY__ */



 #endif /* OSC_H_INCLUDED */

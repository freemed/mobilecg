
 #ifndef SYSCLK_H_INCLUDED
 #define SYSCLK_H_INCLUDED

 #include <parts.h>
 #include "conf_clock.h"

 #if (UC3A0 || UC3A1)
 # include "uc3a0_a1/sysclk.h"
 #elif UC3A3
 # include "uc3a3_a4/sysclk.h"
 #elif UC3B
 # include "uc3b0_b1/sysclk.h"
 #elif UC3C
 # include "uc3c/sysclk.h"
 #elif UC3D
 # include "uc3d/sysclk.h"
 #elif UC3L
 # include "uc3l/sysclk.h"
 #elif XMEGA
 # include "xmega/sysclk.h"
 #else
 # error Unsupported chip type
 #endif






 #endif /* SYSCLK_H_INCLUDED */

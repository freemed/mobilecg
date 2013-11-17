
 #ifndef SLEEP_H
 #define SLEEP_H

 #ifdef __cplusplus
 extern "C" {
 #endif

 #include <compiler.h>

 #ifndef AVR32_PM_SMODE_GMCLEAR_MASK
 #define AVR32_PM_SMODE_GMCLEAR_MASK      0x80
 #else
 #warning Define already present in the system toolchain header files!
 #endif

 #if defined(__DOXYGEN__)

 #endif

 #if (UC3A || UC3B)  // For AVR UC3 A0/A1, UC3 B, UC3 A3 series

 # ifndef AVR32_PM_SMODE_DEEPSTOP
 #  define AVR32_PM_SMODE_DEEPSTOP          0x00000004
 # endif
 # include "pm.h"
 #elif UC3C          // For AVR UC3 C series
 # include "pm_uc3c.h"
 #elif UC3D          // For AVR UC3 D series
 # include "pm_uc3d.h"
 #elif UC3L          // For AVR UC3 L series
 # include "pm_uc3l.h"
 #else
 # error Unsupported AVR UC3 series.
 #endif

 static inline void pm_sleep(int sleep_mode)
 {
     switch (sleep_mode) {
     case AVR32_PM_SMODE_IDLE:
         SLEEP(AVR32_PM_SMODE_IDLE);
         break;
     case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_IDLE:
         SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_IDLE);
         break;
     case AVR32_PM_SMODE_FROZEN:
         SLEEP(AVR32_PM_SMODE_FROZEN);
         break;
     case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_FROZEN:
         SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_FROZEN);
         break;
     case AVR32_PM_SMODE_STANDBY:
         SLEEP(AVR32_PM_SMODE_STANDBY);
         break;
     case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STANDBY:
         SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STANDBY);
         break;
     case AVR32_PM_SMODE_STOP:
         SLEEP(AVR32_PM_SMODE_STOP);
         break;
     case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STOP:
         SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STOP);
         break;
     case AVR32_PM_SMODE_DEEPSTOP:
         SLEEP(AVR32_PM_SMODE_DEEPSTOP);
         break;
     case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_DEEPSTOP:
         SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_DEEPSTOP);
         break;
     case AVR32_PM_SMODE_STATIC:
         SLEEP(AVR32_PM_SMODE_STATIC);
         break;
     case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STATIC:
         SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_STATIC);
         break;
 #if UC3L
     case AVR32_PM_SMODE_SHUTDOWN:
         SLEEP(AVR32_PM_SMODE_SHUTDOWN);
         break;
     case AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_SHUTDOWN:
         SLEEP(AVR32_PM_SMODE_GMCLEAR_MASK | AVR32_PM_SMODE_SHUTDOWN);
         break;
 #endif
     default:
         break;
     }
 }



 #ifdef __cplusplus
 }
 #endif

 #endif /* SLEEP_H */

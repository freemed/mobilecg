
 #ifndef UTILS_INTERRUPT_H
 #define UTILS_INTERRUPT_H

 #include <parts.h>

 #if XMEGA || MEGA
 #  include "interrupt/interrupt_avr8.h"
 #elif UC3
 #  include "interrupt/interrupt_avr32.h"
 #else
 #  error Unsupported device.
 #endif

 #if defined(__DOXYGEN__)

 #  define CONFIG_INTERRUPT_FORCE_INTC
 #endif





 #endif /* UTILS_INTERRUPT_H */

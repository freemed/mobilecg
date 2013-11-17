
 #ifndef SLEEPMGR_H
 #define SLEEPMGR_H

 #include <compiler.h>
 #include <sleep.h>
 #include <parts.h>

 #if defined(XMEGA)
 # include "xmega/sleepmgr.h"
 #elif (defined(__GNUC__) && defined(__AVR32__)) || (defined(__ICCAVR32__) || defined(__AAVR32__))
 # include "uc3/sleepmgr.h"
 #else
 # error Unsupported device.
 #endif

 #if defined(__DOXYGEN__) && !defined(CONFIG_SLEEPMGR_ENABLE)
 #  define CONFIG_SLEEPMGR_ENABLE
 #endif

 static inline void sleepmgr_init(void)
 {
 #ifdef CONFIG_SLEEPMGR_ENABLE
     uint8_t i;

     for (i = 0; i < SLEEPMGR_NR_OF_MODES - 1; i++) {
         sleepmgr_locks[i] = 0;
     }
     sleepmgr_locks[SLEEPMGR_NR_OF_MODES - 1] = 1;
 #endif /* CONFIG_SLEEPMGR_ENABLE */
 }

 static inline void sleepmgr_lock_mode(enum sleepmgr_mode mode)
 {
 #ifdef CONFIG_SLEEPMGR_ENABLE
     irqflags_t flags;

     Assert(sleepmgr_locks[mode] < 0xff);

     // Enter a critical section
     flags = cpu_irq_save();

     ++sleepmgr_locks[mode];

     // Leave the critical section
     cpu_irq_restore(flags);
 #endif /* CONFIG_SLEEPMGR_ENABLE */
 }

 static inline void sleepmgr_unlock_mode(enum sleepmgr_mode mode)
 {
 #ifdef CONFIG_SLEEPMGR_ENABLE
     irqflags_t flags;

     Assert(sleepmgr_locks[mode]);

     // Enter a critical section
     flags = cpu_irq_save();

     --sleepmgr_locks[mode];

     // Leave the critical section
     cpu_irq_restore(flags);
 #endif /* CONFIG_SLEEPMGR_ENABLE */
 }

 static inline enum sleepmgr_mode sleepmgr_get_sleep_mode(void)
 {
     enum sleepmgr_mode sleep_mode = SLEEPMGR_ACTIVE;

 #ifdef CONFIG_SLEEPMGR_ENABLE
     uint8_t *lock_ptr = sleepmgr_locks;

     // Find first non-zero lock count, starting with the shallowest modes.
     while (!(*lock_ptr)) {
         lock_ptr++;
         sleep_mode = (enum sleepmgr_mode)((int)sleep_mode+1);
     }

     // Catch the case where one too many sleepmgr_unlock_mode() call has been
     // performed on the deepest sleep mode.
     Assert((uintptr_t)(lock_ptr - sleepmgr_locks) < SLEEPMGR_NR_OF_MODES);

 #endif /* CONFIG_SLEEPMGR_ENABLE */

     return sleep_mode;
 }

 static inline void sleepmgr_enter_sleep(void)
 {
 #ifdef CONFIG_SLEEPMGR_ENABLE
     enum sleepmgr_mode sleep_mode;

     cpu_irq_disable();

     // Find the deepest allowable sleep mode
     sleep_mode = sleepmgr_get_sleep_mode();
     // Return right away if first mode (ACTIVE) is locked.
     if (sleep_mode==SLEEPMGR_ACTIVE) {
         cpu_irq_enable();
         return;
     }
     // Enter the deepest allowable sleep mode with interrupts enabled
     sleepmgr_sleep(sleep_mode);
 #else
     cpu_irq_enable();
 #endif /* CONFIG_SLEEPMGR_ENABLE */
 }



 #endif /* SLEEPMGR_H */

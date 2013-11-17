
 #ifndef UC3_SLEEPMGR_H
 #define UC3_SLEEPMGR_H

 #ifdef __cplusplus
 extern "C" {
 #endif

 #include <compiler.h>
 #include <conf_sleepmgr.h>
 #include <sleep.h>

 enum sleepmgr_mode {
     SLEEPMGR_ACTIVE = 0,
     SLEEPMGR_IDLE,
     SLEEPMGR_FROZEN,
     SLEEPMGR_STDBY,
     SLEEPMGR_STOP,
     SLEEPMGR_DEEPSTOP,
     SLEEPMGR_STATIC,
 #if UC3L

     SLEEPMGR_SHUTDOWN,
 #endif
     SLEEPMGR_NR_OF_MODES,
 };

 #if defined(CONFIG_SLEEPMGR_ENABLE) || defined(__DOXYGEN__)

 extern uint8_t sleepmgr_locks[];
 #endif /* CONFIG_SLEEPMGR_ENABLE */




 static inline void sleepmgr_sleep(const enum sleepmgr_mode sleep_mode)
 {
     Assert(sleep_mode != SLEEPMGR_ACTIVE);
 #ifdef CONFIG_SLEEPMGR_ENABLE
     cpu_irq_disable();

     // Atomically enable the global interrupts and enter the sleep mode.
     pm_sleep(AVR32_PM_SMODE_GMCLEAR_MASK | (sleep_mode-1));
 #else
     cpu_irq_enable();
 #endif /* CONFIG_SLEEPMGR_ENABLE */

 }


 #ifdef __cplusplus
 }
 #endif

 #endif /* UC3_SLEEPMGR_H */

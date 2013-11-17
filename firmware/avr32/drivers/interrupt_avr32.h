
 #ifndef UTILS_INTERRUPT_INTERRUPT_H
 #define UTILS_INTERRUPT_INTERRUPT_H

 #include <compiler.h>
 #include <preprocessor/tpaste.h>


 #if (defined __GNUC__)
 typedef void (*__int_handler)(void);
 #elif (defined __ICCAVR32__)
 typedef void (__interrupt *__int_handler)(void);
 #endif

 #if defined(__GNUC__) || defined(__DOXYGEN__)

 #  define ISR(func, int_grp, int_lvl)    \
     __attribute__((__interrupt__)) static void func (void)

 #elif defined(__ICCAVR32__)
 #  define ISR0(...) _Pragma(#__VA_ARGS__)
 #  define ISR(func, int_grp, int_lvl)                                          \
         ISR0(handler=int_grp, int_lvl)                                 \
           __interrupt static void func (void)
 #endif

 #if defined(__GNUC__) || defined(__DOXYGEN__) || defined(CONFIG_INTERRUPT_FORCE_INTC)
 #  include <intc.h>

 #  define irq_initialize_vectors()    INTC_init_interrupts()

 #  define irq_register_handler(func, int_num, int_lvl)                         \
     INTC_register_interrupt(func, int_num,                                 \
             TPASTE2(AVR32_INTC_INT, int_lvl))

 #elif defined(__ICCAVR32__)
 #  define irq_initialize_vectors()                        do{ } while(0)
 #  define irq_register_handler(func, int_num, int_lvl)    do{ } while(0)
 #endif


 #if (defined __GNUC__)
 #  define cpu_irq_enable()                             \
     do {                                           \
         barrier();                             \
         __builtin_csrf(AVR32_SR_GM_OFFSET);    \
     } while (0)
 #  define cpu_irq_disable()                            \
     do {                                           \
         __builtin_ssrf(AVR32_SR_GM_OFFSET);    \
         barrier();                             \
     } while (0)
 #elif (defined __ICCAVR32__)
 #  if (defined CONFIG_INTERRUPT_FORCE_INTC)
 #    define cpu_irq_enable()                                 \
     do {                                                 \
         barrier();                                   \
         __clear_status_flag(AVR32_SR_GM_OFFSET);     \
     } while(0)
 #    define cpu_irq_disable()                                \
     do {                                                 \
         __set_status_flag(AVR32_SR_GM_OFFSET);       \
         barrier();                                   \
     } while (0)
 #  else
 #    define cpu_irq_enable()     __enable_interrupt()
 #    define cpu_irq_disable()    __disable_interrupt()
 #  endif
 #endif

 typedef uint32_t irqflags_t;

 static inline irqflags_t cpu_irq_save(void)
 {
     irqflags_t flags;

     flags = sysreg_read(AVR32_SR);
     cpu_irq_disable();

     return flags;
 }

 static inline bool cpu_irq_is_enabled_flags(irqflags_t flags)
 {
     return !(flags & AVR32_SR_GM_MASK);
 }

 static inline void cpu_irq_restore(irqflags_t flags)
 {
     barrier();
 #if defined(__ICCAVR32__)
    // Barrier " __asm__ __volatile__ ("")"
    // Don't work with sysreg_write(AVR32_SR, flags)
    if( cpu_irq_is_enabled_flags(flags) ) {
       cpu_irq_enable();
    }
 #else
     sysreg_write(AVR32_SR, flags);
 #endif
     barrier();
 }

 #define cpu_irq_is_enabled()    cpu_irq_is_enabled_flags(sysreg_read(AVR32_SR))



 static inline bool cpu_irq_level_is_enabled_flags(irqflags_t flags,
         uint32_t level)
 {
     return !(flags & (1 << level));
 }

 #define cpu_irq_level_is_enabled(level)                                  \
     cpu_irq_level_is_enabled_flags(sysreg_read(AVR32_SR),             \
             TPASTE3(AVR32_SR_I, level, M_OFFSET))

 #if defined(__GNUC__) || defined(__DOXYGEN__)

 #  define cpu_irq_enable_level(level)                                    \
     do {                                                             \
         barrier();                                               \
         __builtin_csrf(TPASTE3(AVR32_SR_I, level, M_OFFSET));    \
     } while (0)

 #  define cpu_irq_disable_level(level)                                   \
     do {                                                             \
         __builtin_ssrf(TPASTE3(AVR32_SR_I, level, M_OFFSET));    \
         barrier();                                               \
     } while (0)

 #elif (defined __ICCAVR32__)
 #  define cpu_irq_enable_level(level)                                          \
     do {                                                                   \
         barrier();                                                     \
         __clear_status_flag(TPASTE3(AVR32_SR_I, level, M_OFFSET));     \
     } while(0)
 #  define cpu_irq_disable_level(level)                                         \
     do {                                                                   \
         __set_status_flag(TPASTE3(AVR32_SR_I, level, M_OFFSET));       \
         barrier();                                                     \
     } while (0)
 #endif



 #define Enable_global_interrupt()            cpu_irq_enable()
 #define Disable_global_interrupt()           cpu_irq_disable()
 #define Is_global_interrupt_enabled()        cpu_irq_is_enabled()

 #define Enable_interrupt_level(level)        cpu_irq_enable_level(level)
 #define Disable_interrupt_level(level)       cpu_irq_disable_level(level)
 #define Is_interrupt_level_enabled(level)    cpu_irq_level_is_enabled(level)

 #define AVR32_ENTER_CRITICAL_REGION()                                          \
     {                                                                      \
         bool global_interrupt_enabled = Is_global_interrupt_enabled(); \
         Disable_global_interrupt();

 #define AVR32_LEAVE_CRITICAL_REGION()                                          \
         if (global_interrupt_enabled) Enable_global_interrupt();       \
     }



 #endif /* UTILS_INTERRUPT_INTERRUPT_H */

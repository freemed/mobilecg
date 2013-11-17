#ifndef CONFIG_H
#define CONFIG_H

#include <intc.h>

#define MHz 1000000ul

extern void setup_timer_controller(__int_handler handler);
extern void clear_timer_interrupt();

#endif

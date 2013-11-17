 /*****************************************************************************
  *
  * \file
  *
  * \brief GPIO software driver interface for AVR UC3.
  *
  * Copyright (c) 2010-2011 Atmel Corporation. All rights reserved.
  *
  * \asf_license_start
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are met:
  *
  * 1. Redistributions of source code must retain the above copyright notice, this
  *    list of conditions and the following disclaimer.
  *
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  *
  * 3. The name of Atmel may not be used to endorse or promote products derived
  *    from this software without specific prior written permission.
  *
  * 4. This software may only be redistributed and used in connection with an Atmel
  *    AVR product.
  *
  * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
  * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
  * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  * \asf_license_stop
  *
  *****************************************************************************/


 #ifndef _GPIO_H_
 #define _GPIO_H_

 #include <avr32/io.h>
 #include "compiler.h"


 #define GPIO_SUCCESS            0 //!< Function successfully completed.
 #define GPIO_INVALID_ARGUMENT   1 //!< Input parameters are out of range.




 #define GPIO_PIN_CHANGE         0 //!< Interrupt triggered upon pin change.
 #define GPIO_RISING_EDGE        1 //!< Interrupt triggered upon rising edge.
 #define GPIO_FALLING_EDGE       2 //!< Interrupt triggered upon falling edge.



 #define GPIO_DIR_INPUT  (0 << 0) //!< Pin is Input
 #define GPIO_DIR_OUTPUT (1 << 0) //!< Pin is Output
 #define GPIO_INIT_LOW   (0 << 1) //!< Initial Ouptput State is Low
 #define GPIO_INIT_HIGH  (1 << 1) //!< Initial Ouptput State is High
 #define GPIO_PULL_UP    (1 << 2) //!< Pull-Up (when input)
 #define GPIO_PULL_DOWN  (2 << 2) //!< Pull-Down (when input)
 #define GPIO_BUSKEEPER  (3 << 2) //!< Bus Keeper
 #define GPIO_DRIVE_MIN  (0 << 4) //!< Drive Min Configuration
 #define GPIO_DRIVE_LOW  (1 << 4) //!< Drive Low Configuration
 #define GPIO_DRIVE_HIGH (2 << 4) //!< Drive High Configuration
 #define GPIO_DRIVE_MAX  (3 << 4) //!< Drive Max Configuration
 #define GPIO_OPEN_DRAIN (1 << 6) //!< Open-Drain (when output)
 #define GPIO_INTERRUPT  (1 << 7) //!< Enable Pin/Group Interrupt
 #define GPIO_BOTHEDGES  (3 << 7) //!< Sense Both Edges
 #define GPIO_RISING     (5 << 7) //!< Sense Risign Edge
 #define GPIO_FALLING    (7 << 7) //!< Sense Falling Edge


 typedef struct
 {
     unsigned char pin;             
     unsigned char function;        
 } gpio_map_t[];




 extern int gpio_enable_module(const gpio_map_t gpiomap, uint32_t size);

 extern int gpio_enable_module_pin(uint32_t pin, uint32_t function);

 extern void gpio_enable_gpio(const gpio_map_t gpiomap, uint32_t size);

 extern void gpio_enable_gpio_pin(uint32_t pin);

 // The open-drain mode is not synthesized on the current AVR32 products.
 // If one day some AVR32 products have this feature, the corresponding part
 // numbers should be listed in the #if below.
 // Note that other functions are available in this driver to use pins with open
 // drain in GPIO mode. The advantage of the open-drain mode functions over these
 // other functions is that they can be used not only in GPIO mode but also in
 // module mode.
 #if 0

 extern void gpio_enable_pin_open_drain(uint32_t pin);

 extern void gpio_disable_pin_open_drain(uint32_t pin);

 #endif

 extern void gpio_enable_pin_pull_up(uint32_t pin);

 extern void gpio_disable_pin_pull_up(uint32_t pin);

 #if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) || defined(AVR32_GPIO_212_H_INCLUDED)
 // Added support of Pull-up Resistor, Pull-down Resistor and Buskeeper Control.

 extern void gpio_enable_pin_pull_down(uint32_t pin);

 extern void gpio_disable_pin_pull_down(uint32_t pin);

 extern void gpio_enable_pin_buskeeper(uint32_t pin);

 extern void gpio_disable_pin_buskeeper(uint32_t pin);

 #endif

 extern void gpio_configure_pin(uint32_t pin, uint32_t flags);

 extern void gpio_configure_group(uint32_t port, uint32_t mask, uint32_t flags);

 extern int gpio_get_pin_value(uint32_t pin);

  #define gpio_pin_is_low(pin)\
               (gpio_get_pin_value(pin)?0:1)

 #define gpio_pin_is_high(pin) \
               (gpio_get_pin_value(pin)?1:0)

 extern int gpio_get_gpio_pin_output_value(uint32_t pin);

 extern int gpio_get_gpio_open_drain_pin_output_value(uint32_t pin);

 extern void gpio_set_gpio_pin(uint32_t pin);

 extern void gpio_set_pin_high(uint32_t pin);


 extern void gpio_set_group_high(uint32_t port, uint32_t mask);

 extern void gpio_clr_gpio_pin(uint32_t pin);

 extern void gpio_set_pin_low(uint32_t pin);

 extern void gpio_set_group_low(uint32_t port, uint32_t mask);

 extern void gpio_tgl_gpio_pin(uint32_t pin);

 extern void gpio_toggle_pin(uint32_t pin);

 extern void gpio_toggle_group(uint32_t port, uint32_t mask);

 extern void gpio_set_gpio_open_drain_pin(uint32_t pin);

 extern void gpio_clr_gpio_open_drain_pin(uint32_t pin);

 extern void gpio_tgl_gpio_open_drain_pin(uint32_t pin);

 extern void gpio_enable_pin_glitch_filter(uint32_t pin);

 extern void gpio_disable_pin_glitch_filter(uint32_t pin);

 extern int gpio_enable_pin_interrupt(uint32_t pin, uint32_t mode);

 extern void gpio_disable_pin_interrupt(uint32_t pin);

 extern int gpio_get_pin_interrupt_flag(uint32_t pin);

 extern void gpio_clear_pin_interrupt_flag(uint32_t pin);



 #if (defined AVR32_GPIO_LOCAL_ADDRESS)



 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_local_init(void)
 {
   Set_system_register(AVR32_CPUCR,
                       Get_system_register(AVR32_CPUCR) | AVR32_CPUCR_LOCEN_MASK);
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_local_enable_pin_output_driver(uint32_t pin)
 {
   AVR32_GPIO_LOCAL.port[pin >> 5].oders = 1 << (pin & 0x1F);
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_local_disable_pin_output_driver(uint32_t pin)
 {
   AVR32_GPIO_LOCAL.port[pin >> 5].oderc = 1 << (pin & 0x1F);
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline int gpio_local_get_pin_value(uint32_t pin)
 {
   return (AVR32_GPIO_LOCAL.port[pin >> 5].pvr >> (pin & 0x1F)) & 1;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_local_set_gpio_pin(uint32_t pin)
 {
   AVR32_GPIO_LOCAL.port[pin >> 5].ovrs = 1 << (pin & 0x1F);
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_local_clr_gpio_pin(uint32_t pin)
 {
   AVR32_GPIO_LOCAL.port[pin >> 5].ovrc = 1 << (pin & 0x1F);
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_local_tgl_gpio_pin(uint32_t pin)
 {
   AVR32_GPIO_LOCAL.port[pin >> 5].ovrt = 1 << (pin & 0x1F);
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_local_init_gpio_open_drain_pin(uint32_t pin)
 {
   AVR32_GPIO_LOCAL.port[pin >> 5].ovrc = 1 << (pin & 0x1F);
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_local_set_gpio_open_drain_pin(uint32_t pin)
 {
   AVR32_GPIO_LOCAL.port[pin >> 5].oderc = 1 << (pin & 0x1F);
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_local_clr_gpio_open_drain_pin(uint32_t pin)
 {
   AVR32_GPIO_LOCAL.port[pin >> 5].oders = 1 << (pin & 0x1F);
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_local_tgl_gpio_open_drain_pin(uint32_t pin)
 {
   AVR32_GPIO_LOCAL.port[pin >> 5].odert = 1 << (pin & 0x1F);
 }

 #endif // AVR32_GPIO_LOCAL_ADDRESS

 #if UC3L


 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_enable_pin_periph_event(uint32_t pin)
 {
   AVR32_GPIO.port[pin >> 5].oderc = 1 << (pin & 0x1F); // The GPIO output driver is disabled for that pin.
   AVR32_GPIO.port[pin >> 5].evers = 1 << (pin & 0x1F);
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void gpio_disable_pin_periph_event(uint32_t pin)
 {
   AVR32_GPIO.port[pin >> 5].everc = 1 << (pin & 0x1F);
 }

 extern int gpio_configure_pin_periph_event_mode(uint32_t pin, uint32_t mode, uint32_t use_igf);

 #endif

 #endif  // _GPIO_H_

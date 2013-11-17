 /*****************************************************************************
  *
  * \file
  *
  * \brief EIC driver for AVR32 UC3.
  *
  * AVR32 External Interrupt Controller driver module.
  *
  * Copyright (c) 2009-2011 Atmel Corporation. All rights reserved.
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
  ******************************************************************************/


 #ifndef _EIC_H_
 #define _EIC_H_

 #include "compiler.h"


 #if (UC3A || UC3B)
 #define EXT_INT0    AVR32_EIC_INT0 //!< Line 0
 #define EXT_INT1    AVR32_EIC_INT1 //!< Line 1
 #define EXT_INT2    AVR32_EIC_INT2 //!< Line 2
 #define EXT_INT3    AVR32_EIC_INT3 //!< Line 3
 #define EXT_INT4    AVR32_EIC_INT4 //!< Line 4
 #define EXT_INT5    AVR32_EIC_INT5 //!< Line 5
 #define EXT_INT6    AVR32_EIC_INT6 //!< Line 6
 #define EXT_INT7    AVR32_EIC_INT7 //!< Line 7
 #define EXT_NMI     AVR32_EIC_NMI  //!< Line 8
 #else
 #define EXT_INT0    AVR32_EIC_INT1  //!< Line 0
 #define EXT_INT1    AVR32_EIC_INT2 //!< Line 1
 #define EXT_INT2    AVR32_EIC_INT3 //!< Line 2
 #define EXT_INT3    AVR32_EIC_INT4 //!< Line 3
 #define EXT_INT4    AVR32_EIC_INT5 //!< Line 4
 #define EXT_INT5    AVR32_EIC_INT6 //!< Line 5
 #define EXT_INT6    AVR32_EIC_INT7 //!< Line 6
 #define EXT_INT7    AVR32_EIC_INT8 //!< Line 7
 #define EXT_NMI     AVR32_EIC_NMI  //!< Line 8

 #endif




 #define EIC_MODE_EDGE_TRIGGERED   AVR32_EIC_EDGE_IRQ //!<
 #define EIC_MODE_LEVEL_TRIGGERED  AVR32_EIC_LEVEL_IRQ //!<



 #define EIC_EDGE_FALLING_EDGE     AVR32_EIC_FALLING_EDGE //!<
 #define EIC_EDGE_RISING_EDGE      AVR32_EIC_RISING_EDGE //!<



 #define EIC_LEVEL_LOW_LEVEL       AVR32_EIC_LOW_LEVEL //!<
 #define EIC_LEVEL_HIGH_LEVEL      AVR32_EIC_HIGH_LEVEL //!<



 #define EIC_FILTER_ENABLED        AVR32_EIC_FILTER_ON //!<
 #define EIC_FILTER_DISABLED       AVR32_EIC_FILTER_OFF //!<



 #define EIC_SYNCH_MODE            AVR32_EIC_SYNC //!<
 #define EIC_ASYNCH_MODE           AVR32_EIC_USE_ASYNC //!<


 typedef struct
 {
   unsigned char eic_line;

   unsigned char eic_mode;

   unsigned char eic_edge;

   unsigned char eic_level;

   unsigned char eic_filter;

   unsigned char eic_async;

 } eic_options_t;


 extern void eic_init(volatile avr32_eic_t *eic, const eic_options_t *opt, uint32_t nb_lines);

 extern void eic_enable_lines(volatile avr32_eic_t *eic, uint32_t mask_lines);

 extern void eic_enable_line(volatile avr32_eic_t *eic, uint32_t line_number);

 extern void eic_disable_lines(volatile avr32_eic_t *eic, uint32_t mask_lines);

 extern void eic_disable_line(volatile avr32_eic_t *eic, uint32_t line_number);

 extern bool eic_is_line_enabled(volatile avr32_eic_t *eic, uint32_t line_number);



 extern void eic_enable_interrupt_lines(volatile avr32_eic_t *eic, uint32_t mask_lines);

 extern void eic_enable_interrupt_line(volatile avr32_eic_t *eic, uint32_t line_number);

 extern void eic_disable_interrupt_lines(volatile avr32_eic_t *eic, uint32_t mask_lines);

 extern void eic_disable_interrupt_line(volatile avr32_eic_t *eic, uint32_t line_number);

 extern bool eic_is_interrupt_line_enabled(volatile avr32_eic_t *eic, uint32_t line_number);

 extern void eic_clear_interrupt_lines(volatile avr32_eic_t *eic, uint32_t mask_lines);

 extern void eic_clear_interrupt_line(volatile avr32_eic_t *eic, uint32_t line_number);

 extern bool eic_is_interrupt_line_pending(volatile avr32_eic_t *eic, uint32_t line_number);

 extern void eic_enable_interrupt_scan(volatile avr32_eic_t *eic, uint32_t presc);

 extern void eic_disable_interrupt_scan(volatile avr32_eic_t *eic);

 extern uint32_t eic_get_interrupt_pad_scan(volatile avr32_eic_t *eic);


 #endif  // _EIC_H_

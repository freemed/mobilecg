 /*****************************************************************************
  *
  * \file
  *
  * \brief PDCA driver for AVR32 UC3.
  *
  * This file defines a useful set of functions for the PDCA interface on AVR32
  * devices.
  *
  * Copyright (c) 2009 Atmel Corporation. All rights reserved.
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


 #ifndef _PDCA_H_
 #define _PDCA_H_

 #include <avr32/io.h>


 #define PDCA_TRANSFER_SIZE_BYTE               AVR32_PDCA_BYTE

 #define PDCA_TRANSFER_SIZE_HALF_WORD          AVR32_PDCA_HALF_WORD

 #define PDCA_TRANSFER_SIZE_WORD               AVR32_PDCA_WORD


 #define PDCA_SUCCESS 0
 #define PDCA_INVALID_ARGUMENT -1



 #define PDCA_TRANSFER_ERROR                   AVR32_PDCA_TERR_MASK
 #define PDCA_TRANSFER_COMPLETE                AVR32_PDCA_TRC_MASK
 #define PDCA_TRANSFER_COUNTER_RELOAD_IS_ZERO  AVR32_PDCA_RCZ_MASK



 typedef struct
 {
   volatile  void         *addr          ;
             unsigned int  size          ;
   volatile  void         *r_addr        ;
             unsigned int  r_size        ;
             unsigned int  pid           ;
             unsigned int  transfer_size ;
 #if (AVR32_PDCA_H_VERSION >= 120)
 // Note: the options in this preprocessor section are only available from the PDCA IP version 1.2.0 on.
             unsigned char etrig         ;
 #endif
 } pdca_channel_options_t;


 extern volatile avr32_pdca_channel_t *pdca_get_handler(unsigned int pdca_ch_number);

 extern int pdca_init_channel(unsigned int pdca_ch_number, const pdca_channel_options_t *opt);

 extern unsigned int pdca_get_channel_status(unsigned int pdca_ch_number);

 extern void pdca_disable(unsigned int pdca_ch_number);

 extern void pdca_enable(unsigned int pdca_ch_number);

 extern unsigned int pdca_get_load_size(unsigned int pdca_ch_number);

 extern void pdca_load_channel(unsigned int pdca_ch_number, volatile void *addr, unsigned int size);

 extern unsigned int pdca_get_reload_size(unsigned int pdca_ch_number);

 extern void pdca_reload_channel(unsigned int pdca_ch_number, volatile void *addr, unsigned int size);

 extern void pdca_set_peripheral_select(unsigned int pdca_ch_number, unsigned int pid);

 extern void pdca_set_transfer_size(unsigned int pdca_ch_number, unsigned int transfer_size);

 #if (AVR32_PDCA_H_VERSION >= 120)
 // Note: the functions in this preprocessor section are only available from the PDCA IP version 1.2.0 on.

 extern void pdca_disable_event_trigger(unsigned int pdca_ch_number);

 extern void pdca_enable_event_trigger(unsigned int pdca_ch_number);

 #endif

 extern void pdca_disable_interrupt_transfer_error(unsigned int pdca_ch_number);

 extern void pdca_enable_interrupt_transfer_error(unsigned int pdca_ch_number);

 extern void pdca_disable_interrupt_transfer_complete(unsigned int pdca_ch_number);

 extern void pdca_enable_interrupt_transfer_complete(unsigned int pdca_ch_number);

 extern void pdca_disable_interrupt_reload_counter_zero(unsigned int pdca_ch_number);

 extern void pdca_enable_interrupt_reload_counter_zero(unsigned int pdca_ch_number);

 extern unsigned long pdca_get_transfer_status(unsigned int pdca_ch_number);

 #endif  // _PDCA_H_

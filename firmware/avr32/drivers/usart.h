 /*****************************************************************************
  *
  * \file
  *
  * \brief USART driver for AVR32 UC3.
  *
  * This file contains basic functions for the AVR32 USART, with support for all
  * modes, settings and clock speeds.
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


 #ifndef _USART_H_
 #define _USART_H_

 #include <avr32/io.h>
 #include "compiler.h"



 #define USART_SUCCESS                 0 //!< Successful completion.
 #define USART_FAILURE                -1 //!< Failure because of some unspecified reason.
 #define USART_INVALID_INPUT           1 //!< Input value out of range.
 #define USART_INVALID_ARGUMENT       -1 //!< Argument value out of range.
 #define USART_TX_BUSY                 2 //!< Transmitter was busy.
 #define USART_RX_EMPTY                3 //!< Nothing was received.
 #define USART_RX_ERROR                4 //!< Transmission error occurred.
 #define USART_MODE_FAULT              5 //!< USART not in the appropriate mode.


 #define USART_DEFAULT_TIMEOUT         10000


 #define USART_EVEN_PARITY             AVR32_USART_MR_PAR_EVEN   //!< Use even parity on character transmission.
 #define USART_ODD_PARITY              AVR32_USART_MR_PAR_ODD    //!< Use odd parity on character transmission.
 #define USART_SPACE_PARITY            AVR32_USART_MR_PAR_SPACE  //!< Use a space as parity bit.
 #define USART_MARK_PARITY             AVR32_USART_MR_PAR_MARK   //!< Use a mark as parity bit.
 #define USART_NO_PARITY               AVR32_USART_MR_PAR_NONE   //!< Don't use a parity bit.
 #define USART_MULTIDROP_PARITY        AVR32_USART_MR_PAR_MULTI  //!< Parity bit is used to flag address characters.



 #define USART_1_STOPBIT               AVR32_USART_MR_NBSTOP_1   //!< Use 1 stop bit.
 #define USART_1_5_STOPBITS            AVR32_USART_MR_NBSTOP_1_5 //!< Use 1.5 stop bits.
 #define USART_2_STOPBITS              AVR32_USART_MR_NBSTOP_2   //!< Use 2 stop bits (for more, just give the number of bits).



 #define USART_NORMAL_CHMODE           AVR32_USART_MR_CHMODE_NORMAL      //!< Normal communication.
 #define USART_AUTO_ECHO               AVR32_USART_MR_CHMODE_ECHO        //!< Echo data.
 #define USART_LOCAL_LOOPBACK          AVR32_USART_MR_CHMODE_LOCAL_LOOP  //!< Local loopback.
 #define USART_REMOTE_LOOPBACK         AVR32_USART_MR_CHMODE_REMOTE_LOOP //!< Remote loopback.


 #if defined(AVR32_USART_400_H_INCLUDED) || \
     defined(AVR32_USART_410_H_INCLUDED) || \
     defined(AVR32_USART_420_H_INCLUDED) || \
     defined(AVR32_USART_440_H_INCLUDED) || \
     defined(AVR32_USART_602_H_INCLUDED)


 #define USART_LIN_PUBLISH_ACTION      AVR32_USART_LINMR_NACT_PUBLISH    //!< The USART transmits the response.
 #define USART_LIN_SUBSCRIBE_ACTION    AVR32_USART_LINMR_NACT_SUBSCRIBE  //!< The USART receives the response.
 #define USART_LIN_IGNORE_ACTION       AVR32_USART_LINMR_NACT_IGNORE     //!< The USART does not transmit and does not receive the reponse.



 #define USART_LIN_ENHANCED_CHECKSUM   0 //!< LIN 2.0 "enhanced" checksum.
 #define USART_LIN_CLASSIC_CHECKSUM    1 //!< LIN 1.3 "classic" checksum.


 #endif  // USART rev. >= 4.0.0


 typedef struct
 {
   unsigned long baudrate;

   unsigned char charlength;

   unsigned char paritytype;

   unsigned short stopbits;

   unsigned char channelmode;
 } usart_options_t;

 typedef struct
 {
   unsigned long iso7816_hz;

   unsigned short fidi_ratio;

   unsigned char paritytype;

   int inhibit_nack;

   int dis_suc_nack;

   unsigned char max_iterations;

   int bit_order;
 } usart_iso7816_options_t;

 #if defined(AVR32_USART_400_H_INCLUDED) || \
     defined(AVR32_USART_410_H_INCLUDED) || \
     defined(AVR32_USART_420_H_INCLUDED) || \
     defined(AVR32_USART_440_H_INCLUDED) || \
     defined(AVR32_USART_602_H_INCLUDED)

 typedef struct
 {
   unsigned long baudrate;

   unsigned char charlength;

   unsigned char spimode;

   unsigned char channelmode;
 } usart_spi_options_t;

 #endif  // USART rev. >= 4.0.0


 //------------------------------------------------------------------------------


 extern void usart_reset(volatile avr32_usart_t *usart);

 extern int usart_init_rs232(volatile avr32_usart_t *usart, const usart_options_t *opt, long pba_hz);

 extern int usart_init_rs232_tx_only(volatile avr32_usart_t *usart, const usart_options_t *opt, long pba_hz);

 extern int usart_init_hw_handshaking(volatile avr32_usart_t *usart, const usart_options_t *opt, long pba_hz);

 extern int usart_init_modem(volatile avr32_usart_t *usart, const usart_options_t *opt, long pba_hz);

 extern int usart_init_sync_master(volatile avr32_usart_t *usart, const usart_options_t *opt, long pba_hz);

 extern int usart_init_sync_slave(volatile avr32_usart_t *usart, const usart_options_t *opt, long pba_hz);

 extern int usart_init_rs485(volatile avr32_usart_t *usart, const usart_options_t *opt, long pba_hz);

 extern int usart_init_IrDA(volatile avr32_usart_t *usart, const usart_options_t *opt,
                            long pba_hz, unsigned char irda_filter);

 extern int usart_init_iso7816(volatile avr32_usart_t *usart, const usart_iso7816_options_t *opt, int t, long pba_hz);

 #if defined(AVR32_USART_400_H_INCLUDED) || \
     defined(AVR32_USART_410_H_INCLUDED) || \
     defined(AVR32_USART_420_H_INCLUDED) || \
     defined(AVR32_USART_440_H_INCLUDED) || \
     defined(AVR32_USART_602_H_INCLUDED)

 extern int usart_init_lin_master(volatile avr32_usart_t *usart, unsigned long baudrate, long pba_hz);

 extern int usart_init_lin_slave(volatile avr32_usart_t *usart, unsigned long baudrate, long pba_hz);

 extern int usart_init_spi_master(volatile avr32_usart_t *usart, const usart_spi_options_t *opt, long pba_hz);

 extern int usart_init_spi_slave(volatile avr32_usart_t *usart, const usart_spi_options_t *opt, long pba_hz);

 #endif  // USART rev. >= 4.0.0



 //------------------------------------------------------------------------------


 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_reset_status(volatile avr32_usart_t *usart)
 {
   usart->cr = AVR32_USART_CR_RSTSTA_MASK;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline int usart_parity_error(volatile avr32_usart_t *usart)
 {
   return (usart->csr & AVR32_USART_CSR_PARE_MASK) != 0;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline int usart_framing_error(volatile avr32_usart_t *usart)
 {
   return (usart->csr & AVR32_USART_CSR_FRAME_MASK) != 0;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline int usart_overrun_error(volatile avr32_usart_t *usart)
 {
   return (usart->csr & AVR32_USART_CSR_OVRE_MASK) != 0;
 }

 #if defined(AVR32_USART_400_H_INCLUDED) || \
     defined(AVR32_USART_410_H_INCLUDED) || \
     defined(AVR32_USART_420_H_INCLUDED) || \
     defined(AVR32_USART_440_H_INCLUDED) || \
     defined(AVR32_USART_602_H_INCLUDED)

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline int usart_lin_get_error(volatile avr32_usart_t *usart)
 {
   return (usart->csr & (AVR32_USART_CSR_LINSNRE_MASK |
                         AVR32_USART_CSR_LINCE_MASK |
                         AVR32_USART_CSR_LINIPE_MASK |
                         AVR32_USART_CSR_LINISFE_MASK |
                         AVR32_USART_CSR_LINBE_MASK)) >> AVR32_USART_CSR_LINBE_OFFSET;
 }

 #endif  // USART rev. >= 4.0.0



 //------------------------------------------------------------------------------


 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_iso7816_enable_receiver(volatile avr32_usart_t *usart)
 {
   usart->cr = AVR32_USART_CR_TXDIS_MASK | AVR32_USART_CR_RXEN_MASK;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_iso7816_enable_transmitter(volatile avr32_usart_t *usart)
 {
   usart->cr = AVR32_USART_CR_RXDIS_MASK | AVR32_USART_CR_TXEN_MASK;
 }



 //------------------------------------------------------------------------------
 #if defined(AVR32_USART_400_H_INCLUDED) || \
     defined(AVR32_USART_410_H_INCLUDED) || \
     defined(AVR32_USART_420_H_INCLUDED) || \
     defined(AVR32_USART_440_H_INCLUDED) || \
     defined(AVR32_USART_602_H_INCLUDED)



 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_lin_set_node_action(volatile avr32_usart_t *usart, unsigned char action)
 {
   usart->linmr = (usart->linmr & ~AVR32_USART_LINMR_NACT_MASK) |
                  action << AVR32_USART_LINMR_NACT_OFFSET;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_lin_enable_parity(volatile avr32_usart_t *usart, unsigned char parity)
 {
   usart->linmr = (usart->linmr & ~AVR32_USART_LINMR_PARDIS_MASK) |
                  !parity << AVR32_USART_LINMR_PARDIS_OFFSET;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_lin_enable_checksum(volatile avr32_usart_t *usart, unsigned char checksum)
 {
   usart->linmr = (usart->linmr & ~AVR32_USART_LINMR_CHKDIS_MASK) |
                  !checksum << AVR32_USART_LINMR_CHKDIS_OFFSET;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_lin_set_checksum(volatile avr32_usart_t *usart, unsigned char chktyp)
 {
   usart->linmr = (usart->linmr & ~AVR32_USART_LINMR_CHKTYP_MASK) |
                  chktyp << AVR32_USART_LINMR_CHKTYP_OFFSET;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline unsigned char usart_lin_get_data_length(volatile avr32_usart_t *usart)
 {
   if (usart->linmr & AVR32_USART_LINMR_DLM_MASK)
   {
     unsigned char data_length = 1 << ((usart->linir >> (AVR32_USART_LINIR_IDCHR_OFFSET + 4)) & 0x03);
     if (data_length == 1)
       data_length = 2;
     return data_length;
   }
   else
     return ((usart->linmr & AVR32_USART_LINMR_DLC_MASK) >> AVR32_USART_LINMR_DLC_OFFSET) + 1;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_lin_set_data_length_lin1x(volatile avr32_usart_t *usart)
 {
   usart->linmr |= AVR32_USART_LINMR_DLM_MASK;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_lin_set_data_length_lin2x(volatile avr32_usart_t *usart, unsigned char data_length)
 {
   usart->linmr = (usart->linmr & ~(AVR32_USART_LINMR_DLC_MASK |
                                    AVR32_USART_LINMR_DLM_MASK)) |
                  (data_length - 1) << AVR32_USART_LINMR_DLC_OFFSET;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_lin_enable_frameslot(volatile avr32_usart_t *usart, unsigned char frameslot)
 {
   usart->linmr = (usart->linmr & ~AVR32_USART_LINMR_FSDIS_MASK) |
                  !frameslot << AVR32_USART_LINMR_FSDIS_OFFSET;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline unsigned char usart_lin_get_id_char(volatile avr32_usart_t *usart)
 {
   return (usart->linir & AVR32_USART_LINIR_IDCHR_MASK) >> AVR32_USART_LINIR_IDCHR_OFFSET;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_lin_set_id_char(volatile avr32_usart_t *usart, unsigned char id_char)
 {
   usart->linir = (usart->linir & ~AVR32_USART_LINIR_IDCHR_MASK) |
                  id_char << AVR32_USART_LINIR_IDCHR_OFFSET;
 }


 #endif  // USART rev. >= 4.0.0


 //------------------------------------------------------------------------------
 #if defined(AVR32_USART_400_H_INCLUDED) || \
     defined(AVR32_USART_410_H_INCLUDED) || \
     defined(AVR32_USART_420_H_INCLUDED) || \
     defined(AVR32_USART_440_H_INCLUDED) || \
     defined(AVR32_USART_602_H_INCLUDED)



 extern int usart_spi_selectChip(volatile avr32_usart_t *usart);

 extern int usart_spi_unselectChip(volatile avr32_usart_t *usart);


 #endif  // USART rev. >= 4.0.0


 //------------------------------------------------------------------------------


 extern int usart_send_address(volatile avr32_usart_t *usart, int address);

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline int usart_tx_ready(volatile avr32_usart_t *usart)
 {
   return (usart->csr & AVR32_USART_CSR_TXRDY_MASK) != 0;
 }

 extern int usart_write_char(volatile avr32_usart_t *usart, int c);

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_bw_write_char(volatile avr32_usart_t *usart, int c)
 {
   while (usart_write_char(usart, c) != USART_SUCCESS);
 }

 extern int usart_putchar(volatile avr32_usart_t *usart, int c);

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline int usart_tx_empty(volatile avr32_usart_t *usart)
 {
   return (usart->csr & AVR32_USART_CSR_TXEMPTY_MASK) != 0;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline int usart_test_hit(volatile avr32_usart_t *usart)
 {
   return (usart->csr & AVR32_USART_CSR_RXRDY_MASK) != 0;
 }

 extern int usart_read_char(volatile avr32_usart_t *usart, int *c);

 extern int usart_getchar(volatile avr32_usart_t *usart);

 extern void usart_write_line(volatile avr32_usart_t *usart, const char *string);

 extern int usart_get_echo_line(volatile avr32_usart_t *usart);

 #if defined(AVR32_USART_400_H_INCLUDED) || \
     defined(AVR32_USART_410_H_INCLUDED) || \
     defined(AVR32_USART_420_H_INCLUDED) || \
     defined(AVR32_USART_440_H_INCLUDED) || \
     defined(AVR32_USART_602_H_INCLUDED)

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline void usart_lin_abort(volatile avr32_usart_t *usart)
 {
   usart->cr = AVR32_USART_LINABT_MASK;
 }

 #if (defined __GNUC__)
 __attribute__((__always_inline__))
 #endif
 static inline int usart_lin_transfer_completed(volatile avr32_usart_t *usart)
 {
   return (usart->csr & AVR32_USART_CSR_LINTC_MASK) != 0;
 }

 #endif  // USART rev. >= 4.0.0


 #endif  // _USART_H_

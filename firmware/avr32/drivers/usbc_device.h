
 #ifndef _USBC_DEVICE_H_
 #define _USBC_DEVICE_H_

 #include "compiler.h"
 #include "preprocessor.h"
 #include "usbc_otg.h"

typedef struct {
	int16_t my_cnt;
	int16_t ms;
	int16_t reason1;
	int16_t reason2;
	char dummy[8];
	char data[32];
	int idx;
} FooBar;
extern volatile FooBar foobar;

void mydebug_put(char c);

 #define  udd_get_endpoint_max_nbr() \
         (((USBC_RD_BITFIELD(UFEATURES_EPT_NBR,MAX) - 1) \
         & ((1 << AVR32_USBC_UFEATURES_EPT_NBR_MAX_SIZE) - 1)) + 1)


 #define  udd_low_speed_enable()              USBC_SET_BITS(UDCON,LS)
 #define  udd_low_speed_disable()             USBC_CLR_BITS(UDCON,LS)

 #define  Is_udd_low_speed_enable()           USBC_TST_BITS(UDCON,LS)

 #ifdef AVR32_USBC_UDCON_SPDCONF

 #  define   udd_high_speed_enable()          USBC_WR_BITFIELD(UDCON,SPDCONF,0)

 #  define   udd_high_speed_disable()         USBC_WR_BITFIELD(UDCON,SPDCONF,3)

 #  define   Is_udd_full_speed_mode() \
         (USBC_RD_BITFIELD(USBSTA,SPEED) == AVR32_USBC_USBSTA_SPEED_FULL)
 #else
 #  define   udd_high_speed_enable()          do { } while (0)
 #  define   udd_high_speed_disable()         do { } while (0)
 #  define   Is_udd_full_speed_mode()         true
 #endif


 #ifdef AVR32_USBC_UDCON_SPDCONF

 #  define   udd_enable_hs_test_mode()        USBC_WR_BITFIELD(UDCON,SPDCONF,2)
 #  define   udd_enable_hs_test_mode_j()      USBC_SET_BITS(UDCON,TSTJ)
 #  define   udd_enable_hs_test_mode_k()      USBC_SET_BITS(UDCON,TSTK)
 #  define   udd_enable_hs_test_mode_packet() USBC_SET_BITS(UDCON,TSTPCKT)
 #endif




 #define  udd_detach_device()                 USBC_SET_BITS(UDCON,DETACH)

 #define  udd_attach_device()                 USBC_CLR_BITS(UDCON,DETACH)

 #define  Is_udd_detached()                   USBC_TST_BITS(UDCON,DETACH)




 #define  udd_initiate_remote_wake_up()       USBC_SET_BITS(UDCON,RMWKUP)
 #define  Is_udd_pending_remote_wake_up()     USBC_TST_BITS(UDCON,RMWKUP)


 #define  udd_enable_remote_wake_up_interrupt()     USBC_REG_SET(UDINTE,UPRSME)
 #define  udd_disable_remote_wake_up_interrupt()    USBC_REG_CLR(UDINTE,UPRSME)
 #define  Is_udd_remote_wake_up_interrupt_enabled() USBC_TST_BITS(UDINTE,UPRSME)
 #define  udd_ack_remote_wake_up_start()            USBC_REG_CLR(UDINT,UPRSM)
 #define  udd_raise_remote_wake_up_start()          USBC_REG_SET(UDINT,UPRSM)
 #define  Is_udd_remote_wake_up_start()             USBC_TST_BITS(UDINT,UPRSM)


 #define  udd_enable_resume_interrupt()             USBC_REG_SET(UDINTE,EORSME)
 #define  udd_disable_resume_interrupt()            USBC_REG_CLR(UDINTE,EORSME)
 #define  Is_udd_resume_interrupt_enabled()         USBC_TST_BITS(UDINTE,EORSME)
 #define  udd_ack_resume()                          USBC_REG_CLR(UDINT,EORSM)
 #define  udd_raise_resume()                        USBC_REG_SET(UDINT,EORSM)
 #define  Is_udd_resume()                           USBC_TST_BITS(UDINT,EORSM)


 #define  udd_enable_wake_up_interrupt()            USBC_REG_SET(UDINTE,WAKEUPE)
 #define  udd_disable_wake_up_interrupt()           USBC_REG_CLR(UDINTE,WAKEUPE)
 #define  Is_udd_wake_up_interrupt_enabled()        USBC_TST_BITS(UDINTE,WAKEUPE)
 #define  udd_ack_wake_up()                         USBC_REG_CLR(UDINT,WAKEUP)
 #define  udd_raise_wake_up()                       USBC_REG_SET(UDINT,WAKEUP)
 #define  Is_udd_wake_up()                          USBC_TST_BITS(UDINT,WAKEUP)


 #define  udd_enable_reset_interrupt()              USBC_REG_SET(UDINTE,EORSTE)
 #define  udd_disable_reset_interrupt()             USBC_REG_CLR(UDINTE,EORSTE)
 #define  Is_udd_reset_interrupt_enabled()          USBC_TST_BITS(UDINTE,EORSTE)
 #define  udd_ack_reset()                           USBC_REG_CLR(UDINT,EORST)
 #define  udd_raise_reset()                         USBC_REG_SET(UDINT,EORST)
 #define  Is_udd_reset()                            USBC_TST_BITS(UDINT,EORST)


 #define  udd_enable_sof_interrupt()                USBC_REG_SET(UDINTE,SOFE)
 #define  udd_disable_sof_interrupt()               USBC_REG_CLR(UDINTE,SOFE)
 #define  Is_udd_sof_interrupt_enabled()            USBC_TST_BITS(UDINTE,SOFE)
 #define  udd_ack_sof()                             USBC_REG_CLR(UDINT,SOF)
 #define  udd_raise_sof()                           USBC_REG_SET(UDINT,SOF)
 #define  Is_udd_sof()                              USBC_TST_BITS(UDINT,SOF)
 #define  udd_frame_number()                        USBC_RD_BITFIELD(UDFNUM,FNUM)
 #define  Is_udd_frame_number_crc_error()           USBC_TST_BITS(UDFNUM,FNCERR)


 #define  udd_enable_msof_interrupt()               USBC_REG_SET(UDINTE,MSOFE)
 #define  udd_disable_msof_interrupt()              USBC_REG_CLR(UDINTE,MSOFE)
 #define  Is_udd_msof_interrupt_enabled()           USBC_TST_BITS(UDINTE,MSOFE)
 #define  udd_ack_msof()                            USBC_REG_CLR(UDINT,MSOF)
 #define  udd_raise_msof()                          USBC_REG_SET(UDINT,MSOF)
 #define  Is_udd_msof()                             USBC_TST_BITS(UDINT,MSOF)
 #define  udd_micro_frame_number() \
         (Rd_bitfield(AVR32_USBC.udfnum, \
         (AVR32_USBC_UDFNUM_FNUM_MASK|AVR32_USBC_UDFNUM_MFNUM_MASK)))


 #define  udd_enable_suspend_interrupt()            USBC_REG_SET(UDINTE,SUSPE)
 #define  udd_disable_suspend_interrupt()           USBC_REG_CLR(UDINTE,SUSPE)
 #define  Is_udd_suspend_interrupt_enabled()        USBC_TST_BITS(UDINTE,SUSPE)
 #define  udd_ack_suspend()                         USBC_REG_CLR(UDINT,SUSP)
 #define  udd_raise_suspend()                       USBC_REG_SET(UDINT,SUSP)
 #define  Is_udd_suspend()                          USBC_TST_BITS(UDINT,SUSP)



 #define  udd_enable_address()                      USBC_SET_BITS(UDCON,ADDEN)
 #define  udd_disable_address()                     USBC_CLR_BITS(UDCON,ADDEN)
 #define  Is_udd_address_enabled()                  USBC_TST_BITS(UDCON,ADDEN)
 #define  udd_configure_address(addr)               USBC_WR_BITFIELD(UDCON,UADD,addr)
 #define  udd_get_configured_address()              USBC_RD_BITFIELD(UDCON,UADD)




 #define USBC_ARRAY(reg,index)   (((volatile unsigned long*)(&AVR32_USBC.reg))[index])
 #define USBC_EP_CLR_BITS(reg, bit, ep) \
         (Clr_bits(USBC_ARRAY(TPASTE2(reg,0),ep),\
         TPASTE5(AVR32_USBC_,reg,0_,bit,_MASK)))
 #define USBC_EP_SET_BITS(reg, bit, ep) \
         (Set_bits(USBC_ARRAY(TPASTE2(reg,0),ep),\
         TPASTE5(AVR32_USBC_,reg,0_,bit,_MASK)))
 #define USBC_EP_TST_BITS(reg, bit, ep) \
         (Tst_bits(USBC_ARRAY(TPASTE2(reg,0),ep),\
         TPASTE5(AVR32_USBC_,reg,0_,bit,_MASK)))
 #define USBC_EP_RD_BITFIELD(reg, bit, ep) \
         (Rd_bitfield(USBC_ARRAY(TPASTE2(reg,0),ep),\
         TPASTE5(AVR32_USBC_,reg,0_,bit,_MASK)))
 #define USBC_EP_WR_BITFIELD(reg, bit, ep, value) \
         (Wr_bitfield(USBC_ARRAY(TPASTE2(reg,0),ep),\
         TPASTE5(AVR32_USBC_,reg,0_,bit,_MASK), value))
 #define USBC_EP_REG_CLR(reg, bit, ep) \
         (USBC_ARRAY(TPASTE2(reg,0CLR),ep) \
          = TPASTE5(AVR32_USBC_,reg,0CLR_,bit,C_MASK))
 #define USBC_EP_REG_SET(reg, bit, ep) \
         (USBC_ARRAY(TPASTE2(reg,0SET),ep) \
          = TPASTE5(AVR32_USBC_,reg,0SET_,bit,S_MASK))


 #define  udd_enable_endpoint(ep) \
         (Set_bits(AVR32_USBC.uerst, AVR32_USBC_UERST_EPEN0_MASK << (ep)))
 #define  udd_disable_endpoint(ep) \
         (Clr_bits(AVR32_USBC.uerst, AVR32_USBC_UERST_EPEN0_MASK << (ep)))
 #define  Is_udd_endpoint_enabled(ep) \
         (Tst_bits(AVR32_USBC.uerst, AVR32_USBC_UERST_EPEN0_MASK << (ep)))
 #define  udd_reset_endpoint(ep) \
         (Set_bits(AVR32_USBC.uerst, AVR32_USBC_UERST_EPRST0_MASK << (ep)),\
         Clr_bits(AVR32_USBC.uerst, AVR32_USBC_UERST_EPRST0_MASK << (ep)))
 #define  Is_udd_resetting_endpoint(ep) \
         (Tst_bits(AVR32_USBC.uerst, AVR32_USBC_UERST_EPRST0_MASK << (ep)))

 #define  udd_configure_endpoint_type(ep, type)     USBC_EP_WR_BITFIELD(UECFG,EPTYPE,ep,type)
 #define  udd_get_endpoint_type(ep)                 USBC_EP_RD_BITFIELD(UECFG,EPTYPE,ep)
 #define  udd_configure_endpoint_direction(ep, dir) USBC_EP_WR_BITFIELD(UECFG,EPDIR,ep,dir)
 #define  udd_get_endpoint_direction(ep)            USBC_EP_RD_BITFIELD(UECFG,EPDIR,ep)
 #define  Is_udd_endpoint_in(ep)                    USBC_EP_TST_BITS(UECFG,EPDIR,ep)



 #define  udd_format_endpoint_size(size)            (32 - clz(((uint32_t)min(max(size, 8), 1024) << 1) - 1) - 1 - 3)
 #define  udd_configure_endpoint_size(ep, size)     (USBC_EP_WR_BITFIELD(UECFG,EPSIZE,ep, udd_format_endpoint_size(size)))
 #define  udd_get_endpoint_size(ep)                 (8 << USBC_EP_RD_BITFIELD(UECFG,EPSIZE,ep))
 #define  udd_configure_endpoint_bank(ep, bank)     USBC_EP_WR_BITFIELD(UECFG,EPBK,ep,bank)
 #define  udd_get_endpoint_bank(ep)                 USBC_EP_RD_BITFIELD(UECFG,EPBK,ep)

 #define  udd_configure_endpoint(ep, type, dir, size, bank) \
 (\
    Wr_bits(USBC_ARRAY(uecfg0,ep), AVR32_USBC_UECFG0_EPTYPE_MASK |\
                                   AVR32_USBC_UECFG0_EPDIR_MASK  |\
                                   AVR32_USBC_UECFG0_EPSIZE_MASK |\
                                   AVR32_USBC_UECFG0_EPBK_MASK,   \
             (((uint32_t)(type) << AVR32_USBC_UECFG0_EPTYPE_OFFSET) & AVR32_USBC_UECFG0_EPTYPE_MASK) |\
             (((uint32_t)(dir ) << AVR32_USBC_UECFG0_EPDIR_OFFSET ) & AVR32_USBC_UECFG0_EPDIR_MASK ) |\
             ( (uint32_t)udd_format_endpoint_size(size) << AVR32_USBC_UECFG0_EPSIZE_OFFSET         ) |\
             (((uint32_t)(bank) << AVR32_USBC_UECFG0_EPBK_OFFSET  ) & AVR32_USBC_UECFG0_EPBK_MASK  ))\
 )

 #define  udd_reset_data_toggle(ep)                 USBC_EP_REG_SET(UECON,RSTDT,ep)
 #define  Is_udd_data_toggle_reset(ep)              USBC_EP_TST_BITS(UECON,RSTDT,ep)
 #define  udd_data_toggle(ep)                       USBC_EP_RD_BITFIELD(UESTA,DTSEQ,ep)




 #define  udd_enable_endpoint_interrupt(ep) \
         (AVR32_USBC.udinteset = AVR32_USBC_UDINTESET_EP0INTES_MASK << (ep))
 #define  udd_disable_endpoint_interrupt(ep) \
         (AVR32_USBC.udinteclr = AVR32_USBC_UDINTECLR_EP0INTEC_MASK << (ep))
 #define  Is_udd_endpoint_interrupt_enabled(ep) \
         (Tst_bits(AVR32_USBC.udinte, AVR32_USBC_UDINTE_EP0INTE_MASK << (ep)))
 #define  Is_udd_endpoint_interrupt(ep) \
         (Tst_bits(AVR32_USBC.udint, AVR32_USBC_UDINT_EP0INT_MASK << (ep)))
 #define  udd_get_interrupt_endpoint_number() \
         (ctz(((AVR32_USBC.udint >> AVR32_USBC_UDINT_EP0INT_OFFSET) &\
         (AVR32_USBC.udinte >> AVR32_USBC_UDINTE_EP0INTE_OFFSET)) |\
         (1 << AVR32_USBC_EPT_NUM)))


 #define  udd_enable_stall_handshake(ep)            USBC_EP_REG_SET(UECON,STALLRQ,ep)

 #define  udd_disable_stall_handshake(ep)           USBC_EP_REG_CLR(UECON,STALLRQ,ep)

 #define  Is_udd_endpoint_stall_requested(ep)       USBC_EP_TST_BITS(UECON,STALLRQ,ep)

 #define  Is_udd_stall(ep)                          USBC_EP_TST_BITS(UESTA,STALLEDI,ep)

 #define  udd_ack_stall(ep)                         USBC_EP_REG_CLR(UESTA,STALLEDI,ep)

 #define  udd_raise_stall(ep)                       USBC_EP_REG_SET(UESTA,STALLEDI,ep)

 #define  udd_enable_stall_interrupt(ep)            USBC_EP_REG_SET(UECON,STALLEDE,ep)

 #define  udd_disable_stall_interrupt(ep)           USBC_EP_REG_CLR(UECON,STALLEDE,ep)

 #define  Is_udd_stall_interrupt_enabled(ep)        USBC_EP_TST_BITS(UECON,STALLEDE,ep)

 #define  Is_udd_ram_access_error(ep)               USBC_EP_TST_BITS(UESTA,RAMACCERI,ep)

 #define  Is_udd_nak_out(ep)                        USBC_EP_TST_BITS(UESTA,NAKOUTI,ep)

 #define  udd_ack_nak_out(ep)                       USBC_EP_REG_CLR(UESTA,NAKOUTI,ep)

 #define  udd_raise_nak_out(ep)                     USBC_EP_REG_SET(UESTA,NAKOUTI,ep)

 #define  udd_enable_nak_out_interrupt(ep)          USBC_EP_REG_SET(UECON,NAKOUTE,ep)

 #define  udd_disable_nak_out_interrupt(ep)         USBC_EP_REG_CLR(UECON,NAKOUTE,ep)

 #define  Is_udd_nak_out_interrupt_enabled(ep)      USBC_EP_TST_BITS(UECON,NAKOUTE,ep)

 #define  Is_udd_nak_in(ep)                         USBC_EP_TST_BITS(UESTA,NAKINI,ep)

 #define  udd_ack_nak_in(ep)                        USBC_EP_REG_CLR(UESTA,NAKINI,ep)

 #define  udd_raise_nak_in(ep)                      USBC_EP_REG_SET(UESTA,NAKINI,ep)

 #define  udd_enable_nak_in_interrupt(ep)           USBC_EP_REG_SET(UECON,NAKINE,ep)

 #define  udd_disable_nak_in_interrupt(ep)          USBC_EP_REG_CLR(UECON,NAKINE,ep)

 #define  Is_udd_nak_in_interrupt_enabled(ep)       USBC_EP_TST_BITS(UECON,NAKINE,ep)

 #define  udd_ack_overflow_interrupt(ep)            USBC_EP_REG_CLR(UESTA,OVERFI,ep)

 #define  udd_raise_overflow_interrupt(ep)          USBC_EP_REG_SET(UESTA,OVERFI,ep)

 #define  Is_udd_overflow(ep)                       USBC_EP_TST_BITS(UESTA,OVERFI,ep)

 #define  udd_enable_overflow_interrupt(ep)         USBC_EP_REG_SET(UECON,OVERFE,ep)

 #define  udd_disable_overflow_interrupt(ep)        USBC_EP_REG_CLR(UECON,OVERFE,ep)

 #define  Is_udd_overflow_interrupt_enabled(ep)     USBC_EP_TST_BITS(UECON,OVERFE,ep)

 #define  udd_ack_underflow_interrupt(ep)           USBC_EP_REG_CLR(UESTA,UNDERFI,ep)

 #define  udd_raise_underflow_interrupt(ep)         USBC_EP_REG_SET(UESTA,UNDERFI,ep)

 #define  Is_udd_underflow(ep)                      USBC_EP_TST_BITS(UESTA,UNDERFI,ep)

 #define  udd_enable_underflow_interrupt(ep)        USBC_EP_REG_SET(UECON,RXSTPE,ep)

 #define  udd_disable_underflow_interrupt(ep)       USBC_EP_REG_CLR(UECON,RXSTPE,ep)

 #define  Is_udd_underflow_interrupt_enabled(ep)    USBC_EP_TST_BITS(UECON,RXSTPE,ep)

 #define  Is_udd_crc_error(ep)                      USBC_EP_TST_BITS(UESTA,STALLEDI,ep)

 #define  udd_ack_crc_error(ep)                     USBC_EP_REG_CLR(UESTA,STALLEDI,ep)

 #define  udd_raise_crc_error(ep)                   USBC_EP_REG_SET(UESTA,STALLEDI,ep)

 #define  udd_enable_crc_error_interrupt(ep)        USBC_EP_REG_SET(UECON,STALLEDE,ep)

 #define  udd_disable_crc_error_interrupt(ep)       USBC_EP_REG_CLR(UECON,STALLEDE,ep)

 #define  Is_udd_crc_error_interrupt_enabled(ep)    USBC_EP_TST_BITS(UECON,STALLEDE,ep)


 #define  udd_ack_fifocon(ep)                       USBC_EP_REG_CLR(UECON,FIFOCON,ep)
 #define  Is_udd_fifocon(ep)                        USBC_EP_TST_BITS(UECON,FIFOCON,ep)

 #define  udd_disable_nyet(ep)                      USBC_EP_REG_SET(UECON,NYETDIS,ep)
 #define  udd_enable_nyet(ep)                       USBC_EP_REG_CLR(UECON,NYETDIS,ep)

 #define  udd_enable_busy_bank0(ep)                 USBC_EP_REG_SET(UECON,BUSY0,ep)
 #define  udd_disable_busy_bank0(ep)                USBC_EP_REG_CLR(UECON,BUSY0,ep)
 #define  udd_enable_busy_bank1(ep)                 USBC_EP_REG_SET(UECON,BUSY1,ep)
 #define  udd_disable_busy_bank1(ep)                USBC_EP_REG_CLR(UECON,BUSY1,ep)
 #define  udd_nb_busy_bank(ep)                      USBC_EP_RD_BITFIELD(UESTA,NBUSYBK,ep)
 #define  udd_current_bank(ep)                      USBC_EP_RD_BITFIELD(UESTA,CURRBK,ep)

 #define  udd_kill_last_in_bank(ep)                 USBC_EP_REG_SET(UECON,KILLBK,ep)
 #define  Is_udd_last_in_bank_killed(ep)            USBC_EP_TST_BITS(UECON,KILLBK,ep)
 #define  udd_force_bank_interrupt(ep)              USBC_EP_REG_SET(UESTA,NBUSYBK,ep)
 #define  udd_unforce_bank_interrupt(ep)            USBC_EP_REG_SET(UESTA,NBUSYBK,ep)
 #define  udd_enable_bank_interrupt(ep)             USBC_EP_REG_SET(UECON,NBUSYBKE,ep)
 #define  udd_disable_bank_interrupt(ep)            USBC_EP_REG_CLR(UECON,NBUSYBKE,ep)
 #define  Is_udd_bank_interrupt_enabled(ep)         USBC_EP_TST_BITS(UECON,NBUSYBKE,ep)

 #define  Is_udd_short_packet(ep)                   USBC_EP_TST_BITS(UESTA,SHORTPACKETI,ep)
 #define  udd_ack_short_packet(ep)                  USBC_EP_REG_CLR(UESTA,SHORTPACKETI,ep)
 #define  udd_raise_short_packet(ep)                USBC_EP_REG_SET(UESTA,SHORTPACKETI,ep)
 #define  udd_enable_short_packet_interrupt(ep)     USBC_EP_REG_SET(UECON,SHORTPACKETE,ep)
 #define  udd_disable_short_packet_interrupt(ep)    USBC_EP_REG_CLR(UECON,SHORTPACKETE,ep)
 #define  Is_udd_short_packet_interrupt_enabled(ep) USBC_EP_TST_BITS(UECON,SHORTPACKETE,ep)


 #define  Is_udd_setup_received(ep)                 USBC_EP_TST_BITS(UESTA,RXSTPI,ep)
 #define  udd_ack_setup_received(ep)                USBC_EP_REG_CLR(UESTA,RXSTPI,ep)
 #define  udd_raise_setup_received(ep)              USBC_EP_REG_SET(UESTA,RXSTPI,ep)
 #define  udd_enable_setup_received_interrupt(ep)   USBC_EP_REG_SET(UECON,RXSTPE,ep)
 #define  udd_disable_setup_received_interrupt(ep)  USBC_EP_REG_CLR(UECON,RXSTPE,ep)
 #define  Is_udd_setup_received_interrupt_enabled(ep) USBC_EP_TST_BITS(UECON,RXSTPE,ep)

 #define  Is_udd_out_received(ep)                   USBC_EP_TST_BITS(UESTA,RXOUTI,ep)
 #define  udd_ack_out_received(ep)                  USBC_EP_REG_CLR(UESTA,RXOUTI,ep)
 #define  udd_raise_out_received(ep)                USBC_EP_REG_SET(UESTA,RXOUTI,ep)
 #define  udd_enable_out_received_interrupt(ep)     USBC_EP_REG_SET(UECON,RXOUTE,ep)
 #define  udd_disable_out_received_interrupt(ep)    USBC_EP_REG_CLR(UECON,RXOUTE,ep)
 #define  Is_udd_out_received_interrupt_enabled(ep) USBC_EP_TST_BITS(UECON,RXOUTE,ep)

 #define  Is_udd_in_send(ep)                        USBC_EP_TST_BITS(UESTA,TXINI,ep)
 #define  udd_ack_in_send(ep)                       USBC_EP_REG_CLR(UESTA,TXINI,ep)
 #define  udd_raise_in_send(ep)                     USBC_EP_REG_SET(UESTA,TXINI,ep)
 #define  udd_enable_in_send_interrupt(ep)          USBC_EP_REG_SET(UECON,TXINE,ep)
 #define  udd_disable_in_send_interrupt(ep)         USBC_EP_REG_CLR(UECON,TXINE,ep)
 #define  Is_udd_in_send_interrupt_enabled(ep)      USBC_EP_TST_BITS(UECON,TXINE,ep)


 #define udd_udesc_set_buf0_addr(ep,buf)                \
    udd_g_ep_table[ep*2].endpoint_pipe_address = buf
 #define udd_udesc_rst_buf0_size(ep)                    \
    udd_g_ep_table[ep*2].SIZES.multi_packet_size = 0
 #define udd_udesc_get_buf0_size(ep)                    \
    udd_g_ep_table[ep*2].SIZES.multi_packet_size
 #define udd_udesc_set_buf0_size(ep,size)               \
    udd_g_ep_table[ep*2].SIZES.multi_packet_size = size
 #define udd_udesc_rst_buf0_ctn(ep)                     \
    udd_g_ep_table[ep*2].SIZES.byte_count = 0
 #define udd_udesc_get_buf0_ctn(ep)                     \
    udd_g_ep_table[ep*2].SIZES.byte_count
 #define udd_udesc_set_buf0_ctn(ep,size)                \
    udd_g_ep_table[ep*2].SIZES.byte_count = size
 #define udd_udesc_set_buf0_autozlp(ep,val)             \
    udd_g_ep_table[ep*2].SIZES.auto_zlp = val

 // Maximum size of a tranfer in multipacket mode
 #define UDD_ENDPOINT_MAX_TRANS ((32*1024)-1)

 struct avr32_usbc_udesc_sizes_t {
     unsigned int auto_zlp:1;
     unsigned int multi_packet_size:15;
     unsigned int res:1;
     unsigned int byte_count:15;
 };

 struct avr32_usbc_udesc_bk_ctrl_stat_t {
     unsigned int res:13;
     unsigned int underfi:1;
     unsigned int overfi:1;
     unsigned int crc:1;
     unsigned int res2:16;
 };

 struct avr32_usbc_udesc_ep_ctrl_stat_t {
     unsigned int res:8;
     unsigned int pipe_error_status:8;
     unsigned int pipe_error_number_max:4;
     unsigned int pep_num:4;
     unsigned int res2:1;
     unsigned int uhaddr:7;
 };

 typedef struct {
     uint8_t *endpoint_pipe_address;
     union {
         unsigned long sizes;
         struct avr32_usbc_udesc_sizes_t SIZES;
     };
     union {
         unsigned long bk_ctrl_stat;
         struct avr32_usbc_udesc_bk_ctrl_stat_t BK_CTRL_STAT;
     };
     union {
         unsigned long ep_ctrl_stat;
         struct avr32_usbc_udesc_ep_ctrl_stat_t EP_CTRL_STAT;
     };
 } usb_desc_table_t;


 #endif // _USBC_DEVICE_H_

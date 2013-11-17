
 #ifndef _FLASHCDW_H_
 #define _FLASHCDW_H_

 #include <avr32/io.h>
 #include <stddef.h>
 #include "compiler.h"


 #ifdef AVR32_FLASHCDW_101_H_INCLUDED

 #define AVR32_FLASHCDW_FGPFRLO_UPROT                                    22
 #define AVR32_FLASHCDW_FGPFRLO_UPROT_MASK                       0x00400000
 #define AVR32_FLASHCDW_FGPFRLO_UPROT_OFFSET                             22
 #define AVR32_FLASHCDW_FGPFRLO_UPROT_SIZE                                1

 #define AVR32_FLASHCDW_FGPFRLO_SECURE                                   20
 #define AVR32_FLASHCDW_FGPFRLO_SECURE_MASK                      0x00300000
 #define AVR32_FLASHCDW_FGPFRLO_SECURE_OFFSET                            20
 #define AVR32_FLASHCDW_FGPFRLO_SECURE_SIZE                               2

 #define AVR32_FLASHCDW_FGPFRLO_SECURE_SSEN_SSDDIS                         2

 #define AVR32_FLASHCDW_FGPFRLO_SECURE_SSEN_SSDEN                          1

 // These defines are missing from or wrong in the toolchain header file flashcdw_101.h
 // #9267
 #endif


 #define AVR32_FLASHCDW_REGIONS  (AVR32_FLASHCDW_FLASH_SIZE /\
         (AVR32_FLASHCDW_PAGES_PR_REGION * AVR32_FLASHCDW_PAGE_SIZE))




 extern unsigned int flashcdw_get_flash_size(void);

 extern unsigned int flashcdw_get_page_count(void);

 extern unsigned int flashcdw_get_page_count_per_region(void);

 extern unsigned int flashcdw_get_page_region(int page_number);

 extern unsigned int flashcdw_get_region_first_page_number(unsigned int region);





 extern unsigned int flashcdw_get_wait_state(void);

 extern void flashcdw_set_wait_state(unsigned int wait_state);

 extern void flashcdw_set_flash_waitstate_and_readmode(unsigned long cpu_f_hz);

 #define flash_set_bus_freq(cpu_f_hz) flashcdw_set_flash_waitstate_and_readmode(cpu_f_hz)

 extern bool flashcdw_is_ready_int_enabled(void);

 extern void flashcdw_enable_ready_int(bool enable);

 extern bool flashcdw_is_lock_error_int_enabled(void);

 extern void flashcdw_enable_lock_error_int(bool enable);

 extern bool flashcdw_is_prog_error_int_enabled(void);

 extern void flashcdw_enable_prog_error_int(bool enable);





 extern bool flashcdw_is_ready(void);

 extern void flashcdw_default_wait_until_ready(void);

 extern void (*volatile flashcdw_wait_until_ready)(void);

 extern bool flashcdw_is_lock_error(void);

 extern bool flashcdw_is_programming_error(void);

 extern bool flashcdw_is_high_speed_enabled(void);





 extern unsigned int flashcdw_get_command(void);

 extern unsigned int flashcdw_get_page_number(void);

 extern void flashcdw_issue_command(unsigned int command, int page_number);





 extern void flashcdw_no_operation(void);

 extern void flashcdw_erase_all(void);





 extern bool flashcdw_is_security_bit_active(void);

 extern void flashcdw_activate_security_bit(void);

 extern unsigned int flashcdw_get_bootloader_protected_size(void);

 extern unsigned int flashcdw_set_bootloader_protected_size(unsigned int bootprot_size);

 extern bool flashcdw_is_external_privileged_fetch_locked(void);

 extern void flashcdw_lock_external_privileged_fetch(bool lock);

 extern bool flashcdw_is_jtag_user_protection_enabled(void);

 extern void flashcdw_enable_jtag_user_protection(void);

 extern void flashcdw_disable_jtag_user_protection(void);

 extern bool flashcdw_is_secure_state_enabled(void);

 extern bool flashcdw_is_secure_state_debug_enabled(void);

 extern void flashcdw_enable_secure_state_no_debug(void);

 extern void flashcdw_enable_secure_state_with_debug(void);

 extern bool flashcdw_is_page_region_locked(int page_number);

 extern bool flashcdw_is_region_locked(unsigned int region);

 extern void flashcdw_lock_page_region(int page_number, bool lock);

 extern void flashcdw_lock_region(unsigned int region, bool lock);

 extern void flashcdw_lock_all_regions(bool lock);





 extern bool flashcdw_read_gp_fuse_bit(unsigned int gp_fuse_bit);

 extern uint64_t flashcdw_read_gp_fuse_bitfield(unsigned int pos, unsigned int width);

 extern uint8_t flashcdw_read_gp_fuse_byte(unsigned int gp_fuse_byte);

 extern uint64_t flashcdw_read_all_gp_fuses(void);

 extern bool flashcdw_erase_gp_fuse_bit(unsigned int gp_fuse_bit, bool check);

 extern bool flashcdw_erase_gp_fuse_bitfield(unsigned int pos, unsigned int width, bool check);

 extern bool flashcdw_erase_gp_fuse_byte(unsigned int gp_fuse_byte, bool check);

 extern bool flashcdw_erase_all_gp_fuses(bool check);

 extern void flashcdw_write_gp_fuse_bit(unsigned int gp_fuse_bit, bool value);

 extern void flashcdw_write_gp_fuse_bitfield(unsigned int pos, unsigned int width, uint64_t value);

 extern void flashcdw_write_gp_fuse_byte(unsigned int gp_fuse_byte, uint8_t value);

 extern void flashcdw_write_all_gp_fuses(uint64_t value);

 extern void flashcdw_set_gp_fuse_bit(unsigned int gp_fuse_bit, bool value);

 extern void flashcdw_set_gp_fuse_bitfield(unsigned int pos, unsigned int width, uint64_t value);

 extern void flashcdw_set_gp_fuse_byte(unsigned int gp_fuse_byte, uint8_t value);

 extern void flashcdw_set_all_gp_fuses(uint64_t value);





 extern void flashcdw_clear_page_buffer(void);

 extern bool flashcdw_is_page_erased(void);

 extern bool flashcdw_quick_page_read(int page_number);

 extern bool flashcdw_erase_page(int page_number, bool check);

 extern bool flashcdw_erase_all_pages(bool check);

 extern void flashcdw_write_page(int page_number);

 extern bool flashcdw_quick_user_page_read(void);

 extern bool flashcdw_erase_user_page(bool check);

 extern void flashcdw_write_user_page(void);

 extern volatile void *flashcdw_memset8(volatile void *dst, uint8_t src, size_t nbytes, bool erase);

 extern volatile void *flashcdw_memset16(volatile void *dst, uint16_t src, size_t nbytes, bool erase);

 extern volatile void *flashcdw_memset32(volatile void *dst, uint32_t src, size_t nbytes, bool erase);

 extern volatile void *flashcdw_memset64(volatile void *dst, uint64_t src, size_t nbytes, bool erase);

 #define flashcdw_memset(dst, src, src_width, nbytes, erase) \
     TPASTE2(flashcdw_memset, src_width)((dst), (src), (nbytes), (erase))

 extern volatile void *flashcdw_memcpy(volatile void *dst, const void *src, size_t nbytes, bool erase);


 #endif  // _FLASHCDW_H_

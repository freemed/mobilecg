
 #ifndef _COMPILER_AVR32_H_
 #define _COMPILER_AVR32_H_

 #if (defined __ICCAVR32__)
 #  include <intrinsics.h>
 #endif
 #include "preprocessor.h"

 #include "parts.h"


 //_____ D E C L A R A T I O N S ____________________________________________

 #ifdef __AVR32_ABI_COMPILER__ // Automatically defined when compiling for AVR32, not when assembling.

 #include <stddef.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include <stdint.h>


 #if (defined __ICCAVR32__)


 #define __asm__             asm
 #define __inline__          inline
 #define __volatile__


 #endif

 #if defined(__GNUC__)
 #  define barrier()        asm volatile("" ::: "memory")
 #elif defined(__ICCAVR32__)
 #  define barrier()        __asm__ __volatile__ ("")
 #endif

 #define COMPILER_PRAGMA(arg)            _Pragma(#arg)

 #define COMPILER_PACK_SET(alignment)   COMPILER_PRAGMA(pack(alignment))

 #define COMPILER_PACK_RESET()          COMPILER_PRAGMA(pack())


 #if (defined __GNUC__)
 #define COMPILER_ALIGNED(a)    __attribute__((__aligned__(a)))
 #elif (defined __ICCAVR32__)
 #define COMPILER_ALIGNED(a)    COMPILER_PRAGMA(data_alignment = a)
 #endif

 #if (defined __GNUC__)
 #define COMPILER_WORD_ALIGNED    __attribute__((__aligned__(4)))
 #elif (defined __ICCAVR32__)
 #define COMPILER_WORD_ALIGNED    COMPILER_PRAGMA(data_alignment = 4)
 #endif

 #if defined(__GNUC__) || defined(__DOXYGEN__)

 #  define sysreg_read(reg)               __builtin_mfsr(reg)

 #if ((defined __GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >=1)))
 #define __DEPRECATED__  __attribute__((__deprecated__))
 #else
 #define __DEPRECATED__
 #endif


 #  define sysreg_write(reg, val)         __builtin_mtsr(reg, val)

 #elif defined(__ICCAVR32__)
 #  define sysreg_read(reg)               __get_system_register(reg)
 #  define sysreg_write(reg, val)         __set_system_register(reg, val)
 #endif

 // Deprecated definitions
 #define Get_system_register(reg)         sysreg_read(reg)
 #define Set_system_register(reg, val)    sysreg_write(reg, val)


 #include "interrupt.h"


 typedef unsigned char           Bool;
 #ifndef __cplusplus
 #if !defined(__bool_true_false_are_defined)
 typedef unsigned char           bool;
 #endif
 #endif
 typedef int8_t                  S8 ; 
 typedef uint8_t                 U8 ; 
 typedef int16_t                 S16; 
 typedef uint16_t                U16; 
 typedef uint16_t                le16_t;
 typedef uint16_t                be16_t;
 typedef int32_t                 S32; 
 typedef uint32_t                U32; 
 typedef uint32_t                le32_t;
 typedef uint32_t                be32_t;
 typedef signed long long int    S64; 
 typedef unsigned long long int  U64; 
 typedef float                   F32; 
 typedef double                  F64; 
 typedef uint32_t                iram_size_t;



 typedef bool                Status_bool_t; 
 typedef U8                  Status_t;      





 typedef union
 {
   S16 s16   ;
   U16 u16   ;
   S8  s8 [2];
   U8  u8 [2];
 } Union16;

 typedef union
 {
   S32 s32   ;
   U32 u32   ;
   S16 s16[2];
   U16 u16[2];
   S8  s8 [4];
   U8  u8 [4];
 } Union32;

 typedef union
 {
   S64 s64   ;
   U64 u64   ;
   S32 s32[2];
   U32 u32[2];
   S16 s16[4];
   U16 u16[4];
   S8  s8 [8];
   U8  u8 [8];
 } Union64;

 typedef union
 {
   S64 *s64ptr;
   U64 *u64ptr;
   S32 *s32ptr;
   U32 *u32ptr;
   S16 *s16ptr;
   U16 *u16ptr;
   S8  *s8ptr ;
   U8  *u8ptr ;
 } UnionPtr;

 typedef union
 {
   volatile S64 *s64ptr;
   volatile U64 *u64ptr;
   volatile S32 *s32ptr;
   volatile U32 *u32ptr;
   volatile S16 *s16ptr;
   volatile U16 *u16ptr;
   volatile S8  *s8ptr ;
   volatile U8  *u8ptr ;
 } UnionVPtr;

 typedef union
 {
   const S64 *s64ptr;
   const U64 *u64ptr;
   const S32 *s32ptr;
   const U32 *u32ptr;
   const S16 *s16ptr;
   const U16 *u16ptr;
   const S8  *s8ptr ;
   const U8  *u8ptr ;
 } UnionCPtr;

 typedef union
 {
   const volatile S64 *s64ptr;
   const volatile U64 *u64ptr;
   const volatile S32 *s32ptr;
   const volatile U32 *u32ptr;
   const volatile S16 *s16ptr;
   const volatile U16 *u16ptr;
   const volatile S8  *s8ptr ;
   const volatile U8  *u8ptr ;
 } UnionCVPtr;

 typedef struct
 {
   S64 *s64ptr;
   U64 *u64ptr;
   S32 *s32ptr;
   U32 *u32ptr;
   S16 *s16ptr;
   U16 *u16ptr;
   S8  *s8ptr ;
   U8  *u8ptr ;
 } StructPtr;

 typedef struct
 {
   volatile S64 *s64ptr;
   volatile U64 *u64ptr;
   volatile S32 *s32ptr;
   volatile U32 *u32ptr;
   volatile S16 *s16ptr;
   volatile U16 *u16ptr;
   volatile S8  *s8ptr ;
   volatile U8  *u8ptr ;
 } StructVPtr;

 typedef struct
 {
   const S64 *s64ptr;
   const U64 *u64ptr;
   const S32 *s32ptr;
   const U32 *u32ptr;
   const S16 *s16ptr;
   const U16 *u16ptr;
   const S8  *s8ptr ;
   const U8  *u8ptr ;
 } StructCPtr;

 typedef struct
 {
   const volatile S64 *s64ptr;
   const volatile U64 *u64ptr;
   const volatile S32 *s32ptr;
   const volatile U32 *u32ptr;
   const volatile S16 *s16ptr;
   const volatile U16 *u16ptr;
   const volatile S8  *s8ptr ;
   const volatile U8  *u8ptr ;
 } StructCVPtr;


 #endif  // __AVR32_ABI_COMPILER__


 //_____ M A C R O S ________________________________________________________


 #define DISABLE   0
 #define ENABLE    1
 #ifndef __cplusplus
 #if !defined(__bool_true_false_are_defined)
 #define false     0
 #define true      1
 #endif
 #endif
 #define PASS      0
 #define FAIL      1
 #define LOW       0
 #define HIGH      1



 #ifdef __AVR32_ABI_COMPILER__ // Automatically defined when compiling for AVR32, not when assembling.



 #ifndef likely
 # define likely(exp)    (exp)
 #endif

 #ifndef unlikely
 # define unlikely(exp)  (exp)
 #endif

 #ifdef __GNUC__
 # define is_constant(exp)       __builtin_constant_p(exp)
 #else
 # define is_constant(exp)       (0)
 #endif




 #define Rd_bits( value, mask)        ((value) & (mask))

 #define Wr_bits(lvalue, mask, bits)  ((lvalue) = ((lvalue) & ~(mask)) |\
                                                  ((bits  ) &  (mask)))

 #define Tst_bits( value, mask)  (Rd_bits(value, mask) != 0)

 #define Clr_bits(lvalue, mask)  ((lvalue) &= ~(mask))

 #define Set_bits(lvalue, mask)  ((lvalue) |=  (mask))

 #define Tgl_bits(lvalue, mask)  ((lvalue) ^=  (mask))

 #define Rd_bitfield( value, mask)           (Rd_bits( value, mask) >> ctz(mask))

 #define Wr_bitfield(lvalue, mask, bitfield) (Wr_bits(lvalue, mask, (U32)(bitfield) << ctz(mask)))



 #if (defined __GNUC__)
 # define cpu_relax()             __asm__ __volatile__("sub pc, pc, -4" ::: "memory", "cc")
 #elif (defined __ICCAVR32__)
 # define cpu_relax()             __asm__ __volatile__("sub pc, pc, -4")
 #endif


 #if defined(_ASSERT_ENABLE_)
 #  if defined(TEST_SUITE_DEFINE_ASSERT_MACRO)
     // Assert() is defined in unit_test/suite.h
 #    include "unit_test/suite.h"
 #  else
 #    define Assert(expr) \
     {\
         if (!(expr)) while (true);\
     }
 #  endif
 #else
 #  define Assert(expr) ((void) 0)
 #endif




 #if (defined __GNUC__)
   #define clz(u)              __builtin_clz(u)
 #elif (defined __ICCAVR32__)
   #if (__VER__ == 330) && (__SUBVERSION__ <= 1)
     // __count_leading_zeros is broken and returns a value which is offset by
     // -32 when called with a constant parameter.
     #define clz(v) (0 == v ? 32 : (31 & __count_leading_zeros(v)))
   #else
     #define clz(v) __count_leading_zeros(v)
   #endif
 #endif

 #if (defined __GNUC__)
   #define ctz(u)              __builtin_ctz(u)
 #elif (defined __ICCAVR32__)
   #define ctz(u)              __count_trailing_zeros(u)
 #endif



 int_fast8_t ilog2_undefined(void);

 static inline int_fast8_t ilog2(uint32_t x)
 {
     if (is_constant(x))
         return ((x) & (1ULL << 31) ? 31 :
             (x) & (1ULL << 30) ? 30 :
             (x) & (1ULL << 29) ? 29 :
             (x) & (1ULL << 28) ? 28 :
             (x) & (1ULL << 27) ? 27 :
             (x) & (1ULL << 26) ? 26 :
             (x) & (1ULL << 25) ? 25 :
             (x) & (1ULL << 24) ? 24 :
             (x) & (1ULL << 23) ? 23 :
             (x) & (1ULL << 22) ? 22 :
             (x) & (1ULL << 21) ? 21 :
             (x) & (1ULL << 20) ? 20 :
             (x) & (1ULL << 19) ? 19 :
             (x) & (1ULL << 18) ? 18 :
             (x) & (1ULL << 17) ? 17 :
             (x) & (1ULL << 16) ? 16 :
             (x) & (1ULL << 15) ? 15 :
             (x) & (1ULL << 14) ? 14 :
             (x) & (1ULL << 13) ? 13 :
             (x) & (1ULL << 12) ? 12 :
             (x) & (1ULL << 11) ? 11 :
             (x) & (1ULL << 10) ? 10 :
             (x) & (1ULL <<  9) ?  9 :
             (x) & (1ULL <<  8) ?  8 :
             (x) & (1ULL <<  7) ?  7 :
             (x) & (1ULL <<  6) ?  6 :
             (x) & (1ULL <<  5) ?  5 :
             (x) & (1ULL <<  4) ?  4 :
             (x) & (1ULL <<  3) ?  3 :
             (x) & (1ULL <<  2) ?  2 :
             (x) & (1ULL <<  1) ?  1 :
             (x) & (1ULL <<  0) ?  0 :
             ilog2_undefined());

     return 31 - clz(x);
 }




 #define bit_reverse8(u8)    ((U8)(bit_reverse32((U8)(u8)) >> 24))

 #define bit_reverse16(u16)  ((U16)(bit_reverse32((U16)(u16)) >> 16))

 #if (defined __GNUC__)
   #define bit_reverse32(u32) \
   (\
     {\
       unsigned int __value = (U32)(u32);\
       __asm__ ("brev\t%0" : "+r" (__value) :  : "cc");\
       (U32)__value;\
     }\
   )
 #elif (defined __ICCAVR32__)
   #define bit_reverse32(u32)  ((U32)__bit_reverse((U32)(u32)))
 #endif

 #define bit_reverse64(u64)  ((U64)(((U64)bit_reverse32((U64)(u64) >> 32)) |\
                                    ((U64)bit_reverse32((U64)(u64)) << 32)))





 #define Test_align(val, n     ) (!Tst_bits( val, (n) - 1     )   )

 #define Get_align( val, n     ) (  Rd_bits( val, (n) - 1     )   )

 #define Set_align(lval, n, alg) (  Wr_bits(lval, (n) - 1, alg)   )

 #define Align_up(  val, n     ) (((val) + ((n) - 1)) & ~((n) - 1))

 #define Align_down(val, n     ) ( (val)              & ~((n) - 1))





 #define Abs(a)              (((a) <  0 ) ? -(a) : (a))

 #define Min(a, b)           (((a) < (b)) ?  (a) : (b))

 #define Max(a, b)           (((a) > (b)) ?  (a) : (b))

 #if (defined __GNUC__)
   #define abs(a) \
   (\
     {\
       int __value = (a);\
       __asm__ ("abs\t%0" : "+r" (__value) :  : "cc");\
       __value;\
     }\
   )
 #elif (defined __ICCAVR32__)
   #define abs(a)      Abs(a)
 #endif

 #if (defined __GNUC__)
   #define min(a, b) \
   (\
     {\
       int __value, __arg_a = (a), __arg_b = (b);\
       __asm__ ("min\t%0, %1, %2" : "=r" (__value) : "r" (__arg_a), "r" (__arg_b));\
       __value;\
     }\
   )
 #elif (defined __ICCAVR32__)
   #define min(a, b)   __min(a, b)
 #endif

 #if (defined __GNUC__)
   #define max(a, b) \
   (\
     {\
       int __value, __arg_a = (a), __arg_b = (b);\
       __asm__ ("max\t%0, %1, %2" : "=r" (__value) : "r" (__arg_a), "r" (__arg_b));\
       __value;\
     }\
   )
 #elif (defined __ICCAVR32__)
   #define max(a, b)   __max(a, b)
 #endif



 #define Long_call(addr)                   ((*(void (*)(void))(addr))())

 #if (defined __GNUC__)
   #define Reset_CPU() \
   (\
     {\
       __asm__ __volatile__ (\
         "lddpc   r9, 3f\n\t"\
         "mfsr    r8, %[SR]\n\t"\
         "bfextu  r8, r8, %[SR_M_OFFSET], %[SR_M_SIZE]\n\t"\
         "cp.w    r8, 0b001\n\t"\
         "breq    0f\n\t"\
         "sub     r8, pc, $ - 1f\n\t"\
         "pushm   r8-r9\n\t"\
         "rete\n"\
         "0:\n\t"\
         "mtsr    %[SR], r9\n"\
         "1:\n\t"\
         "mov     r0, 0\n\t"\
         "mov     r1, 0\n\t"\
         "mov     r2, 0\n\t"\
         "mov     r3, 0\n\t"\
         "mov     r4, 0\n\t"\
         "mov     r5, 0\n\t"\
         "mov     r6, 0\n\t"\
         "mov     r7, 0\n\t"\
         "mov     r8, 0\n\t"\
         "mov     r9, 0\n\t"\
         "mov     r10, 0\n\t"\
         "mov     r11, 0\n\t"\
         "mov     r12, 0\n\t"\
         "mov     sp, 0\n\t"\
         "stdsp   sp[0], sp\n\t"\
         "ldmts   sp, sp\n\t"\
         "mov     lr, 0\n\t"\
         "lddpc   pc, 2f\n\t"\
         ".balign 4\n"\
         "2:\n\t"\
         ".word   _start\n"\
         "3:\n\t"\
         ".word   %[RESET_SR]"\
         :\
         : [SR] "i" (AVR32_SR),\
           [SR_M_OFFSET] "i" (AVR32_SR_M_OFFSET),\
           [SR_M_SIZE] "i" (AVR32_SR_M_SIZE),\
           [RESET_SR] "i" (AVR32_SR_GM_MASK | AVR32_SR_EM_MASK | (AVR32_SR_M_SUP << AVR32_SR_M_OFFSET))\
       );\
     }\
   )
 #elif (defined __ICCAVR32__)
   #define Reset_CPU() \
   {\
     extern void *volatile __program_start;\
     __asm__ __volatile__ (\
       "mov     r7, LWRD(__program_start)\n\t"\
       "orh     r7, HWRD(__program_start)\n\t"\
       "mov     r9, LWRD("ASTRINGZ(AVR32_SR_GM_MASK | AVR32_SR_EM_MASK | (AVR32_SR_M_SUP << AVR32_SR_M_OFFSET))")\n\t"\
       "orh     r9, HWRD("ASTRINGZ(AVR32_SR_GM_MASK | AVR32_SR_EM_MASK | (AVR32_SR_M_SUP << AVR32_SR_M_OFFSET))")\n\t"\
       "mfsr    r8, "ASTRINGZ(AVR32_SR)"\n\t"\
       "bfextu  r8, r8, "ASTRINGZ(AVR32_SR_M_OFFSET)", "ASTRINGZ(AVR32_SR_M_SIZE)"\n\t"\
       "cp.w    r8, 001b\n\t"\
       "breq    $ + 10\n\t"\
       "sub     r8, pc, -12\n\t"\
       "pushm   r8-r9\n\t"\
       "rete\n\t"\
       "mtsr    "ASTRINGZ(AVR32_SR)", r9\n\t"\
       "mov     r0, 0\n\t"\
       "mov     r1, 0\n\t"\
       "mov     r2, 0\n\t"\
       "mov     r3, 0\n\t"\
       "mov     r4, 0\n\t"\
       "mov     r5, 0\n\t"\
       "mov     r6, 0\n\t"\
       "st.w    r0[4], r7\n\t"\
       "mov     r7, 0\n\t"\
       "mov     r8, 0\n\t"\
       "mov     r9, 0\n\t"\
       "mov     r10, 0\n\t"\
       "mov     r11, 0\n\t"\
       "mov     r12, 0\n\t"\
       "mov     sp, 0\n\t"\
       "stdsp   sp[0], sp\n\t"\
       "ldmts   sp, sp\n\t"\
       "mov     lr, 0\n\t"\
       "ld.w    pc, lr[4]"\
     );\
     __program_start;\
   }
 #endif





 #define Is_global_exception_enabled()         (!Tst_bits(Get_system_register(AVR32_SR), AVR32_SR_EM_MASK))

 #if (defined __GNUC__)
   #define Disable_global_exception()          ({__asm__ __volatile__ ("ssrf\t%0" :  : "i" (AVR32_SR_EM_OFFSET));})
 #elif (defined __ICCAVR32__)
   #define Disable_global_exception()          (__set_status_flag(AVR32_SR_EM_OFFSET))
 #endif

 #if (defined __GNUC__)
   #define Enable_global_exception()           ({__asm__ __volatile__ ("csrf\t%0" :  : "i" (AVR32_SR_EM_OFFSET));})
 #elif (defined __ICCAVR32__)
   #define Enable_global_exception()           (__clear_status_flag(AVR32_SR_EM_OFFSET))
 #endif





 #if (defined __GNUC__)
   #define Get_debug_register(dbgreg)          __builtin_mfdr(dbgreg)
 #elif (defined __ICCAVR32__)
   #define Get_debug_register(dbgreg)          __get_debug_register(dbgreg)
 #endif

 #if (defined __GNUC__)
   #define Set_debug_register(dbgreg, value)   __builtin_mtdr(dbgreg, value)
 #elif (defined __ICCAVR32__)
   #define Set_debug_register(dbgreg, value)   __set_debug_register(dbgreg, value)
 #endif




 #if (defined __GNUC__)
 #define __always_inline     __attribute__((__always_inline__))
 #elif (defined __ICCAVR32__)
 #define __always_inline     _Pragma("inline=forced")
 #endif



 #define  MSB(u16)       (((U8  *)&(u16))[0]) //!< Most significant byte of \a u16.
 #define  LSB(u16)       (((U8  *)&(u16))[1]) //!< Least significant byte of \a u16.

 #define  MSH(u32)       (((U16 *)&(u32))[0]) //!< Most significant half-word of \a u32.
 #define  LSH(u32)       (((U16 *)&(u32))[1]) //!< Least significant half-word of \a u32.
 #define  MSB0W(u32)     (((U8  *)&(u32))[0]) //!< Most significant byte of 1st rank of \a u32.
 #define  MSB1W(u32)     (((U8  *)&(u32))[1]) //!< Most significant byte of 2nd rank of \a u32.
 #define  MSB2W(u32)     (((U8  *)&(u32))[2]) //!< Most significant byte of 3rd rank of \a u32.
 #define  MSB3W(u32)     (((U8  *)&(u32))[3]) //!< Most significant byte of 4th rank of \a u32.
 #define  LSB3W(u32)     MSB0W(u32)           //!< Least significant byte of 4th rank of \a u32.
 #define  LSB2W(u32)     MSB1W(u32)           //!< Least significant byte of 3rd rank of \a u32.
 #define  LSB1W(u32)     MSB2W(u32)           //!< Least significant byte of 2nd rank of \a u32.
 #define  LSB0W(u32)     MSB3W(u32)           //!< Least significant byte of 1st rank of \a u32.

 #define  MSW(u64)       (((U32 *)&(u64))[0]) //!< Most significant word of \a u64.
 #define  LSW(u64)       (((U32 *)&(u64))[1]) //!< Least significant word of \a u64.
 #define  MSH0(u64)      (((U16 *)&(u64))[0]) //!< Most significant half-word of 1st rank of \a u64.
 #define  MSH1(u64)      (((U16 *)&(u64))[1]) //!< Most significant half-word of 2nd rank of \a u64.
 #define  MSH2(u64)      (((U16 *)&(u64))[2]) //!< Most significant half-word of 3rd rank of \a u64.
 #define  MSH3(u64)      (((U16 *)&(u64))[3]) //!< Most significant half-word of 4th rank of \a u64.
 #define  LSH3(u64)      MSH0(u64)            //!< Least significant half-word of 4th rank of \a u64.
 #define  LSH2(u64)      MSH1(u64)            //!< Least significant half-word of 3rd rank of \a u64.
 #define  LSH1(u64)      MSH2(u64)            //!< Least significant half-word of 2nd rank of \a u64.
 #define  LSH0(u64)      MSH3(u64)            //!< Least significant half-word of 1st rank of \a u64.
 #define  MSB0D(u64)     (((U8  *)&(u64))[0]) //!< Most significant byte of 1st rank of \a u64.
 #define  MSB1D(u64)     (((U8  *)&(u64))[1]) //!< Most significant byte of 2nd rank of \a u64.
 #define  MSB2D(u64)     (((U8  *)&(u64))[2]) //!< Most significant byte of 3rd rank of \a u64.
 #define  MSB3D(u64)     (((U8  *)&(u64))[3]) //!< Most significant byte of 4th rank of \a u64.
 #define  MSB4D(u64)     (((U8  *)&(u64))[4]) //!< Most significant byte of 5th rank of \a u64.
 #define  MSB5D(u64)     (((U8  *)&(u64))[5]) //!< Most significant byte of 6th rank of \a u64.
 #define  MSB6D(u64)     (((U8  *)&(u64))[6]) //!< Most significant byte of 7th rank of \a u64.
 #define  MSB7D(u64)     (((U8  *)&(u64))[7]) //!< Most significant byte of 8th rank of \a u64.
 #define  LSB7D(u64)     MSB0D(u64)           //!< Least significant byte of 8th rank of \a u64.
 #define  LSB6D(u64)     MSB1D(u64)           //!< Least significant byte of 7th rank of \a u64.
 #define  LSB5D(u64)     MSB2D(u64)           //!< Least significant byte of 6th rank of \a u64.
 #define  LSB4D(u64)     MSB3D(u64)           //!< Least significant byte of 5th rank of \a u64.
 #define  LSB3D(u64)     MSB4D(u64)           //!< Least significant byte of 4th rank of \a u64.
 #define  LSB2D(u64)     MSB5D(u64)           //!< Least significant byte of 3rd rank of \a u64.
 #define  LSB1D(u64)     MSB6D(u64)           //!< Least significant byte of 2nd rank of \a u64.
 #define  LSB0D(u64)     MSB7D(u64)           //!< Least significant byte of 1st rank of \a u64.

 #define  LE16(x)        Swap16(x)
 #define  le16_to_cpu(x) swap16(x)
 #define  cpu_to_le16(x) swap16(x)
 #define  LE16_TO_CPU(x) Swap16(x)
 #define  CPU_TO_LE16(x) Swap16(x)

 #define  be16_to_cpu(x) (x)
 #define  cpu_to_be16(x) (x)
 #define  BE16_TO_CPU(x) (x)
 #define  CPU_TO_BE16(x) (x)

 #define  le32_to_cpu(x) swap32(x)
 #define  cpu_to_le32(x) swap32(x)
 #define  LE32_TO_CPU(x) Swap32(x)
 #define  CPU_TO_LE32(x) Swap32(x)

 #define  be32_to_cpu(x) (x)
 #define  cpu_to_be32(x) (x)
 #define  BE32_TO_CPU(x) (x)
 #define  CPU_TO_BE32(x) (x)





 #define Swap16(u16) ((U16)(((U16)(u16) >> 8) |\
                            ((U16)(u16) << 8)))

 #define Swap32(u32) ((U32)(((U32)Swap16((U32)(u32) >> 16)) |\
                            ((U32)Swap16((U32)(u32)) << 16)))

 #define Swap64(u64) ((U64)(((U64)Swap32((U64)(u64) >> 32)) |\
                            ((U64)Swap32((U64)(u64)) << 32)))

 #if (defined __GNUC__)
 #  if (!defined __OPTIMIZE_SIZE__) || !__OPTIMIZE_SIZE__
   #define swap16(u16) ((U16)__builtin_bswap_16((U16)(u16)))
 #  else
   // swap_16 must be not used when GCC's -Os command option is used
   #define swap16(u16) Swap16(u16)
 #  endif
 #elif (defined __ICCAVR32__)
   #define swap16(u16) ((U16)__swap_bytes_in_halfwords((U16)(u16)))
 #endif

 #if (defined __GNUC__)
   #define swap32(u32) ((U32)__builtin_bswap_32((U32)(u32)))
 #elif (defined __ICCAVR32__)
   #define swap32(u32) ((U32)__swap_bytes((U32)(u32)))
 #endif

 #define swap64(u64) ((U64)(((U64)swap32((U64)(u64) >> 32)) |\
                            ((U64)swap32((U64)(u64)) << 32)))





 #define _GLOBEXT_           extern      //!< extern storage-class specifier.
 #define _CONST_TYPE_        const       //!< const type qualifier.
 #define _MEM_TYPE_SLOW_                 //!< Slow memory type.
 #define _MEM_TYPE_MEDFAST_              //!< Fairly fast memory type.
 #define _MEM_TYPE_FAST_                 //!< Fast memory type.

 typedef U8                  Byte;      

 #define memcmp_ram2ram      memcmp      //!< Target-specific memcmp of RAM to RAM.
 #define memcmp_code2ram     memcmp      //!< Target-specific memcmp of RAM to NVRAM.
 #define memcpy_ram2ram      memcpy      //!< Target-specific memcpy from RAM to RAM.
 #define memcpy_code2ram     memcpy      //!< Target-specific memcpy from NVRAM to RAM.

 #define LSB0(u32)           LSB0W(u32)  //!< Least significant byte of 1st rank of \a u32.
 #define LSB1(u32)           LSB1W(u32)  //!< Least significant byte of 2nd rank of \a u32.
 #define LSB2(u32)           LSB2W(u32)  //!< Least significant byte of 3rd rank of \a u32.
 #define LSB3(u32)           LSB3W(u32)  //!< Least significant byte of 4th rank of \a u32.
 #define MSB3(u32)           MSB3W(u32)  //!< Most significant byte of 4th rank of \a u32.
 #define MSB2(u32)           MSB2W(u32)  //!< Most significant byte of 3rd rank of \a u32.
 #define MSB1(u32)           MSB1W(u32)  //!< Most significant byte of 2nd rank of \a u32.
 #define MSB0(u32)           MSB0W(u32)  //!< Most significant byte of 1st rank of \a u32.


 #define div_ceil(a, b)  (((a) + (b) - 1) / (b))

 #endif  // __AVR32_ABI_COMPILER__

 #endif  // _COMPILER_AVR32_H_

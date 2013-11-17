
 #ifndef _UC3D_DEFINES_FIX_
 #define _UC3D_DEFINES_FIX_

 #if (UC3D)

 //  These defines are missing from or wrong in the toolchain header file ip_xxx.h or part.h
 #ifndef AVR32_SCIF_GC_NO_DIV_CLOCK
 #define AVR32_SCIF_GC_NO_DIV_CLOCK           0
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif // end AVR32_SCIF_GC_NO_DIV_CLOCK

 #ifndef AVR32_SCIF_GCLK_ADCIFD
 #define AVR32_SCIF_GCLK_ADCIFD               8
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif // end AVR32_SCIF_GCLK_ADCIFD

 #ifndef AVR32_SCIF_GCLK_AST
 #define AVR32_SCIF_GCLK_AST                  6
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif // end AVR32_SCIF_GCLK_AST

 #ifndef AVR32_SCIF_GCLK_GLOC
 #define AVR32_SCIF_GCLK_GLOC                 0
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif // end AVR32_SCIF_GCLK_GLOC

 #ifndef AVR32_SCIF_GCLK_IISC
 #define AVR32_SCIF_GCLK_IISC                 5
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif // end AVR32_SCIF_GCLK_IISC

 #ifndef AVR32_SCIF_GCLK_PWMA
 #define AVR32_SCIF_GCLK_PWMA                 4
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif // end AVR32_SCIF_GCLK_PWMA

 #ifndef AVR32_SCIF_GCLK_USBC
 #define AVR32_SCIF_GCLK_USBC                 3
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif // end AVR32_SCIF_GCLK_USBC

 #ifndef AVR32_PM_CPU_MAX_FREQ
 #define AVR32_PM_CPU_MAX_FREQ              48000000
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif // AVR32_PM_CPU_MAX_FREQ

 #ifndef AVR32_PM_HSB_MAX_FREQ
 #define AVR32_PM_HSB_MAX_FREQ              48000000
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif // AVR32_PM_HSB_MAX_FREQ

 #ifndef AVR32_PM_PBA_MAX_FREQ
 #define AVR32_PM_PBA_MAX_FREQ              48000000
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif // AVR32_PM_PBA_MAX_FREQ

 #ifndef AVR32_PM_PBB_MAX_FREQ
 #define AVR32_PM_PBB_MAX_FREQ              48000000
 #else
 #warning "Duplicate define(s) to remove from the ASF"
 #endif  // AVR32_PM_PBB_MAX_FREQ

 #endif // end UC3D

 #endif  // _UC3D_DEFINES_FIX

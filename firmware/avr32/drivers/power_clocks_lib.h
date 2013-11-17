 /*****************************************************************************
  *
  * \file
  *
  * \brief High-level library abstracting features such as oscillators/pll/dfll
  *        configuration, clock configuration, System-sensible parameters
  *        configuration, buses clocks configuration, sleep mode, reset.
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
  *****************************************************************************/


 #ifndef _POWER_CLOCKS_LIB_H_
 #define _POWER_CLOCKS_LIB_H_

 #ifdef __cplusplus
 extern "C" {
 #endif

 #include <avr32/io.h>
 #include "compiler.h"

 #ifndef AVR32_PM_VERSION_RESETVALUE
 // Support for UC3A, UC3A3, UC3B parts.
   #include "pm.h"
 #else

 #if UC3L
   #include "pm_uc3l.h"
   #include "scif_uc3l.h"
   #include "flashcdw.h"
 #elif UC3C
   #include "pm_uc3c.h"
   #include "scif_uc3c.h"
   #include "flashc.h"
 #elif UC3D
   #include "pm_uc3d.h"
   #include "scif_uc3d.h"
   #include "flashcdw.h"
 #endif
   #endif



 typedef enum
 {
   PCL_OSC0  = 0,
   PCL_OSC1  = 1
 } pcl_osc_t;

 typedef enum
 {
   PCL_DFLL0  = 0,
   PCL_DFLL1  = 1
 } pcl_dfll_t;

 typedef enum
 {
   PCL_MC_RCSYS,      // Default main clock source, supported by all (aka Slow Clock)
   PCL_MC_OSC0,       // Supported by all
   PCL_MC_OSC1,       // Supported by UC3C only
   PCL_MC_OSC0_PLL0,  // Supported by UC3A, UC3B, UC3A3, UC3C (the main clock source is PLL0 with OSC0 as reference)
   PCL_MC_OSC1_PLL0,  // Supported by UC3A, UC3B, UC3A3, UC3C (the main clock source is PLL0 with OSC1 as reference)
   PCL_MC_OSC0_PLL1,  // Supported by UC3C  (the main clock source is PLL1 with OSC0 as reference)
   PCL_MC_OSC1_PLL1,  // Supported by UC3C  (the main clock source is PLL1 with OSC1 as reference)
   PCL_MC_DFLL0,      // Supported by UC3L
   PCL_MC_DFLL1,      // Not supported yet
   PCL_MC_RC120M,     // Supported by UC3L, UC3C
   PCL_MC_RC8M,       // Supported by UC3C
   PCL_MC_CRIPOSC     // Supported by UC3C
 } pcl_mainclk_t;

 // NOTE: regarding the frequency settings, always abide by the datasheet rules and min & max supported frequencies.
 #ifndef AVR32_PM_VERSION_RESETVALUE
 // Support for UC3A, UC3A3, UC3B parts.
 #define pcl_freq_param_t  pm_freq_param_t // See pm.h
 #else
 // Support for UC3C, UC3L parts.
 typedef struct
 {
   pcl_mainclk_t main_clk_src;

   unsigned long cpu_f;

   unsigned long pba_f;

   unsigned long pbb_f;

   unsigned long pbc_f;

   unsigned long osc0_f;

   unsigned long osc0_startup;

   unsigned long dfll_f;

   // For the UC3L DFLL setup, this parameter should be pointing to a structure of
   // type (scif_gclk_opt_t *).
   void *pextra_params;
 } pcl_freq_param_t;
 #endif

 #define PCL_NOT_SUPPORTED (-10000)

 extern long int pcl_configure_clocks(pcl_freq_param_t *param);

 extern long int pcl_configure_clocks_rcsys(pcl_freq_param_t *param);

 extern long int pcl_configure_clocks_rc120m(pcl_freq_param_t *param);

 extern long int pcl_configure_clocks_osc0(pcl_freq_param_t *param);

 extern long int pcl_configure_clocks_dfll0(pcl_freq_param_t *param);

 extern long int pcl_switch_to_osc(pcl_osc_t osc, unsigned int fcrystal, unsigned int startup);

 #ifndef AVR32_PM_VERSION_RESETVALUE
 // Implementation for UC3A, UC3A3, UC3B parts.
 #define pcl_enable_module(module) pm_enable_module(&AVR32_PM, module)
 #else
 // Implementation for UC3C, UC3L parts.
 #define pcl_enable_module(module) pm_enable_module(module)
 #endif

 #ifndef AVR32_PM_VERSION_RESETVALUE
 // Implementation for UC3A, UC3A3, UC3B parts.
 #define pcl_disable_module(module)  pm_disable_module(&AVR32_PM, module)
 #else
 // Implementation for UC3C, UC3L parts.
 #define pcl_disable_module(module)  pm_disable_module(module)
 #endif

 extern long int pcl_configure_usb_clock(void);




 extern unsigned long pcl_read_gplp(unsigned long gplp);


 extern void pcl_write_gplp(unsigned long gplp, unsigned long value);


 #ifdef __cplusplus
 }
 #endif

 #endif  // _POWER_CLOCKS_LIB_H_

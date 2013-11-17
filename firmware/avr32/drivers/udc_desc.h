
 #ifndef _UDC_DESC_H_
 #define _UDC_DESC_H_

 #include "conf_usb.h"
 #include "usb_protocol.h"
 #include "udi.h"

 #ifdef __cplusplus
 extern "C" {
 #endif

 #define  UDC_DESC_STORAGE
     // Descriptor storage in internal RAM
 #if (defined UDC_DATA_USE_HRAM_SUPPORT)
 #   if defined(__GNUC__)
 #       define UDC_DATA(x)              COMPILER_WORD_ALIGNED __attribute__((__section__(".data_hram0")))
 #       define UDC_BSS(x)               COMPILER_ALIGNED(x)   __attribute__((__section__(".bss_hram0")))
 #   elif defined(__ICCAVR32__)
 #       define UDC_DATA(x)              COMPILER_ALIGNED(x)   __data32
 #       define UDC_BSS(x)               COMPILER_ALIGNED(x)   __data32
 #   endif
 #else
 #   define UDC_DATA(x)              COMPILER_ALIGNED(x)
 #   define UDC_BSS(x)               COMPILER_ALIGNED(x)
 #endif



 typedef struct {
     usb_conf_desc_t UDC_DESC_STORAGE *desc;
     udi_api_t UDC_DESC_STORAGE *UDC_DESC_STORAGE * udi_apis;
 } udc_config_speed_t;


 typedef struct {
     usb_dev_desc_t UDC_DESC_STORAGE *confdev_lsfs;
     udc_config_speed_t UDC_DESC_STORAGE *conf_lsfs;
 #ifdef USB_DEVICE_HS_SUPPORT

     usb_dev_desc_t UDC_DESC_STORAGE *confdev_hs;
     usb_dev_qual_desc_t UDC_DESC_STORAGE *qualifier;
     udc_config_speed_t UDC_DESC_STORAGE *conf_hs;
 #endif
 } udc_config_t;

 extern UDC_DESC_STORAGE udc_config_t udc_config;


 #ifdef __cplusplus
 }
 #endif
 #endif // _UDC_DESC_H_

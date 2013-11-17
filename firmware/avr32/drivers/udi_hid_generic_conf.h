
 #ifndef _UDI_HID_GENERIC_CONF_H_
 #define _UDI_HID_GENERIC_CONF_H_

 #ifdef __cplusplus
 extern "C" {
 #endif


 #ifdef USB_DEVICE_HS_SUPPORT
 #  define  USB_DEVICE_EP_CTRL_SIZE       64
 #else
 #  define  USB_DEVICE_EP_CTRL_SIZE       64
 #endif

 #define  UDI_HID_GENERIC_EP_OUT   (2 | USB_EP_DIR_OUT)
 #define  UDI_HID_GENERIC_EP_IN    (1 | USB_EP_DIR_IN)

 #define  UDI_HID_GENERIC_IFACE_NUMBER     0



 #define  USB_DEVICE_MAX_EP    2



 #ifdef __cplusplus
 }
 #endif

 #include "udi_hid_generic.h"

 #endif // _UDI_HID_GENERIC_CONF_H_

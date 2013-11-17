
 #ifndef _CONF_USB_H_
 #define _CONF_USB_H_

 #include "compiler.h"


 #define  USB_DEVICE_VENDOR_ID             USB_VID_ATMEL
 #define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_AVR_HIDGENERIC
 #define  USB_DEVICE_MAJOR_VERSION         1
 #define  USB_DEVICE_MINOR_VERSION         0
 #define  USB_DEVICE_POWER                 100 // Consumption on Vbus line (mA)
 #define  USB_DEVICE_ATTR                  \
   (USB_CONFIG_ATTR_BUS_POWERED)
//   (USB_CONFIG_ATTR_SELF_POWERED)
 //    (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED)
//   (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_SELF_POWERED)
 //  (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED)

 #define  USB_DEVICE_MANUFACTURE_NAME      "mobilECG"
 #define  USB_DEVICE_PRODUCT_NAME          "12-lead cable"
 // #define  USB_DEVICE_SERIAL_NAME           "12...EF"


 //#define  USB_DEVICE_LOW_SPEED

 #if (UC3A3||UC3A4)
 //#define  USB_DEVICE_HS_SUPPORT
 #endif


 #define  UDC_VBUS_EVENT(b_vbus_high)      main_vbus_action(b_vbus_high)
 #define  UDC_SOF_EVENT()                  main_sof_action()
 #define  UDC_SUSPEND_EVENT()              main_suspend_action()
 #define  UDC_RESUME_EVENT()               main_resume_action()

 #define  UDC_REMOTEWAKEUP_ENABLE()        main_remotewakeup_enable()
 #define  UDC_REMOTEWAKEUP_DISABLE()       main_remotewakeup_disable()


 // #define  UDC_GET_EXTRA_STRING()




 #define  UDI_HID_GENERIC_ENABLE_EXT()        main_generic_enable()
 #define  UDI_HID_GENERIC_DISABLE_EXT()       main_generic_disable()
 #define  UDI_HID_GENERIC_REPORT_OUT(ptr)     usb_receive_packet(ptr)
 #define  UDI_HID_GENERIC_SET_FEATURE(report) main_hid_set_feature(report)

 #define  UDI_HID_REPORT_IN_SIZE             64
 #define  UDI_HID_REPORT_OUT_SIZE            64
 #define  UDI_HID_REPORT_FEATURE_SIZE        4

 #define  UDI_HID_GENERIC_EP_SIZE            64





 #include "udi_hid_generic_conf.h"
 #include "usb_callbacks.h"

 #endif // _CONF_USB_H_

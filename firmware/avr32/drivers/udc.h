
 #ifndef _UDC_H_
 #define _UDC_H_

 #include "conf_usb.h"
 #include "usb_protocol.h"
 #include "udc_desc.h"
 #include "udd.h"

 #ifdef __cplusplus
 extern "C" {
 #endif

 static inline bool udc_include_vbus_monitoring(void)
 {
     return udd_include_vbus_monitoring();
 }

 void udc_start(void);

 void udc_stop(void);

 static inline void udc_attach(void)
 {
     udd_attach();
 }


 static inline void udc_detach(void)
 {
     udd_detach();
 }


 static inline void udc_wakeup(void)
 {
     udd_send_wake_up();
 }


 usb_iface_desc_t UDC_DESC_STORAGE *udc_get_interface_desc(void);




 #ifdef __cplusplus
 }
 #endif
 #endif // _UDC_H_

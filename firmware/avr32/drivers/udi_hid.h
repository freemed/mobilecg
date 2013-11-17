
 #ifndef _UDI_HID_H_
 #define _UDI_HID_H_

 #include "conf_usb.h"
 #include "usb_protocol.h"
 #include "usb_protocol_hid.h"
 #include "udd.h"

 #ifdef __cplusplus
 extern "C" {
 #endif


 bool udi_hid_setup( uint8_t *rate, uint8_t *protocol, uint8_t *report_desc, bool (*set_report)(void) );



 #ifdef __cplusplus
 }
 #endif
 #endif // _UDI_HID_H_

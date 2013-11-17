
 #ifndef _UDI_H_
 #define _UDI_H_

 #include "conf_usb.h"
 #include "usb_protocol.h"

 #ifdef __cplusplus
 extern "C" {
 #endif

 typedef struct {
     bool(*enable) (void);

     void (*disable) (void);

     bool(*setup) (void);

     uint8_t(*getsetting) (void);

     void(*sof_notify) (void);
 } udi_api_t;


 #ifdef __cplusplus
 }
 #endif
 #endif // _UDI_H_

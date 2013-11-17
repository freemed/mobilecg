
 #include "conf_usb.h"
 #include "usb_protocol.h"
 #include "udd.h"
 #include "udc.h"
 #include "udi_hid.h"



 static bool udi_hid_reqstdifaceget_descriptor(uint8_t *report_desc);


 bool udi_hid_setup( uint8_t *rate, uint8_t *protocol, uint8_t *report_desc, bool (*set_report)(void) )
 {
     if (Udd_setup_is_in()) {
         // Requests Interface GET
         if (Udd_setup_type() == USB_REQ_TYPE_STANDARD) {
             // Requests Standard Interface Get
             switch (udd_g_ctrlreq.req.bRequest) {

             case USB_REQ_GET_DESCRIPTOR:
                 return udi_hid_reqstdifaceget_descriptor(report_desc);
             }
         }
         if (Udd_setup_type() == USB_REQ_TYPE_CLASS) {
             // Requests Class Interface Get
             switch (udd_g_ctrlreq.req.bRequest) {

             case USB_REQ_HID_GET_REPORT:
                 // TODO
                 break;

             case USB_REQ_HID_GET_IDLE:
                 udd_g_ctrlreq.payload = rate;
                 udd_g_ctrlreq.payload_size = 1;
                 return true;

             case USB_REQ_HID_GET_PROTOCOL:
                 udd_g_ctrlreq.payload = protocol;
                 udd_g_ctrlreq.payload_size = 1;
                 return true;
             }
         }
     }
     if (Udd_setup_is_out()) {
         // Requests Interface SET
         if (Udd_setup_type() == USB_REQ_TYPE_CLASS) {
             // Requests Class Interface Set
             switch (udd_g_ctrlreq.req.bRequest) {

             case USB_REQ_HID_SET_REPORT:
                 return set_report();

             case USB_REQ_HID_SET_IDLE:
                 *rate = udd_g_ctrlreq.req.wValue >> 8;
                 return true;

             case USB_REQ_HID_SET_PROTOCOL:
                 if (0 != udd_g_ctrlreq.req.wLength)
                     return false;
                 *protocol = udd_g_ctrlreq.req.wValue;
                 return true;
             }
         }
     }
     return false;   // Request not supported
 }


 //---------------------------------------------
 //------- Internal routines

 static bool udi_hid_reqstdifaceget_descriptor(uint8_t *report_desc)
 {
     usb_hid_descriptor_t UDC_DESC_STORAGE *ptr_hid_desc;

     // Get the USB descriptor which is located after the interface descriptor
     // This descriptor must be the HID descriptor
     ptr_hid_desc = (usb_hid_descriptor_t UDC_DESC_STORAGE *) ((uint8_t *)
             udc_get_interface_desc() + sizeof(usb_iface_desc_t));
     if (USB_DT_HID != ptr_hid_desc->bDescriptorType)
         return false;

     // The SETUP request can ask for:
     // - an USB_DT_HID descriptor
     // - or USB_DT_HID_REPORT descriptor
     // - or USB_DT_HID_PHYSICAL descriptor
     if (USB_DT_HID == (uint8_t) (udd_g_ctrlreq.req.wValue >> 8)) {
         // USB_DT_HID descriptor requested then send it
         udd_g_ctrlreq.payload = (uint8_t *) ptr_hid_desc;
         udd_g_ctrlreq.payload_size =
                 min(udd_g_ctrlreq.req.wLength,
                 ptr_hid_desc->bLength);
         return true;
     }
     // The HID_X descriptor requested must correspond to report type
     // included in the HID descriptor
     if (ptr_hid_desc->bRDescriptorType ==
             (uint8_t) (udd_g_ctrlreq.req.wValue >> 8)) {
         // Send HID Report descriptor given by high level
         udd_g_ctrlreq.payload = report_desc;
         udd_g_ctrlreq.payload_size =
                 min(udd_g_ctrlreq.req.wLength,
                 le16_to_cpu(ptr_hid_desc->wDescriptorLength));
         return true;
     }
     return false;
 }

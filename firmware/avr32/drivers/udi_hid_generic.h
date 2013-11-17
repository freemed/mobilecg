
 #ifndef _UDI_HID_GENERIC_H_
 #define _UDI_HID_GENERIC_H_

 #include "conf_usb.h"
 #include "usb_protocol.h"
 #include "usb_protocol_hid.h"
 #include "udc_desc.h"
 #include "udi.h"

 #ifdef __cplusplus
 extern "C" {
 #endif


 extern UDC_DESC_STORAGE udi_api_t udi_api_hid_generic;

 typedef struct {
     usb_iface_desc_t iface;
     usb_hid_descriptor_t hid;
     usb_ep_desc_t ep_in;
     usb_ep_desc_t ep_out;
 } udi_hid_generic_desc_t;

 typedef struct {
     uint8_t array[53];
 } udi_hid_generic_report_desc_t;


 #ifndef UDI_HID_GENERIC_STRING_ID
 #define UDI_HID_GENERIC_STRING_ID 0
 #endif



 #define UDI_HID_GENERIC_DESC    {\
    .iface.bLength             = sizeof(usb_iface_desc_t),\
    .iface.bDescriptorType     = USB_DT_INTERFACE,\
    .iface.bInterfaceNumber    = UDI_HID_GENERIC_IFACE_NUMBER,\
    .iface.bAlternateSetting   = 0,\
    .iface.bNumEndpoints       = 2,\
    .iface.bInterfaceClass     = HID_CLASS,\
    .iface.bInterfaceSubClass  = HID_SUB_CLASS_NOBOOT,\
    .iface.bInterfaceProtocol  = HID_PROTOCOL_GENERIC,\
    .iface.iInterface          = UDI_HID_GENERIC_STRING_ID,\
    .hid.bLength               = sizeof(usb_hid_descriptor_t),\
    .hid.bDescriptorType       = USB_DT_HID,\
    .hid.bcdHID                = LE16(USB_HID_BDC_V1_11),\
    .hid.bCountryCode          = USB_HID_NO_COUNTRY_CODE,\
    .hid.bNumDescriptors       = USB_HID_NUM_DESC,\
    .hid.bRDescriptorType      = USB_DT_HID_REPORT,\
    .hid.wDescriptorLength     = LE16(sizeof(udi_hid_generic_report_desc_t)),\
    .ep_in.bLength             = sizeof(usb_ep_desc_t),\
    .ep_in.bDescriptorType     = USB_DT_ENDPOINT,\
    .ep_in.bEndpointAddress    = UDI_HID_GENERIC_EP_IN,\
    .ep_in.bmAttributes        = USB_EP_TYPE_INTERRUPT,\
    .ep_in.wMaxPacketSize      = LE16(UDI_HID_GENERIC_EP_SIZE),\
    .ep_in.bInterval           = 1,\
    .ep_out.bLength            = sizeof(usb_ep_desc_t),\
    .ep_out.bDescriptorType    = USB_DT_ENDPOINT,\
    .ep_out.bEndpointAddress   = UDI_HID_GENERIC_EP_OUT,\
    .ep_out.bmAttributes       = USB_EP_TYPE_INTERRUPT,\
    .ep_out.wMaxPacketSize     = LE16(UDI_HID_GENERIC_EP_SIZE),\
    .ep_out.bInterval          = 1,\
    }



 bool udi_hid_generic_send_report_in(uint8_t *data);
char* udi_hid_generic_get_buffer_in();
void udi_hid_generic_send_buffer_in();
void UDI_HID_GENERIC_REPORT_OUT(uint8_t *data);

 #ifdef __cplusplus
 }
 #endif
 #endif // _UDI_HID_GENERIC_H_

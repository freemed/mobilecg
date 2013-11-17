
 #include "conf_usb.h"
 #include "udd.h"
 #include "udc_desc.h"
 #include "udi_hid.h"
 #include "udi_hid_generic.h"


 #define  USB_DEVICE_NB_INTERFACE       1


 COMPILER_WORD_ALIGNED
 UDC_DESC_STORAGE usb_dev_desc_t udc_device_desc = {
     .bLength                   = sizeof(usb_dev_desc_t),
     .bDescriptorType           = USB_DT_DEVICE,
     .bcdUSB                    = LE16(USB_V2_0),
     .bDeviceClass              = 0,
     .bDeviceSubClass           = 0,
     .bDeviceProtocol           = 0,
     .bMaxPacketSize0           = USB_DEVICE_EP_CTRL_SIZE,
     .idVendor                  = LE16(USB_DEVICE_VENDOR_ID),
     .idProduct                 = LE16(USB_DEVICE_PRODUCT_ID),
     .bcdDevice                 = LE16((USB_DEVICE_MAJOR_VERSION << 8)
         | USB_DEVICE_MINOR_VERSION),
 #ifdef USB_DEVICE_MANUFACTURE_NAME
     .iManufacturer = 1,
 #else
     .iManufacturer = 0, // No manufacture string
 #endif
 #ifdef USB_DEVICE_PRODUCT_NAME
     .iProduct = 2,
 #else
     .iProduct = 0,  // No product string
 #endif
 #ifdef USB_DEVICE_SERIAL_NAME
     .iSerialNumber = 3,
 #else
     .iSerialNumber = 0, // No serial string
 #endif
     .bNumConfigurations        = 1
 };


 #ifdef USB_DEVICE_HS_SUPPORT

 COMPILER_WORD_ALIGNED
 UDC_DESC_STORAGE usb_dev_qual_desc_t udc_device_qual = {
     .bLength                   = sizeof(usb_dev_qual_desc_t),
     .bDescriptorType           = USB_DT_DEVICE_QUALIFIER,
     .bcdUSB                    = LE16(USB_V2_0),
     .bDeviceClass              = 0,
     .bDeviceSubClass           = 0,
     .bDeviceProtocol           = 0,
     .bMaxPacketSize0           = USB_DEVICE_EP_CTRL_SIZE,
     .bNumConfigurations        = 1
 };
 #endif

 COMPILER_PACK_SET(1);
 typedef struct {
     usb_conf_desc_t conf;
     udi_hid_generic_desc_t hid_generic;
 } udc_desc_t;
 COMPILER_PACK_RESET();

 COMPILER_WORD_ALIGNED
 UDC_DESC_STORAGE udc_desc_t udc_desc = {
     .conf.bLength              = sizeof(usb_conf_desc_t),
     .conf.bDescriptorType      = USB_DT_CONFIGURATION,
     .conf.wTotalLength         = LE16(sizeof(udc_desc_t)),
     .conf.bNumInterfaces       = USB_DEVICE_NB_INTERFACE,
     .conf.bConfigurationValue  = 1,
     .conf.iConfiguration       = 0,
     .conf.bmAttributes         = USB_CONFIG_ATTR_MUST_SET | USB_DEVICE_ATTR,
     .conf.bMaxPower            = USB_CONFIG_MAX_POWER(USB_DEVICE_POWER),
     .hid_generic               = UDI_HID_GENERIC_DESC,
 };



 UDC_DESC_STORAGE udi_api_t *udi_apis[USB_DEVICE_NB_INTERFACE] = {
     &udi_api_hid_generic,
 };

 UDC_DESC_STORAGE udc_config_speed_t udc_config_fshs[1] = { {
     .desc          = (usb_conf_desc_t UDC_DESC_STORAGE*)&udc_desc,
     .udi_apis = udi_apis,
 }};

 UDC_DESC_STORAGE udc_config_t udc_config = {
     .confdev_lsfs = &udc_device_desc,
     .conf_lsfs = udc_config_fshs,
 #ifdef USB_DEVICE_HS_SUPPORT
     .confdev_hs = &udc_device_desc,
     .qualifier = &udc_device_qual,
     .conf_hs = udc_config_fshs,
 #endif
 };

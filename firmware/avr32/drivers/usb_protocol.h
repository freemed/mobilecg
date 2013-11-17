
 #ifndef _USB_PROTOCOL_H_
 #define _USB_PROTOCOL_H_

 #include "usb_atmel.h"


 #define  USB_V2_0    0x0200 //!< USB Specification version 2.00


 #define  NO_CLASS                0x00
 #define  CLASS_VENDOR_SPECIFIC   0xFF
 #define  NO_SUBCLASS             0x00
 #define  NO_PROTOCOL             0x00


 #define  CLASS_IAD               0xEF
 #define  SUB_CLASS_IAD           0x02
 #define  PROTOCOL_IAD            0x01


 #define  USB_REQ_DIR_OUT         (0<<7) //!< Host to device
 #define  USB_REQ_DIR_IN          (1<<7) //!< Device to host
 #define  USB_REQ_DIR_MASK        (1<<7) //!< Mask

 #define  USB_REQ_TYPE_STANDARD   (0<<5) //!< Standard request
 #define  USB_REQ_TYPE_CLASS      (1<<5) //!< Class-specific request
 #define  USB_REQ_TYPE_VENDOR     (2<<5) //!< Vendor-specific request
 #define  USB_REQ_TYPE_MASK       (3<<5) //!< Mask

 #define  USB_REQ_RECIP_DEVICE    (0<<0) //!< Recipient device
 #define  USB_REQ_RECIP_INTERFACE (1<<0) //!< Recipient interface
 #define  USB_REQ_RECIP_ENDPOINT  (2<<0) //!< Recipient endpoint
 #define  USB_REQ_RECIP_OTHER     (3<<0) //!< Recipient other
 #define  USB_REQ_RECIP_MASK      (0x1F) //!< Mask

 enum usb_reqid {
     USB_REQ_GET_STATUS = 0,
     USB_REQ_CLEAR_FEATURE = 1,
     USB_REQ_SET_FEATURE = 3,
     USB_REQ_SET_ADDRESS = 5,
     USB_REQ_GET_DESCRIPTOR = 6,
     USB_REQ_SET_DESCRIPTOR = 7,
     USB_REQ_GET_CONFIGURATION = 8,
     USB_REQ_SET_CONFIGURATION = 9,
     USB_REQ_GET_INTERFACE = 10,
     USB_REQ_SET_INTERFACE = 11,
     USB_REQ_SYNCH_FRAME = 12,
 };

 enum usb_device_status {
     USB_DEV_STATUS_BUS_POWERED = 0,
     USB_DEV_STATUS_SELF_POWERED = 1,
     USB_DEV_STATUS_REMOTEWAKEUP = 2
 };

 enum usb_interface_status {
     USB_IFACE_STATUS_RESERVED = 0
 };

 enum usb_endpoint_status {
     USB_EP_STATUS_HALTED = 1,
 };

 enum usb_device_feature {
     USB_DEV_FEATURE_REMOTE_WAKEUP = 1,
     USB_DEV_FEATURE_TEST_MODE = 2,    
     USB_DEV_FEATURE_OTG_B_HNP_ENABLE = 3,
     USB_DEV_FEATURE_OTG_A_HNP_SUPPORT = 4,
     USB_DEV_FEATURE_OTG_A_ALT_HNP_SUPPORT = 5
 };

 enum usb_device_hs_test_mode {
     USB_DEV_TEST_MODE_J = 1,
     USB_DEV_TEST_MODE_K = 2,
     USB_DEV_TEST_MODE_SE0_NAK = 3,
     USB_DEV_TEST_MODE_PACKET = 4,
     USB_DEV_TEST_MODE_FORCE_ENABLE = 5,
 };

 enum usb_endpoint_feature {
     USB_EP_FEATURE_HALT = 0,
 };

 enum usb_test_mode_selector {
     USB_TEST_J = 0x01,
     USB_TEST_K = 0x02,
     USB_TEST_SE0_NAK = 0x03,
     USB_TEST_PACKET = 0x04,
     USB_TEST_FORCE_ENABLE = 0x05,
 };

 enum usb_descriptor_type {
     USB_DT_DEVICE = 1,
     USB_DT_CONFIGURATION = 2,
     USB_DT_STRING = 3,
     USB_DT_INTERFACE = 4,
     USB_DT_ENDPOINT = 5,
     USB_DT_DEVICE_QUALIFIER = 6,
     USB_DT_OTHER_SPEED_CONFIGURATION = 7,
     USB_DT_INTERFACE_POWER = 8,
     USB_DT_OTG = 9,
     USB_DT_IAD = 0x0B,
 };

 enum usb_ep_type {
     USB_EP_TYPE_CONTROL = 0x00,
     USB_EP_TYPE_ISOCHRONOUS = 0x01,
     USB_EP_TYPE_BULK = 0x02,
     USB_EP_TYPE_INTERRUPT = 0x03,
     USB_EP_TYPE_MASK = 0x03,
 };

 enum usb_langid {
     USB_LANGID_EN_US = 0x0409,
 };

 #define  USB_EP_ADDR_MASK     0x0f

 typedef uint8_t usb_add_t;

 #define  USB_EP_DIR_IN        0x80

 #define  USB_EP_DIR_OUT       0x00

 typedef uint8_t usb_ep_t;

 #define  USB_MAX_DESC_LEN     255

 /*
  * 2-byte alignment requested for all USB structures.
  */
 COMPILER_PACK_SET(1);

 typedef struct {
     uint8_t bmRequestType;
     uint8_t bRequest;
     le16_t wValue;
     le16_t wIndex;
     le16_t wLength;
 } usb_setup_req_t;

 typedef struct {
     uint8_t bLength;
     uint8_t bDescriptorType;
     le16_t bcdUSB;
     uint8_t bDeviceClass;
     uint8_t bDeviceSubClass;
     uint8_t bDeviceProtocol;
     uint8_t bMaxPacketSize0;
     le16_t idVendor;
     le16_t idProduct;
     le16_t bcdDevice;
     uint8_t iManufacturer;
     uint8_t iProduct;
     uint8_t iSerialNumber;
     uint8_t bNumConfigurations;
 } usb_dev_desc_t;

 typedef struct {
     uint8_t bLength;
     uint8_t bDescriptorType;
     le16_t bcdUSB;
     uint8_t bDeviceClass;
     uint8_t bDeviceSubClass;
     uint8_t bDeviceProtocol;
     uint8_t bMaxPacketSize0;
     uint8_t bNumConfigurations;
     uint8_t bReserved;
 } usb_dev_qual_desc_t;


 typedef struct {
     uint8_t bLength;         
     uint8_t bDescriptorType; 
     uint8_t bFirstInterface; 
     uint8_t bInterfaceCount; 
     uint8_t bFunctionClass;  
     uint8_t bFunctionSubClass;
     uint8_t bFunctionProtocol;
     uint8_t iFunction;       
 } usb_association_desc_t;


 typedef struct {
     uint8_t bLength;
     uint8_t bDescriptorType;
     le16_t wTotalLength;
     uint8_t bNumInterfaces;
     uint8_t bConfigurationValue;
     uint8_t iConfiguration;
     uint8_t bmAttributes;
     uint8_t bMaxPower;
 } usb_conf_desc_t;


 #define  USB_CONFIG_ATTR_MUST_SET         (1 << 7) //!< Must always be set
 #define  USB_CONFIG_ATTR_BUS_POWERED      (0 << 6) //!< Bus-powered
 #define  USB_CONFIG_ATTR_SELF_POWERED     (1 << 6) //!< Self-powered
 #define  USB_CONFIG_ATTR_REMOTE_WAKEUP    (1 << 5) //!< remote wakeup supported

 #define  USB_CONFIG_MAX_POWER(ma)         (((ma) + 1) / 2) //!< Max power in mA

 typedef struct {
     uint8_t bLength;             
     uint8_t bDescriptorType;     
     uint8_t bFirstInterface;     
     uint8_t bInterfaceCount;     
     uint8_t bFunctionClass;      
     uint8_t bFunctionSubClass;   
     uint8_t bFunctionProtocol;   
     uint8_t iFunction;           
 } usb_iad_desc_t;

 typedef struct {
     uint8_t bLength;
     uint8_t bDescriptorType;
     uint8_t bInterfaceNumber;
     uint8_t bAlternateSetting;
     uint8_t bNumEndpoints;
     uint8_t bInterfaceClass;
     uint8_t bInterfaceSubClass;
     uint8_t bInterfaceProtocol;
     uint8_t iInterface;
 } usb_iface_desc_t;

 typedef struct {
     uint8_t bLength;
     uint8_t bDescriptorType;
     uint8_t bEndpointAddress;
     uint8_t bmAttributes;
     le16_t wMaxPacketSize;
     uint8_t bInterval;
 } usb_ep_desc_t;


 typedef struct {
     uint8_t bLength;
     uint8_t bDescriptorType;
 } usb_str_desc_t;

 typedef struct {
     usb_str_desc_t desc;
     le16_t string[1];
 } usb_str_lgid_desc_t;

 COMPILER_PACK_RESET();


 #endif /* _USB_PROTOCOL_H_ */

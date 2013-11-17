
 #include "conf_usb.h"
 #include "usb_protocol.h"
 #include "udd.h"
 #include "udc_desc.h"
 #include "udi.h"
 #include "udc.h"




 static le16_t udc_device_status;

 static uint8_t udc_num_configuration = 0;

 static udc_config_speed_t UDC_DESC_STORAGE *udc_ptr_conf;

 static usb_iface_desc_t UDC_DESC_STORAGE *udc_ptr_iface;




 COMPILER_WORD_ALIGNED
 static UDC_DESC_STORAGE usb_str_lgid_desc_t udc_string_desc_languageid = {
     .desc.bLength = sizeof(usb_str_lgid_desc_t),
     .desc.bDescriptorType = USB_DT_STRING,
     .string = {LE16(USB_LANGID_EN_US)}
 };

 #ifdef USB_DEVICE_MANUFACTURE_NAME
 static uint8_t udc_string_manufacturer_name[] = USB_DEVICE_MANUFACTURE_NAME;
 #  define USB_DEVICE_MANUFACTURE_NAME_SIZE  \
     (sizeof(udc_string_manufacturer_name)-1)
 #else
 #  define USB_DEVICE_MANUFACTURE_NAME_SIZE  0
 #endif

 #ifdef USB_DEVICE_PRODUCT_NAME
 static uint8_t udc_string_product_name[] = USB_DEVICE_PRODUCT_NAME;
 #  define USB_DEVICE_PRODUCT_NAME_SIZE  (sizeof(udc_string_product_name)-1)
 #else
 #  define USB_DEVICE_PRODUCT_NAME_SIZE  0
 #endif

 #if defined USB_DEVICE_GET_SERIAL_NAME_POINTER
     static const uint8_t *udc_get_string_serial_name(void)
     {
         return (const uint8_t *)USB_DEVICE_GET_SERIAL_NAME_POINTER;
     }
 #  define USB_DEVICE_SERIAL_NAME_SIZE \
     USB_DEVICE_GET_SERIAL_NAME_LENGTH
 #elif defined USB_DEVICE_SERIAL_NAME
     static const uint8_t *udc_get_string_serial_name(void)
     {
         return (const uint8_t *)USB_DEVICE_SERIAL_NAME;
     }
 #  define USB_DEVICE_SERIAL_NAME_SIZE \
     (sizeof(USB_DEVICE_SERIAL_NAME)-1)
 #else
 #  define USB_DEVICE_SERIAL_NAME_SIZE  0
 #endif

 struct udc_string_desc_t {
     usb_str_desc_t header;
     le16_t string[Max(Max(USB_DEVICE_MANUFACTURE_NAME_SIZE, \
             USB_DEVICE_PRODUCT_NAME_SIZE), USB_DEVICE_SERIAL_NAME_SIZE)];
 };
 COMPILER_WORD_ALIGNED
 static UDC_DESC_STORAGE struct udc_string_desc_t udc_string_desc = {
     .header.bDescriptorType = USB_DT_STRING
 };

 usb_iface_desc_t UDC_DESC_STORAGE *udc_get_interface_desc(void)
 {
     return udc_ptr_iface;
 }

 static usb_conf_desc_t UDC_DESC_STORAGE *udc_get_eof_conf(void)
 {
     return (UDC_DESC_STORAGE usb_conf_desc_t *) ((uint8_t *)
             udc_ptr_conf->desc +
             le16_to_cpu(udc_ptr_conf->desc->wTotalLength));
 }

 #if (0!=USB_DEVICE_MAX_EP)

 static usb_conf_desc_t UDC_DESC_STORAGE *udc_next_desc_in_iface(usb_conf_desc_t
         UDC_DESC_STORAGE * desc, uint8_t desc_id)
 {
     usb_conf_desc_t UDC_DESC_STORAGE *ptr_eof_desc;

     ptr_eof_desc = udc_get_eof_conf();
     // Go to next descriptor
     desc = (UDC_DESC_STORAGE usb_conf_desc_t *) ((uint8_t *) desc +
             desc->bLength);
     // Check the end of configuration descriptor
     while (ptr_eof_desc > desc) {
         // If new interface descriptor is found,
         // then it is the end of the current global interface descriptor
         if (USB_DT_INTERFACE == desc->bDescriptorType) {
             break; // End of global interface descriptor
         }
         if (desc_id == desc->bDescriptorType) {
             return desc; // Specific descriptor found
         }
         // Go to next descriptor
         desc = (UDC_DESC_STORAGE usb_conf_desc_t *) ((uint8_t *) desc +
                 desc->bLength);
     }
     return NULL; // No specific descriptor found
 }
 #endif

 static bool udc_update_iface_desc(uint8_t iface_num, uint8_t setting_num)
 {
     usb_conf_desc_t UDC_DESC_STORAGE *ptr_end_desc;

     if (0 == udc_num_configuration) {
         return false;
     }

     if (iface_num >= udc_ptr_conf->desc->bNumInterfaces) {
         return false;
     }

     // Start at the beginning of configuration descriptor
     udc_ptr_iface = (UDC_DESC_STORAGE usb_iface_desc_t *)
             udc_ptr_conf->desc;

     // Check the end of configuration descriptor
     ptr_end_desc = udc_get_eof_conf();
     while (ptr_end_desc >
             (UDC_DESC_STORAGE usb_conf_desc_t *) udc_ptr_iface) {
         if (USB_DT_INTERFACE == udc_ptr_iface->bDescriptorType) {
             // A interface descriptor is found
             // Check interface and alternate setting number
             if ((iface_num == udc_ptr_iface->bInterfaceNumber) &&
                     (setting_num ==
                     udc_ptr_iface->bAlternateSetting)) {
                 return true; // Interface found
             }
         }
         // Go to next descriptor
         udc_ptr_iface = (UDC_DESC_STORAGE usb_iface_desc_t *) (
                 (uint8_t *) udc_ptr_iface +
                 udc_ptr_iface->bLength);
     }
     return false; // Interface not found
 }

 static bool udc_iface_disable(uint8_t iface_num)
 {
     udi_api_t UDC_DESC_STORAGE *udi_api;

     // Select first alternate setting of the interface
     // to update udc_ptr_iface before call iface->getsetting()
     if (!udc_update_iface_desc(iface_num, 0)) {
         return false;
     }

     // Select the interface with the current alternate setting
     udi_api = udc_ptr_conf->udi_apis[iface_num];

 #if (0!=USB_DEVICE_MAX_EP)
     if (!udc_update_iface_desc(iface_num, udi_api->getsetting())) {
         return false;
     }

     // Start at the beginning of interface descriptor
     {
         usb_ep_desc_t UDC_DESC_STORAGE *ep_desc;
         ep_desc = (UDC_DESC_STORAGE usb_ep_desc_t *) udc_ptr_iface;
         while (1) {
             // Search Endpoint descriptor included in global interface descriptor
             ep_desc = (UDC_DESC_STORAGE usb_ep_desc_t *)
                     udc_next_desc_in_iface((UDC_DESC_STORAGE
                     usb_conf_desc_t *)
                     ep_desc, USB_DT_ENDPOINT);
             if (NULL == ep_desc) {
                 break;
             }
             // Free the endpoint used by the interface
             udd_ep_free(ep_desc->bEndpointAddress);
         }
     }
 #endif

     // Disable interface
     udi_api->disable();
     return true;
 }

 static bool udc_iface_enable(uint8_t iface_num, uint8_t setting_num)
 {
     // Select the interface descriptor
     if (!udc_update_iface_desc(iface_num, setting_num)) {
         return false;
     }

 #if (0!=USB_DEVICE_MAX_EP)
     usb_ep_desc_t UDC_DESC_STORAGE *ep_desc;

     // Start at the beginning of the global interface descriptor
     ep_desc = (UDC_DESC_STORAGE usb_ep_desc_t *) udc_ptr_iface;
     while (1) {
         // Search Endpoint descriptor included in the global interface descriptor
         ep_desc = (UDC_DESC_STORAGE usb_ep_desc_t *)
                 udc_next_desc_in_iface((UDC_DESC_STORAGE
                         usb_conf_desc_t *) ep_desc,
                 USB_DT_ENDPOINT);
         if (NULL == ep_desc)
             break;
         // Alloc the endpoint used by the interface
         if (!udd_ep_alloc(ep_desc->bEndpointAddress,
                 ep_desc->bmAttributes,
                 le16_to_cpu
                 (ep_desc->wMaxPacketSize))) {
             return false;
         }
     }
 #endif
     // Enable the interface
     return udc_ptr_conf->udi_apis[iface_num]->enable();
 }

 void udc_start(void)
 {
     udd_enable();
 }

 void udc_stop(void)
 {
     udd_disable();
 }

 void udc_reset(void)
 {
     uint8_t iface_num;

     if (udc_num_configuration) {
         for (iface_num = 0;
                 iface_num < udc_ptr_conf->desc->bNumInterfaces;
                 iface_num++) {
             udc_iface_disable(iface_num);
         }
     }
     udc_num_configuration = 0;
 #if (USB_CONFIG_ATTR_REMOTE_WAKEUP \
     == (USB_DEVICE_ATTR & USB_CONFIG_ATTR_REMOTE_WAKEUP))
     if (CPU_TO_LE16(USB_DEV_STATUS_REMOTEWAKEUP) & udc_device_status) {
         // Remote wakeup is enabled then disable it
         UDC_REMOTEWAKEUP_DISABLE();
     }
 #endif
     udc_device_status =
 #if (USB_DEVICE_ATTR & USB_CONFIG_ATTR_SELF_POWERED)
             CPU_TO_LE16(USB_DEV_STATUS_SELF_POWERED);
 #else
             CPU_TO_LE16(USB_DEV_STATUS_BUS_POWERED);
 #endif
 }

 void udc_sof_notify(void)
 {
     uint8_t iface_num;

     if (udc_num_configuration) {
         for (iface_num = 0;
                 iface_num < udc_ptr_conf->desc->bNumInterfaces;
                 iface_num++) {
             if (udc_ptr_conf->udi_apis[iface_num]->sof_notify != NULL) {
                 udc_ptr_conf->udi_apis[iface_num]->sof_notify();
             }
         }
     }
 }

 static bool udc_req_std_dev_get_status(void)
 {
     if (udd_g_ctrlreq.req.wLength != sizeof(udc_device_status)) {
         return false;
     }

     udd_set_setup_payload( (uint8_t *) & udc_device_status,
             sizeof(udc_device_status));
     return true;
 }

 #if (0!=USB_DEVICE_MAX_EP)

 static bool udc_req_std_ep_get_status(void)
 {
     static le16_t udc_ep_status;

     if (udd_g_ctrlreq.req.wLength != sizeof(udc_ep_status)) {
         return false;
     }

     udc_ep_status = udd_ep_is_halted(udd_g_ctrlreq.req.
             wIndex & 0xFF) ? CPU_TO_LE16(USB_EP_STATUS_HALTED) : 0;

     udd_set_setup_payload( (uint8_t *) & udc_ep_status,
             sizeof(udc_ep_status));
     return true;
 }
 #endif

 static bool udc_req_std_dev_clear_feature(void)
 {
     if (udd_g_ctrlreq.req.wLength) {
         return false;
     }

     if (udd_g_ctrlreq.req.wValue == USB_DEV_FEATURE_REMOTE_WAKEUP) {
         udc_device_status &= CPU_TO_LE16(~USB_DEV_STATUS_REMOTEWAKEUP);
 #if (USB_CONFIG_ATTR_REMOTE_WAKEUP \
     == (USB_DEVICE_ATTR & USB_CONFIG_ATTR_REMOTE_WAKEUP))
         UDC_REMOTEWAKEUP_DISABLE();
 #endif
         return true;
     }
     return false;
 }

 #if (0!=USB_DEVICE_MAX_EP)

 static bool udc_req_std_ep_clear_feature(void)
 {
     if (udd_g_ctrlreq.req.wLength) {
         return false;
     }

     if (udd_g_ctrlreq.req.wValue == USB_EP_FEATURE_HALT) {
         return udd_ep_clear_halt(udd_g_ctrlreq.req.wIndex & 0xFF);
     }
     return false;
 }
 #endif

 static bool udc_req_std_dev_set_feature(void)
 {
     if (udd_g_ctrlreq.req.wLength) {
         return false;
     }

     switch (udd_g_ctrlreq.req.wValue) {

     case USB_DEV_FEATURE_REMOTE_WAKEUP:
 #if (USB_CONFIG_ATTR_REMOTE_WAKEUP \
     == (USB_DEVICE_ATTR & USB_CONFIG_ATTR_REMOTE_WAKEUP))
         udc_device_status |= CPU_TO_LE16(USB_DEV_STATUS_REMOTEWAKEUP);
         UDC_REMOTEWAKEUP_ENABLE();
         return true;
 #else
         return false;
 #endif

 #ifdef USB_DEVICE_HS_SUPPORT
     case USB_DEV_FEATURE_TEST_MODE:
         if (!udd_is_high_speed()) {
             break;
         }
         if (udd_g_ctrlreq.req.wIndex & 0xff) {
             break;
         }
         // Unconfigure the device, terminating all ongoing requests
         udc_reset();
         switch ((udd_g_ctrlreq.req.wIndex >> 8) & 0xFF) {
         case USB_DEV_TEST_MODE_J:
             udd_g_ctrlreq.callback = udd_test_mode_j;
             return true;

         case USB_DEV_TEST_MODE_K:
             udd_g_ctrlreq.callback = udd_test_mode_k;
             return true;

         case USB_DEV_TEST_MODE_SE0_NAK:
             udd_g_ctrlreq.callback = udd_test_mode_se0_nak;
             return true;

         case USB_DEV_TEST_MODE_PACKET:
             udd_g_ctrlreq.callback = udd_test_mode_packet;
             return true;

         case USB_DEV_TEST_MODE_FORCE_ENABLE: // Only for downstream facing hub ports
         default:
             break;
         }
         break;
 #endif
     default:
         break;
     }
     return false;
 }

 #if (0!=USB_DEVICE_MAX_EP)
 static bool udc_req_std_epset_feature(void)
 {
     if (udd_g_ctrlreq.req.wLength) {
         return false;
     }
     if (udd_g_ctrlreq.req.wValue == USB_EP_FEATURE_HALT) {
         return udd_ep_set_halt(udd_g_ctrlreq.req.wIndex & 0xFF);
     }
     return false;
 }
 #endif

 static void udc_valid_address(void)
 {
     udd_set_address(udd_g_ctrlreq.req.wValue & 0x7F);
 }

 static bool udc_req_std_dev_set_address(void)
 {
     if (udd_g_ctrlreq.req.wLength) {
         return false;
     }

     // The address must be changed at the end of setup request after the handshake
     // then we use a callback to change address
     udd_g_ctrlreq.callback = udc_valid_address;
     return true;
 }

 static bool udc_req_std_dev_get_str_desc(void)
 {
     uint8_t i;
     const uint8_t *str;
     uint8_t str_length = 0;

     // Link payload pointer to the string corresponding at request
     switch (udd_g_ctrlreq.req.wValue & 0xff) {
     case 0:
         udd_set_setup_payload((uint8_t *) &udc_string_desc_languageid,
                 sizeof(udc_string_desc_languageid));
         break;

 #ifdef USB_DEVICE_MANUFACTURE_NAME
     case 1:
         str_length = USB_DEVICE_MANUFACTURE_NAME_SIZE;
         str = udc_string_manufacturer_name;
         break;
 #endif
 #ifdef USB_DEVICE_PRODUCT_NAME
     case 2:
         str_length = USB_DEVICE_PRODUCT_NAME_SIZE;
         str = udc_string_product_name;
         break;
 #endif
 #if defined USB_DEVICE_SERIAL_NAME || defined USB_DEVICE_GET_SERIAL_NAME_POINTER
     case 3:
         str_length = USB_DEVICE_SERIAL_NAME_SIZE;
         str = udc_get_string_serial_name();
         break;
 #endif
     default:
 #ifdef UDC_GET_EXTRA_STRING
         if (UDC_GET_EXTRA_STRING()) {
             break;
         }
 #endif
         return false;
     }

     if (str_length) {
         for(i = 0; i < str_length; i++) {
             udc_string_desc.string[i] = cpu_to_le16((le16_t)str[i]);
         }

         udc_string_desc.header.bLength = 2 + (str_length) * 2;
         udd_set_setup_payload(
             (uint8_t *) &udc_string_desc,
             udc_string_desc.header.bLength);
     }

     return true;
 }

 static bool udc_req_std_dev_get_descriptor(void)
 {
     uint8_t conf_num;

     conf_num = udd_g_ctrlreq.req.wValue & 0xff;

     // Check descriptor ID
     switch ((uint8_t) (udd_g_ctrlreq.req.wValue >> 8)) {
     case USB_DT_DEVICE:
         // Device descriptor requested
 #ifdef USB_DEVICE_HS_SUPPORT
         if (!udd_is_high_speed()) {
             udd_set_setup_payload(
                 (uint8_t *) udc_config.confdev_hs,
                 udc_config.confdev_hs->bLength);
         } else
 #endif
         {
             udd_set_setup_payload(
                 (uint8_t *) udc_config.confdev_lsfs,
                 udc_config.confdev_lsfs->bLength);
         }
         break;

     case USB_DT_CONFIGURATION:
         // Configuration descriptor requested
 #ifdef USB_DEVICE_HS_SUPPORT
         if (udd_is_high_speed()) {
             // HS descriptor
             if (conf_num >= udc_config.confdev_hs->
                     bNumConfigurations) {
                 return false;
             }
             udd_set_setup_payload(
                 (uint8_t *)udc_config.conf_hs[conf_num].desc,
                 le16_to_cpu(udc_config.conf_hs[conf_num].desc->wTotalLength));
         } else
 #endif
         {
             // FS descriptor
             if (conf_num >= udc_config.confdev_lsfs->
                     bNumConfigurations) {
                 return false;
             }
             udd_set_setup_payload(
                 (uint8_t *)udc_config.conf_lsfs[conf_num].desc,
                 le16_to_cpu(udc_config.conf_lsfs[conf_num].desc->wTotalLength));
         }
         ((usb_conf_desc_t *) udd_g_ctrlreq.payload)->bDescriptorType =
                 USB_DT_CONFIGURATION;
         break;

 #ifdef USB_DEVICE_HS_SUPPORT
     case USB_DT_DEVICE_QUALIFIER:
         // Device qualifier descriptor requested
         udd_set_setup_payload( (uint8_t *) udc_config.qualifier,
                 udc_config.qualifier->bLength);
         break;

     case USB_DT_OTHER_SPEED_CONFIGURATION:
         // Other configuration descriptor requested
         if (!udd_is_high_speed()) {
             // HS descriptor
             if (conf_num >= udc_config.confdev_hs->
                     bNumConfigurations) {
                 return false;
             }
             udd_set_setup_payload(
                 (uint8_t *)udc_config.conf_hs[conf_num].desc,
                 le16_to_cpu(udc_config.conf_hs[conf_num].desc->wTotalLength));
         } else {
             // FS descriptor
             if (conf_num >= udc_config.confdev_lsfs->
                     bNumConfigurations) {
                 return false;
             }
             udd_set_setup_payload(
                 (uint8_t *)udc_config.conf_lsfs[conf_num].desc,
                 le16_to_cpu(udc_config.conf_lsfs[conf_num].desc->wTotalLength));
         }
         ((usb_conf_desc_t *) udd_g_ctrlreq.payload)->bDescriptorType =
                 USB_DT_OTHER_SPEED_CONFIGURATION;
         break;
 #endif

     case USB_DT_STRING:
         // String descriptor requested
         if (!udc_req_std_dev_get_str_desc()) {
             return false;
         }
         break;

     default:
         // Unknown descriptor requested
         return false;
     }
     // if the descriptor is larger than length requested, then reduce it
     if (udd_g_ctrlreq.req.wLength < udd_g_ctrlreq.payload_size) {
         udd_g_ctrlreq.payload_size = udd_g_ctrlreq.req.wLength;
     }
     return true;
 }

 static bool udc_req_std_dev_get_configuration(void)
 {
     if (udd_g_ctrlreq.req.wLength != 1) {
         return false;
     }

     udd_set_setup_payload(&udc_num_configuration,1);
     return true;
 }

 static bool udc_req_std_dev_set_configuration(void)
 {
     uint8_t iface_num;

     // Check request length
     if (udd_g_ctrlreq.req.wLength) {
         return false;
     }
     // Authorize configuration only if the address is valid
     if (!udd_getaddress()) {
         return false;
     }
     // Check the configuration number requested
 #ifdef USB_DEVICE_HS_SUPPORT
     if (udd_is_high_speed()) {
         // HS descriptor
         if ((udd_g_ctrlreq.req.wValue & 0xFF) >
                 udc_config.confdev_hs->bNumConfigurations) {
             return false;
         }
     } else
 #endif
     {
         // FS descriptor
         if ((udd_g_ctrlreq.req.wValue & 0xFF) >
                 udc_config.confdev_lsfs->bNumConfigurations) {
             return false;
         }
     }

     // Reset current configuration
     udc_reset();

     // Enable new configuration
     udc_num_configuration = udd_g_ctrlreq.req.wValue & 0xFF;
     if (udc_num_configuration == 0) {
         return true; // Default empty configuration requested
     }
     // Update pointer of the configuration descriptor
 #ifdef USB_DEVICE_HS_SUPPORT
     if (udd_is_high_speed()) {
         // HS descriptor
         udc_ptr_conf = &udc_config.conf_hs[udc_num_configuration - 1];
     } else
 #endif
     {
         // FS descriptor
         udc_ptr_conf = &udc_config.conf_lsfs[udc_num_configuration - 1];
     }
     // Enable all interfaces of the selected configuration
     for (iface_num = 0; iface_num < udc_ptr_conf->desc->bNumInterfaces;
             iface_num++) {
         if (!udc_iface_enable(iface_num, 0)) {
             return false;
         }
     }
     return true;
 }

 static bool udc_req_std_iface_get_setting(void)
 {
     static uint8_t udc_iface_setting;
     uint8_t iface_num;
     udi_api_t UDC_DESC_STORAGE *udi_api;

     if (udd_g_ctrlreq.req.wLength != 1) {
         return false; // Error in request
     }
     if (!udc_num_configuration) {
         return false; // The device is not is configured state yet
     }

     // Check the interface number included in the request
     iface_num = udd_g_ctrlreq.req.wIndex & 0xFF;
     if (iface_num >= udc_ptr_conf->desc->bNumInterfaces) {
         return false;
     }

     // Select first alternate setting of the interface to update udc_ptr_iface
     // before call iface->getsetting()
     if (!udc_update_iface_desc(iface_num, 0)) {
         return false;
     }
     // Get alternate setting from UDI
     udi_api = udc_ptr_conf->udi_apis[iface_num];
     udc_iface_setting = udi_api->getsetting();

     // Link value to payload pointer of request
     udd_set_setup_payload(&udc_iface_setting,1);
     return true;
 }

 static bool udc_req_std_iface_set_setting(void)
 {
     uint8_t iface_num, setting_num;

     if (udd_g_ctrlreq.req.wLength) {
         return false; // Error in request
     }
     if (!udc_num_configuration) {
         return false; // The device is not is configured state yet
     }

     iface_num = udd_g_ctrlreq.req.wIndex & 0xFF;
     setting_num = udd_g_ctrlreq.req.wValue & 0xFF;

     // Disable current setting
     if (!udc_iface_disable(iface_num)) {
         return false;
     }

     // Enable new setting
     return udc_iface_enable(iface_num, setting_num);
 }

 static bool udc_reqstd(void)
 {
     if (Udd_setup_is_in()) {
         // GET Standard Requests
         if (udd_g_ctrlreq.req.wLength == 0) {
             return false; // Error for USB host
         }

         if (USB_REQ_RECIP_DEVICE == Udd_setup_recipient()) {
             // Standard Get Device request
             switch (udd_g_ctrlreq.req.bRequest) {
             case USB_REQ_GET_STATUS:
                 return udc_req_std_dev_get_status();
             case USB_REQ_GET_DESCRIPTOR:
                 return udc_req_std_dev_get_descriptor();
             case USB_REQ_GET_CONFIGURATION:
                 return udc_req_std_dev_get_configuration();
             default:
                 break;
             }
         }

         if (USB_REQ_RECIP_INTERFACE == Udd_setup_recipient()) {
             // Standard Get Interface request
             switch (udd_g_ctrlreq.req.bRequest) {
             case USB_REQ_GET_INTERFACE:
                 return udc_req_std_iface_get_setting();
             default:
                 break;
             }
         }
 #if (0!=USB_DEVICE_MAX_EP)
         if (USB_REQ_RECIP_ENDPOINT == Udd_setup_recipient()) {
             // Standard Get Endpoint request
             switch (udd_g_ctrlreq.req.bRequest) {
             case USB_REQ_GET_STATUS:
                 return udc_req_std_ep_get_status();
             default:
                 break;
             }
         }
 #endif
     } else {
         // SET Standard Requests
         if (USB_REQ_RECIP_DEVICE == Udd_setup_recipient()) {
             // Standard Set Device request
             switch (udd_g_ctrlreq.req.bRequest) {
             case USB_REQ_SET_ADDRESS:
                 return udc_req_std_dev_set_address();
             case USB_REQ_CLEAR_FEATURE:
                 return udc_req_std_dev_clear_feature();
             case USB_REQ_SET_FEATURE:
                 return udc_req_std_dev_set_feature();
             case USB_REQ_SET_CONFIGURATION:
                 return udc_req_std_dev_set_configuration();
             case USB_REQ_SET_DESCRIPTOR:
                 /* Not supported (defined as optional by the USB 2.0 spec) */
                 break;
             default:
                 break;
             }
         }

         if (USB_REQ_RECIP_INTERFACE == Udd_setup_recipient()) {
             // Standard Set Interface request
             switch (udd_g_ctrlreq.req.bRequest) {
             case USB_REQ_SET_INTERFACE:
                 return udc_req_std_iface_set_setting();
             default:
                 break;
             }
         }
 #if (0!=USB_DEVICE_MAX_EP)
         if (USB_REQ_RECIP_ENDPOINT == Udd_setup_recipient()) {
             // Standard Set Endpoint request
             switch (udd_g_ctrlreq.req.bRequest) {
             case USB_REQ_CLEAR_FEATURE:
                 return udc_req_std_ep_clear_feature();
             case USB_REQ_SET_FEATURE:
                 return udc_req_std_epset_feature();
             default:
                 break;
             }
         }
 #endif
     }
     return false;
 }

 static bool udc_req_iface(void)
 {
     uint8_t iface_num;
     udi_api_t UDC_DESC_STORAGE *udi_api;

     if (0 == udc_num_configuration) {
         return false; // The device is not is configured state yet
     }
     // Check interface number
     iface_num = udd_g_ctrlreq.req.wIndex & 0xFF;
     if (iface_num >= udc_ptr_conf->desc->bNumInterfaces) {
         return false;
     }

     //* To update udc_ptr_iface with the selected interface in request
     // Select first alternate setting of interface to update udc_ptr_iface
     // before calling udi_api->getsetting()
     if (!udc_update_iface_desc(iface_num, 0)) {
         return false;
     }
     // Select the interface with the current alternate setting
     udi_api = udc_ptr_conf->udi_apis[iface_num];
     if (!udc_update_iface_desc(iface_num, udi_api->getsetting())) {
         return false;
     }

     // Send the SETUP request to the UDI corresponding to the interface number
     return udi_api->setup();
 }

 bool udc_process_setup(void)
 {
     // By default no data (receive/send) and no callbacks registered
     udd_g_ctrlreq.payload_size = 0;
     udd_g_ctrlreq.callback = NULL;
     udd_g_ctrlreq.over_under_run = NULL;

     if (Udd_setup_is_in()) {
         if (udd_g_ctrlreq.req.wLength == 0) {
             return false; // Error from USB host
         }
     }

     // If standard request then try to decode it in UDC
     if (Udd_setup_type() == USB_REQ_TYPE_STANDARD) {
         if (udc_reqstd()) {
             return true;
         }
     }

     // If interface request then try to decode it in UDI
     if (Udd_setup_recipient() == USB_REQ_RECIP_INTERFACE) {
         if (udc_req_iface()) {
             return true;
         }
     }

     // Here SETUP request unknown by UDC and UDIs
 #ifdef USB_DEVICE_SPECIFIC_REQUEST
     // Try to decode it in specific callback
     return USB_DEVICE_SPECIFIC_REQUEST(); // Ex: Vendor request,...
 #else
     return false;
 #endif
 }

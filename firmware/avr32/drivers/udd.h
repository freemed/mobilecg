
 #ifndef _UDD_H_
 #define _UDD_H_

 #include "usb_protocol.h"
 #include "udc_desc.h"

 #ifdef __cplusplus
 extern "C" {
 #endif


 typedef uint8_t udd_ep_id_t;

 typedef enum {
     UDD_EP_TRANSFER_OK = 0,
     UDD_EP_TRANSFER_ABORT = 1,
 } udd_ep_status_t;

 typedef struct {
     usb_setup_req_t req;

     uint8_t *payload;

     uint16_t payload_size;

     void (*callback) (void);

     bool(*over_under_run) (void);
 } udd_ctrl_request_t;
 extern udd_ctrl_request_t udd_g_ctrlreq;

 #define  Udd_setup_is_in()       \
       (USB_REQ_DIR_IN == (udd_g_ctrlreq.req.bmRequestType & USB_REQ_DIR_MASK))

 #define  Udd_setup_is_out()      \
       (USB_REQ_DIR_OUT == (udd_g_ctrlreq.req.bmRequestType & USB_REQ_DIR_MASK))

 #define  Udd_setup_type()        \
       (udd_g_ctrlreq.req.bmRequestType & USB_REQ_TYPE_MASK)

 #define  Udd_setup_recipient()   \
       (udd_g_ctrlreq.req.bmRequestType & USB_REQ_RECIP_MASK)

 typedef void (*udd_callback_halt_cleared_t) (void);

 typedef void (*udd_callback_trans_t) (udd_ep_status_t status,
         iram_size_t nb_transfered);

 bool udd_include_vbus_monitoring(void);

 void udd_enable(void);

 void udd_disable(void);

 void udd_attach(void);

 void udd_detach(void);

 bool udd_is_high_speed(void);

 void udd_set_address(uint8_t address);

 uint8_t udd_getaddress(void);

 uint16_t udd_get_frame_number(void);

 uint16_t udd_get_micro_frame_number(void);

 void udd_send_wake_up(void);

 void udd_set_setup_payload( uint8_t *payload, uint16_t payload_size );



 #if (USB_DEVICE_MAX_EP != 0)

 bool udd_ep_alloc(udd_ep_id_t ep, uint8_t bmAttributes,
         uint16_t MaxEndpointSize);

 void udd_ep_free(udd_ep_id_t ep);

 bool udd_ep_is_halted(udd_ep_id_t ep);

 bool udd_ep_set_halt(udd_ep_id_t ep);

 bool udd_ep_clear_halt(udd_ep_id_t ep);

 bool udd_ep_wait_stall_clear(udd_ep_id_t ep,
         udd_callback_halt_cleared_t callback);

 bool udd_ep_run(udd_ep_id_t ep, bool b_shortpacket,
         uint8_t * buf, iram_size_t buf_size,
         udd_callback_trans_t callback);
 void udd_ep_abort(udd_ep_id_t ep);

 #endif



 void udd_test_mode_j(void);
 void udd_test_mode_k(void);
 void udd_test_mode_se0_nak(void);
 void udd_test_mode_packet(void);



 extern bool udc_process_setup(void);

 extern void udc_reset(void);

 extern void udc_sof_notify(void);



 #ifdef __cplusplus
 }
 #endif
 #endif // _UDD_H_

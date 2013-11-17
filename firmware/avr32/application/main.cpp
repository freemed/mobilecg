extern "C" {
	#include "compiler.h"
	#include "preprocessor.h"
	#include "board.h"
	#include "gpio.h"
	#include "sysclk.h"
	#include "sleepmgr.h"
	#include "conf_usb.h"
	#include "usbc_device.h"
	#include "udc.h"
	#include "udd.h"
	#include "config.h"
}

#include "ecg_controller.hpp"
#include "hardware_interface.hpp"
#include "usart_driver.hpp"
#include "usb_packet_buffer.hpp"
#include "usb_packets.hpp"

extern "C" void __cxa_pure_virtual() { while (1); }

volatile FooBar foobar;

volatile static uint32_t tc_counter = 0;
UsbPacketBuffer usb_packet_buffer;
EcgController ecg_controller(usb_packet_buffer);

void usb_receive_packet(uint8_t* data)
{
	if(NULL == data || data[0] != COMMAND_PACKET)
	{
		// TODO: handle invalid packet error
		return;
	}
	CommandPacketOut *packet = (CommandPacketOut*)data;
	switch(packet->command)
	{
		case DEBUGCMD_LED1_OFF:
			hw::led1(false);
			break;
		case DEBUGCMD_LED1_ON:
			hw::led1(true);
			break;
		case DEBUGCMD_LED2_OFF:
			hw::led2(false);
			break;
		case DEBUGCMD_LED2_ON:
			hw::led2(true);
			break;
		case CMD_START_MEASUREMENT:
			usb_packet_buffer.add_debug_message("Starting measurement.");
			ecg_controller.startRecording();
			break;
		case CMD_STOP_MEASUREMENT:
			usb_packet_buffer.add_debug_message("Stopping measurement.");
			ecg_controller.stopRecording();
			break;
		case CMD_GET_STATUS:
		{
			StatusPacketIn packet;
			packet.is_recording = false;
			usb_packet_buffer.add_packet(&packet);
			break;
		}
	}
}

int initial_test_timer = 0; // 325*3;

__attribute__((__interrupt__))
static void timer_interrupt(void)
{
	tc_counter++;
	clear_timer_interrupt();

	if(tc_counter == 250)
	{
		StatusPacketIn packet;
		packet.is_recording = false;
		//usb_packet_buffer.add_packet(&packet);
		tc_counter = 0;
	}
	/*if(ecg_controller.isRecording())
	{
		DataPacketIn dummy;
		dummy.time_stamp = foobar.ms;
		usb_packet_buffer.add_packet(&dummy);
		foobar.ms++;
	}
	else
		foobar.ms = 0;*/
/*	if(ecg_controller.isRecording())
		ecg_controller.onReceiveData(0, 30);*/
/*	if(initial_test_timer > 0)
		initial_test_timer--;
	if(initial_test_timer == 1)
		ecg_controller.stopRecording();*/
}

void usb_pins_init()
{
	static const gpio_map_t USB_GPIO_MAP =
	{
		{AVR32_USBC_DP_0_PIN, AVR32_USBC_DP_0_FUNCTION},
		{AVR32_USBC_DM_0_PIN, AVR32_USBC_DM_0_FUNCTION},
		{AVR32_USBC_VBUS_0_PIN, AVR32_USBC_VBUS_0_FUNCTION}
	};

	gpio_enable_module(USB_GPIO_MAP, sizeof(USB_GPIO_MAP) / sizeof(USB_GPIO_MAP[0]));
}

int main()
{
	sysclk_init();
	irq_initialize_vectors();
	cpu_irq_enable();

	hw::init();
	// Initialize the sleep manager
	sleepmgr_init();

	setup_timer_controller(timer_interrupt);

	usb_pins_init();

	udc_start();
	usart::init(&ecg_controller);

	if (!udc_include_vbus_monitoring()) {
		// VBUS monitoring is not available on this product
		// thereby VBUS has to be considered as present
		main_vbus_action(true);
	}

	while (true) {
		usb_packet_buffer.do_send_task();
		// sleepmgr_enter_sleep();
	}
	
	while(1);
	return 0;
}

 void main_vbus_action(bool b_high)
 {
     if (b_high) {
         // Attach USB Device
         udc_attach();
     } else {
         // VBUS not present
         udc_detach();
     }
 }

 void main_suspend_action(void)
 {
 }

 void main_resume_action(void)
 {
 }

volatile bool main_b_generic_enable;

 void main_sof_action(void)
 {
//	if (!main_b_generic_enable)
//		return;
	foobar.reason1++;
 }

 void main_remotewakeup_enable(void)
 {
//     ui_wakeup_enable();
 }

 void main_remotewakeup_disable(void)
 {
//     ui_wakeup_disable();
 }

 bool main_generic_enable(void)
 {
     main_b_generic_enable = true;
     return true;
 }

 void main_generic_disable(void)
 {
     main_b_generic_enable = false;
 }

 void main_hid_set_feature(uint8_t* report)
 {
     if (*((uint32_t*)report)==0x55AA55AA) {
         // Disconnect USB Device
         udc_stop();
     }
 }

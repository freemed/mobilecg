#include "usb_packet_buffer.hpp"
#include "usb_packets.hpp"

#include <hardware_interface.hpp>
#include <udi_hid_generic.h>

void UsbPacketBuffer::do_send_task()
{
	char *buffer = udi_hid_generic_get_buffer_in();
	if(!buffer)
		return;
	if(!usb_packet_buffer_.popBytes(buffer, 1))
		return;

	int size = getUsbPacketSize((int)buffer[0]);
	if(!usb_packet_buffer_.popBytes(buffer+1, size-1))
	{
		hw::led1(true);
		return;
	}
	udi_hid_generic_send_buffer_in();
	
}

void UsbPacketBuffer::add_packet(void* data)
{
	char* packet = (char*) data;
	int size = getUsbPacketSize(packet[0]);
	usb_packet_buffer_.pushBytes(packet, size);
}

void UsbPacketBuffer::add_debug_message(const char* message)
{
	char packet_id = DEBUG_PACKET;
	usb_packet_buffer_.pushBytes(&packet_id, 1);
	usb_packet_buffer_.pushBytes(message, sizeof(DebugPacketIn)-1);
}

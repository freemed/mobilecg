#ifndef USB_PACKET_BUFFER_H
#define USB_PACKET_BUFFER_H

#include "circular_buffer.hpp"

class UsbPacketBuffer
{
public:
	UsbPacketBuffer():
		act_packet_valid_(false)
	{
	}
	void do_send_task();
	void add_packet(void* data);
	void add_debug_message(const char* message);
	int freeBytes() const { return usb_packet_buffer_.freeBytes(); }
private:
	CircularBuffer<5000> usb_packet_buffer_;
	char act_packet_[64];
	bool act_packet_valid_;
	int frames_in_packet;
};

#endif

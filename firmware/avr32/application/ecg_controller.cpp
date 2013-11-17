#include "debug.hpp"
#include "ecg_controller.hpp"
#include "hardware_interface.hpp"
#include "usart_driver.hpp"
#include "usb_packet_buffer.hpp"
#include "usb_packets.hpp"

char debug_str_[63];
volatile int debug_idx_;


void EcgController::startRecording()
{
	// TODO: egy picit ezeket késleltetve
	hw::led2(true);
	is_recording_ = true;
	time_stamp_ = 0;
	hw::ecg_power_on();
	hw::iso_power_on();
	usart::init(this);
	usart::enable();

	last_packet_id_ = -1;
	debug_idx_ = 0;
}

void EcgController::stopRecording()
{
	usart::disable();
	hw::iso_power_off();
	hw::ecg_power_off();
	time_stamp_ = -1;
	is_recording_ = false;
	hw::led2(false);
}


void EcgController::onReceiveData(char* buffer, int num_packets)
{
	char *ptr = buffer;
	DataPacketIn packet;
	int frame_cnt = 0;
	for(int p = 0; p < num_packets; p++)
	{
		for(int ch = 0; ch < 8; ch++)
		{
			int sample = *(ptr++) << 16;
			sample |= *(ptr++) << 8;
			sample |= *(ptr++);
			if(0 != (sample & 0x800000))
				sample |= 0xff000000;
			filters_[ch].put(sample);
		}
		
		char packet_id = *(ptr++);

		last_packet_id_++;
		if(packet_id != last_packet_id_)
		{
			char message[128];
			int n = (unsigned char)packet_id;
			int o = (unsigned char)(last_packet_id_);
			debug::sprintf(message, "Error: corrupt packet ID: %d instead of %d.", n, o);
			usb_buffer_.add_debug_message(message);
		}
		last_packet_id_ = packet_id;

		if(filters_[0].available())
		{
			for(int ch = 0; ch < 8; ch++)
				packet.channel_data[frame_cnt & 1][ch] = filters_[ch].get();
			if(frame_cnt & 1)
			{
				packet.time_stamp = time_stamp_++;
				usb_buffer_.add_packet(&packet);
				if(time_stamp_ % 500 == 0)
				{
					char message[128];
					debug::sprintf(message, "Free bytes in buffer: %d.", usb_buffer_.freeBytes());
					usb_buffer_.add_debug_message(message);
				}
			}
			frame_cnt++;
		}
	}
}

#ifndef ECG_CONTROLLER_H
#define ECG_CONTROLLER_H

#include "decimation_filter.hpp"
#include <stddef.h>

class UsbPacketBuffer;

class AbstractClass
{
public:
	void* operator new(size_t n)
	{
		return (void*)-1;
	}

	void operator delete(void* p)
	{
	}
};

class IEcgDataAcceptor: public AbstractClass
{
public:
	virtual ~IEcgDataAcceptor() {}
	virtual void onReceiveData(char* buffer, int num_packets) = 0;
};

class EcgController: public IEcgDataAcceptor
{
public:
	EcgController(UsbPacketBuffer &usb_buffer):
		is_recording_(false),
		time_stamp_(-1),
		usb_buffer_(usb_buffer)
	{
	}
	
	void startRecording();
	void stopRecording();
	
	virtual void onReceiveData(char* buffer, int size);

	bool isRecording() { return is_recording_; }

private:
	bool is_recording_;
	int time_stamp_;
	DecimationFilter filters_[8];
	UsbPacketBuffer &usb_buffer_;
	volatile char last_packet_id_;
};

#endif

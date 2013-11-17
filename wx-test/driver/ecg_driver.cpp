#include "ecg_driver.hpp"
#include "i_ecg_event_handler.hpp"
#include <pthread.h>
#include <unistd.h>
#include "usb_packets.hpp"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern "C"
{
	#include "hid.h"
}

const int kManufacturerId = 0x03EB;
const int kDeviceId = 0x2402;
const int kSendTimeout = 2200;

void* EcgDriver::runThread(void *param)
{
	EcgDriver* driver = (EcgDriver*) param;
	driver->doTask();
	return 0;
}

EcgDriver::EcgDriver(IEcgEventHandler& event_handler):
	device_id_(0),
	event_handler_(event_handler),
	stop_thread_(false),
	current_recv_timeout_(1)
{
	pthread_create(&thread_, NULL, runThread, this);
}

EcgDriver::~EcgDriver()
{
	stop_thread_ = true;
	void *status;
	pthread_join(thread_, &status);
}

void EcgDriver::sendPacket(void* packet, int size)
{
	char buf[64];
	memcpy(buf, packet, size);
	int r = rawhid_send(0, buf, 64, kSendTimeout);
	if(r == 0)
	{
		device_id_ = 0;
		event_handler_.onDisconnected(true);
	}
}

void EcgDriver::sendCommand(char command)
{
	CommandPacketOut packet;
	packet.packet_type = COMMAND_PACKET;
	packet.command = command;
	sendPacket(&packet, 64);
}

void EcgDriver::connect()
{
	device_id_ = rawhid_open(1, kManufacturerId, kDeviceId, -1, -1);
	if(device_id_ > 0)
	{
		event_handler_.onConnected();
	}
}

void EcgDriver::disconnect()
{
	rawhid_close(0);
	event_handler_.onDisconnected(false);
}

void EcgDriver::startRecording()
{
	sendCommand(CMD_START_MEASUREMENT);
}

void EcgDriver::stopRecording()
{
	sendCommand(CMD_STOP_MEASUREMENT);
}

void EcgDriver::doTask()
{
	rawhid_open(0, kManufacturerId, kDeviceId, -1, -1);
	printf("Starting task.\n");
	while (!stop_thread_) {
		char buf[65];
		if(device_id_ <= 0)
		{
			printf("No device id.\n");
			usleep(1000*100);
			continue;
		}
		int num = rawhid_recv(0, buf, 64, current_recv_timeout_);
		if (num < 0) {
			device_id_ = 0;
			event_handler_.onDisconnected(true);
			continue;
		}
		if(num == 0)
		{
			if(current_recv_timeout_ < 100)
				current_recv_timeout_ *= 2;
			continue;
		}
		/*current_recv_timeout_ /= 2;
		if(current_recv_timeout_ < 1)*/
		current_recv_timeout_ = 1;
		
		/*printf("PACKET:");
		printf("\n  [");
		for(int i = 0; i < num; i++)
			if(buf[i] < 32)
				printf("%%%02X", buf[i]);
			else
				printf("%c", buf[i]);
		printf("]");
		printf("\n");*/

		switch(buf[0])
		{
			case DATA_PACKET:
			{
				DataPacketIn* packet = ((DataPacketIn*)&buf[0]);
				event_handler_.onReceiveData(*packet);
				break;
			}
			case DEBUG_PACKET:
				buf[64] = 0;
				event_handler_.onReceiveDebugMessage(buf+1);
				break;
			case STATUS_PACKET:
				StatusPacketIn* status = ((StatusPacketIn*)&buf[0]);
				event_handler_.onReceiveStatus(*status);
				break;
		};
	}
	printf("Exiting task.\n");
}

void EcgDriver::requestStatus()
{
	sendCommand(CMD_GET_STATUS);
}

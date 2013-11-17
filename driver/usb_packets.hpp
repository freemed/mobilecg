#ifndef DATA_PACKET_H
#define DATA_PACKET_H

#include <stdint.h>
#include "int24.hpp"
#include "versions.h"

typedef enum {
	INVALID_PACKET = 0,
	DATA_PACKET = 1,
	STATUS_PACKET = 2,
	COMMAND_PACKET = 3,
	DEBUG_PACKET = 4,
	MAX_PACKET_ID = 5
} ePacket;

struct __attribute__((packed)) DataPacketIn {
	char packet_type; // Packet type.
	uint32_t time_stamp; // Packet number. 
	int24 channel_data[2][8]; // ECG data.
	int16_t common_mode[2]; // Common mode signal.
	char pace; // Pacemaker data, 1 bit / channel.
	uint16_t lead_off; // Lead off data, 1 bit / lead.
	int16_t temperature; // Temperature.
	char lead_test1;
	char lead_test2;

	DataPacketIn():
		packet_type(DATA_PACKET)
	{
	}
};

struct __attribute__((packed)) StatusPacketIn {
	char packet_type; // Packet type.
	char hw_version;
	uint16_t fw_version;
	char is_recording;
	uint16_t internal_error;

	StatusPacketIn():
		packet_type(STATUS_PACKET),
		hw_version(HARDWARE_VERSION),
		fw_version(FIRMWARE_VERSION),
		internal_error(0)
	{
	}
};

struct __attribute__((packed)) DebugPacketIn {
	char packet_type; // Packet type.
	char data[63];

	DebugPacketIn():
		packet_type(DEBUG_PACKET)
	{
	}
};

typedef enum {
	CMD_GET_STATUS = 0,
	CMD_START_MEASUREMENT = 1,
	CMD_KEEP_MEASUREMENT = 2,
	CMD_STOP_MEASUREMENT = 3,
	DEBUGCMD_LED1_ON = 100,
	DEBUGCMD_LED1_OFF = 101,
	DEBUGCMD_LED2_ON = 102,
	DEBUGCMD_LED2_OFF = 103
} eCommand;

struct __attribute__((packed)) CommandPacketOut {
	char packet_type; // Packet type.
	char command;
};

int getUsbPacketSize(char packet_type);

#endif

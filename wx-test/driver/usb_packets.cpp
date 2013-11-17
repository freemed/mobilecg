#include "usb_packets.hpp"

int getUsbPacketSize(char packet_type)
{
	switch(packet_type)
	{
		case DATA_PACKET:
			return sizeof(DataPacketIn);
		case STATUS_PACKET:
			return sizeof(StatusPacketIn);
		case COMMAND_PACKET:
			return sizeof(CommandPacketOut);
		case DEBUG_PACKET:
			return sizeof(DebugPacketIn);
	}
	return 0;
}


#include "i_ecg_event_handler.hpp"
#include "ecg_driver.hpp"
#include <unistd.h>
#include "usb_packets.hpp"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

uint32_t swap_endianness(uint32_t num)
{
	return ((num>>24)&0xff) |
		((num<<8)&0xff0000) |
		((num>>8)&0xff00) |
		((num<<24)&0xff000000);
}

FILE *file;

class MyEventHandler: public IEcgEventHandler
{
public:
	MyEventHandler():
		last_time_stamp_(0)
	{
	}

	virtual void onConnected()
	{
		printf("Connected.\n");
		last_time_stamp_ = -1;
	}
	
	virtual void onDisconnected(bool error)
	{
		printf("Disconnected.\n");
	}
	
	virtual void onReceiveData(const DataPacketIn& packet)
	{
		int ts = swap_endianness(packet.time_stamp);
		printf("DATA %d.\n", ts);
		if(last_time_stamp_+1 != ts)
			printf("ERROR: Missing packet(s) between %d and %d.\n", last_time_stamp_, ts);
		
		for(int ch = 0; ch < 8; ch++)
			fprintf(file, "%d ", (int)packet.channel_data[0][ch]);
		fprintf(file, "\n");
		for(int ch = 0; ch < 8; ch++)
			fprintf(file, "%d ", (int)packet.channel_data[1][ch]);
		fprintf(file, "\n");
		last_time_stamp_ = ts;
	}
	
	virtual void onReceiveDebugMessage(char *message)
	{
		/*for(int i = 0; i < 63 && message[i]; i++)
			printf("%02X ", (unsigned char)message[i]);
		printf("\n");*/
		printf("*** DEBUG: %s\n", message);
	}
	
	virtual void onReceiveStatus(const StatusPacketIn& status)
	{
		printf("# hw version %d.%d, recording: %d, error: %d\n",
			(int)status.hw_version,
			(int)status.fw_version,
			status.is_recording,
			status.internal_error
		);
	}
	
	virtual ~MyEventHandler()
	{
	}
	
	int getNumPackets()
	{
		return last_time_stamp_;
	}
private:
	int last_time_stamp_;
};

int main(int argc, char *argv[])
{
	file = fopen("out.txt", "w");
	MyEventHandler handler;
	EcgDriver driver(handler);
	driver.connect();
	if(!driver.isConnected())
	{
		printf("Could not connect.\n");
		return -1;
	}
	driver.requestStatus();
	
	struct timeval start, end;
	gettimeofday(&start, NULL);

	driver.startRecording();

	getchar();

	gettimeofday(&end, NULL);
	
	long seconds  = end.tv_sec  - start.tv_sec;
	long useconds = end.tv_usec - start.tv_usec;
	double dseconds = seconds + useconds/1000000.0;

	driver.stopRecording();
	sleep(1);
	printf("Number of packets is %d, which means %lf sample/s.\n", handler.getNumPackets(), handler.getNumPackets()*2.0/dseconds);
	driver.disconnect();
	fclose(file);
	return 0;
}


#ifndef ECG_DRIVER_H
#define ECG_DRIVER_H

#include <pthread.h>

class IEcgEventHandler;

class EcgDriver
{
public:
	EcgDriver(IEcgEventHandler& event_handler);

	~EcgDriver();
	
	void connect();
	void disconnect();
	void startRecording();
	void stopRecording();
	void requestStatus();

	bool isConnected() {return device_id_ > 0;}
private:
	void doTask();
	static void* runThread(void *param);
	void sendPacket(void* packet, int size);
	void sendCommand(char command);
	bool is_recording_;
	int device_id_;
	IEcgEventHandler& event_handler_;
	pthread_t thread_;
	bool stop_thread_;
	int current_recv_timeout_;
};

#endif

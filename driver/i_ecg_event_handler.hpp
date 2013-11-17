#ifndef I_ECG_EVENT_HANDLER_H
#define I_ECG_EVENT_HANDLER_H

class DataPacketIn;
class StatusPacketIn;

class IEcgEventHandler
{
public:
	virtual void onConnected() = 0;
	virtual void onDisconnected(bool error) = 0;
	virtual void onReceiveData(const DataPacketIn& packet) = 0;
	virtual void onReceiveStatus(const StatusPacketIn& status) = 0;
	virtual void onReceiveDebugMessage(char *message) = 0;
	
	
	virtual ~IEcgEventHandler() {}
};

#endif

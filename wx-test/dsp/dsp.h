#include "baseline.hpp"
#include "notch.hpp"
#include <vector>
#include "../driver/usb_packets.hpp"


enum EcgChannel {
	CHANNEL_AVR = 0,
	CHANNEL_AVL,
	CHANNEL_AVF,
	CHANNEL_I,
	CHANNEL_II,
	CHANNEL_III,
	CHANNEL_V1,
	CHANNEL_V2,
	CHANNEL_V3,
	CHANNEL_V4,
	CHANNEL_V5,
	CHANNEL_V6
};

struct EcgSample
{
	double data[12];
};

class EcgSampleBuffer
{
public:
	const EcgSample* getSample(int n) const 
	{
		int size = samples_.size();
		if(n > size-1)
			return NULL;
		return &samples_[size-1-n];
	}
	void putSample(EcgSample& sample)
	{
		samples_.push_back(sample);
	}
private:
	std::vector<EcgSample> samples_;
};

class PacketToSample
{
public:
	void processPacket(const DataPacketIn &packet, EcgSample *out1, EcgSample *out2);
private:
	void processHalfPacket(const int24 *channel_data, EcgSample *out);
};

class BaselineFilterBuffer
{
public:
	void putSample(EcgSample& sample)
	{
		EcgSample filtered;
		for(int i = 0; i < 12; i++)
			filtered.data[i] = 
				notch_filters_[i].filter(
					fwd_filters_[i].filter(
						sample.data[i]
					)
				);
		prefiltered_.push_back(filtered);
	}
	
	bool getNextSample(EcgSample *out)
	{
		if(idx_ < 0)
			return false;
		for(int i = 0; i < 12; i++)
			out->data[i] = bwd_filters_[i].filter(prefiltered_[idx_].data[i]);
		idx_--;
		return true;
	}
	
	void reset()
	{
		for(int i = 0; i < 12; i++)
			bwd_filters_[i].reset();
		idx_ = prefiltered_.size()-1;
	}
private:
	std::vector<EcgSample> prefiltered_;
	NotchIIR notch_filters_[12];
	BaselineIIR fwd_filters_[12];
	BaselineIIR bwd_filters_[12];
	int idx_;
};

#include "dsp.h"


void PacketToSample::processHalfPacket(const int24 *channel_data, EcgSample *out)
{
	double data[8];
// This needs to be calibrated.
	for(int ch = 0; ch < 8; ch++)
		data[ch] = ((int)channel_data[ch])*0.00005960464478;
	double wct_f = (data[0]+data[1]) / 3.0;
	out->data[CHANNEL_AVR] = data[1] - wct_f; // R-F - (W-F) = R-W
	out->data[CHANNEL_AVL] = data[0] - wct_f; // L-F - (W-F) = L-W
    out->data[CHANNEL_AVF] = - wct_f; // F-W
    out->data[CHANNEL_V1]  = data[2] - wct_f; // V1-F - (W-F)
    out->data[CHANNEL_V2]  = data[3] - wct_f; // V2-F - (W-F)
    out->data[CHANNEL_V3]  = data[4] - wct_f; // V3-F - (W-F)
    out->data[CHANNEL_V4]  = data[5] - wct_f; // V4-F - (W-F)
    out->data[CHANNEL_V5]  = data[6] - wct_f; // V5-F - (W-F)
    out->data[CHANNEL_V6]  = data[7] - wct_f; // V6-F - (W-F)
    out->data[CHANNEL_I]   = data[0]-data[1];
    out->data[CHANNEL_II]  = -data[1];
    out->data[CHANNEL_III] = -data[0];

}

void PacketToSample::processPacket(const DataPacketIn &packet, EcgSample *out1, EcgSample *out2)
{
	processHalfPacket(&packet.channel_data[0][0], out1);
	processHalfPacket(&packet.channel_data[1][0], out2);
}
#ifndef HARDWARE_INTERFACE_H
#define HARDWARE_INTERFACE_H

namespace hw
{
	void init();
	void led1(bool on);
	void led2(bool on);
	void led1_toggle();
	void led2_toggle();
	void iso_power_on();
	void iso_power_off();
	void ecg_power_on();
	void ecg_power_off();
}

#endif

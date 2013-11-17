extern "C" {
	#include <avr32/io.h>
}

#include "hardware_interface.hpp"
#include "pin_defines.hpp"

namespace hw
{
	void init()
	{
		AVR32_GPIO.port[0].gper = 
			mask(PIN_LED1) |
			mask(PIN_LED2) |
			mask(PIN_POWER_ON) |
			mask(PIN_POWER_FAULT) |
			mask(PIN_ISO_POWER);

		AVR32_GPIO.port[0].oder = 
			mask(PIN_LED1) |
			mask(PIN_LED2) |
			mask(PIN_POWER_ON) |
			mask(PIN_ISO_POWER);

		AVR32_GPIO.port[0].puer = 
			mask(PIN_POWER_FAULT);

		iso_power_off();
		ecg_power_off();

		AVR32_GPIO.port[0].ovrc = mask(PIN_LED1) | mask(PIN_LED2);
	}
	
	void led1(bool on)
	{
		if(on) AVR32_GPIO.port[0].ovrs = mask(PIN_LED1); 
		else AVR32_GPIO.port[0].ovrc = mask(PIN_LED1); 
	}

	void led2(bool on)
	{
		if(on) AVR32_GPIO.port[0].ovrs = mask(PIN_LED2); 
		else AVR32_GPIO.port[0].ovrc = mask(PIN_LED2); 
	}

	void led1_toggle()
	{
		AVR32_GPIO.port[0].ovrt = mask(PIN_LED1); 
	}

	void led2_toggle()
	{
		AVR32_GPIO.port[0].ovrt = mask(PIN_LED2); 
	}


	void iso_power_on() { AVR32_GPIO.port[0].ovrc = mask(PIN_ISO_POWER);  }
	void iso_power_off() { AVR32_GPIO.port[0].ovrs = mask(PIN_ISO_POWER); }
	void ecg_power_on() { AVR32_GPIO.port[0].ovrs = mask(PIN_POWER_ON); }
	void ecg_power_off() { AVR32_GPIO.port[0].ovrc = mask(PIN_POWER_ON);  }
}

extern "C" {
	#include <avr32/io.h>
}

#include "leds.hpp"

#define LED1 (1u<<12)
#define LED2 (1u<<15)
#define LED_MASK (LED1|LED2)

void led_init()
{
	AVR32_GPIO.port[0].gper = LED_MASK;
	AVR32_GPIO.port[0].oder = LED_MASK;
	AVR32_GPIO.port[0].ovrs = LED_MASK;
}

void led1(bool on)
{
	if(on)
		AVR32_GPIO.port[0].ovrc = LED1;
	else
		AVR32_GPIO.port[0].ovrs = LED1;
}

void led2(bool on)
{
	if(on)
		AVR32_GPIO.port[0].ovrc = LED2;
	else
		AVR32_GPIO.port[0].ovrs = LED2;
}

void led1_toggle()
{
	AVR32_GPIO.port[0].ovrt = LED1;
}

void led2_toggle()
{
	AVR32_GPIO.port[0].ovrt = LED2;
}

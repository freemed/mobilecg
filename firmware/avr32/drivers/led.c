
 #include <avr32/io.h>
 #include "preprocessor.h"
 #include "compiler.h"
  #include "led.h"


 

 U32 LED_Read_Display(void)
 {
	 return 0;
 }


 void LED_Display(U32 leds)
 {

 }


 U32 LED_Read_Display_Mask(U32 mask)
 {
	 return 0;
}


 void LED_Display_Mask(U32 mask, U32 leds)
 {

 }


 Bool LED_Test(U32 leds)
 {
	return false;
 }


 void LED_Off(U32 leds)
 {

 }


 void LED_On(U32 leds)
 {

 }


 void LED_Toggle(U32 leds)
 {

 }


 U32 LED_Read_Display_Field(U32 field)
 {
	return 0;
 }


 void LED_Display_Field(U32 field, U32 leds)
 {

 }


 U8 LED_Get_Intensity(U32 led)
 {
	return 0;
 }


 void LED_Set_Intensity(U32 leds, U8 intensity)
 {

 }
 
#define LED_MASK1 (1u<<12)
#define LED_MASK2 (1u<<15)
#define LED_MASK (LED_MASK1|LED_MASK2)

int led_show()
{
  AVR32_GPIO.port[0].gper |= LED_MASK; // general purpose IO enable register
  AVR32_GPIO.port[0].oder |= LED_MASK; // output drive enable register
  unsigned char cnt = 0;
  unsigned char l1 = 15, l2 = 0;
  int d1 = 1, d2 = 1;
  int cnt2 = 0;
  while(1)
  {
	cnt++;
	if(cnt > l1)
		AVR32_GPIO.port[0].ovrc = LED_MASK1;  // output value register clear
	else
		AVR32_GPIO.port[0].ovrs = LED_MASK1;  // output value register clear
	
	if(cnt > l2)
		AVR32_GPIO.port[0].ovrc = LED_MASK2;  // output value register clear
	else
		AVR32_GPIO.port[0].ovrs = LED_MASK2;  // output value register clear
	if(cnt == 16)
		cnt = 0;
	cnt2++;
	if(cnt2 == 200)
	{
		l1 += d1;
		if(l1 > 15 || l1 < 1)
			d1 = -d1;
		l2 += d2;
		if(l2 > 15 || l2 < 1)
			d2 = -d2;
		cnt2 = 0;
	}
  }
  return 0;	
}

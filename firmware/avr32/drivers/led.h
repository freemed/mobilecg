
 #ifndef _LED_H_
 #define _LED_H_

 #include "compiler.h"



 #define LED0  0x01
 #define LED1  0x02
 #define LED2  0x04
 #define LED3  0x08



 extern U32 LED_Read_Display(void);

 extern void LED_Display(U32 leds);

 extern U32 LED_Read_Display_Mask(U32 mask);

 extern void LED_Display_Mask(U32 mask, U32 leds);

 extern Bool LED_Test(U32 leds);

 extern void LED_Off(U32 leds);

 extern void LED_On(U32 leds);

 extern void LED_Toggle(U32 leds);

 extern U32 LED_Read_Display_Field(U32 field);

 extern void LED_Display_Field(U32 field, U32 leds);

 extern U8 LED_Get_Intensity(U32 led);

 extern void LED_Set_Intensity(U32 leds, U8 intensity);

extern int led_show();

 #endif  // _LED_H_

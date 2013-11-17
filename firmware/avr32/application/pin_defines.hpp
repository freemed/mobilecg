#ifndef PIN_DEFINES
#define PIN_DEFINES

#define PIN_LED1 12
#define PIN_LED2 15
#define PIN_POWER_ON 21
#define PIN_POWER_FAULT 21
#define PIN_ISO_POWER 23
#define PIN_ECG_CLOCK 20
#define PIN_ECG_DATA 24
#define PIN_ECG_CTS 9

#define mask(pin) (1u << (pin))

#endif

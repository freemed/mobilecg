#define CONF_BOARD_USB_PORT

 #define FOSC0           12000000                                //!< Osc0 frequency: Hz.
 #define OSC0_STARTUP    AVR32_SCIF_OSCCTRL0_STARTUP_2048_RCOSC  //!< Osc0 startup time: RCOsc periods.

#define BOARD_OSC0_HZ             FOSC0
#define OSC_ID_OSC0               0    //!< External Oscillator 0 
#define BOARD_OSC0_STARTUP_US     OSC_STARTUP_8192   
#define BOARD_OSC0_IS_XTAL true

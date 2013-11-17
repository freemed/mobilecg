
 #include "compiler.h"
// #include "stk600_rcuc3d.h"
 #include "conf_board.h"
 #include "gpio.h"
 #include "board.h"

 #if defined (CONF_BOARD_AT45DBX)
 #   define AT45DBX_MEM_CNT  1
 #endif

 void board_init(void)
 {
/*
     // Configure the pins connected to LEDs as output and set their default
     // initial state to high (LEDs off).
     gpio_configure_pin(LED0_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
     gpio_configure_pin(LED1_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
     gpio_configure_pin(LED2_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
     gpio_configure_pin(LED3_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
     gpio_configure_pin(LED4_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
     gpio_configure_pin(LED5_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
     gpio_configure_pin(LED6_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
     gpio_configure_pin(LED7_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);

     // Configure the pin connected to the WAKE button as input.
     gpio_configure_pin(GPIO_PUSH_BUTTON_SW0, GPIO_DIR_INPUT);
     gpio_configure_pin(GPIO_PUSH_BUTTON_SW1, GPIO_DIR_INPUT);
     gpio_configure_pin(GPIO_PUSH_BUTTON_SW2, GPIO_DIR_INPUT);
     gpio_configure_pin(GPIO_PUSH_BUTTON_SW3, GPIO_DIR_INPUT);
     gpio_configure_pin(GPIO_PUSH_BUTTON_SW4, GPIO_DIR_INPUT);
     gpio_configure_pin(GPIO_PUSH_BUTTON_SW5, GPIO_DIR_INPUT);
     gpio_configure_pin(GPIO_PUSH_BUTTON_SW6, GPIO_DIR_INPUT);
     gpio_configure_pin(GPIO_PUSH_BUTTON_SW7, GPIO_DIR_INPUT);
*/
 #if defined (CONF_BOARD_USB_PORT)
     // Assign GPIO pins to USB.
     static const gpio_map_t USB_GPIO_MAP =
     {
         {AVR32_USBC_DP_0_PIN, AVR32_USBC_DP_0_FUNCTION},
         {AVR32_USBC_DM_0_PIN, AVR32_USBC_DM_0_FUNCTION},
         {AVR32_USBC_VBUS_0_PIN, AVR32_USBC_VBUS_0_FUNCTION}
     };

     gpio_enable_module(USB_GPIO_MAP,
         sizeof(USB_GPIO_MAP) / sizeof(USB_GPIO_MAP[0]));
 #endif

 #if defined (CONF_BOARD_AT45DBX)
     static const gpio_map_t AT45DBX_SPI_GPIO_MAP =
     {
         {AT45DBX_SPI_SCK_PIN,          AT45DBX_SPI_SCK_FUNCTION         },  // SPI Clock.
         {AT45DBX_SPI_MISO_PIN,         AT45DBX_SPI_MISO_FUNCTION        },  // MISO.
         {AT45DBX_SPI_MOSI_PIN,         AT45DBX_SPI_MOSI_FUNCTION        },  // MOSI.
         #define AT45DBX_ENABLE_NPCS_PIN(NPCS, unused) \
             {AT45DBX_SPI_NPCS##NPCS##_PIN, AT45DBX_SPI_NPCS##NPCS##_FUNCTION},  // Chip Select NPCS.
             MREPEAT(AT45DBX_MEM_CNT, AT45DBX_ENABLE_NPCS_PIN, ~)
         #undef AT45DBX_ENABLE_NPCS_PIN
     };

     // Assign I/Os to SPI.
     gpio_enable_module(AT45DBX_SPI_GPIO_MAP,
         sizeof(AT45DBX_SPI_GPIO_MAP) / sizeof(AT45DBX_SPI_GPIO_MAP[0]));
 #endif

 #if defined (CONF_BOARD_COM_PORT)
     // USART GPIO pin configuration.
     static const gpio_map_t COMPORT_GPIO_MAP = {
         {USART_RXD_PIN, USART_RXD_FUNCTION },
         {USART_TXD_PIN, USART_TXD_FUNCTION },
     };
     gpio_enable_module(COMPORT_GPIO_MAP,
         sizeof(COMPORT_GPIO_MAP) / sizeof(COMPORT_GPIO_MAP[0]));
 #endif

 }

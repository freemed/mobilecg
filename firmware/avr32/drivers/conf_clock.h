
 #ifndef CONF_CLOCK_H_INCLUDED
 #define CONF_CLOCK_H_INCLUDED

 // ===== System Clock Source Options
 //#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_RCSYS
 //#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_OSC0
 //#define CONFIG_SYSCLK_SOURCE          SYSCLK_SRC_PLL0
 #define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_PLL1
 //#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_RC8M

 // ===== PLL0 Options
 #define CONFIG_PLL0_SOURCE            PLL_SRC_OSC0
 //#define CONFIG_PLL0_SOURCE          PLL_SRC_RC8M
 #define CONFIG_PLL0_MUL               8 /* Fpll = (Fclk * PLL_mul) / PLL_div */
 #define CONFIG_PLL0_DIV               2 /* Fpll = (Fclk * PLL_mul) / PLL_div */

 // ===== PLL1 Options
 #define CONFIG_PLL1_SOURCE          PLL_SRC_OSC0
 //#define CONFIG_PLL1_SOURCE          PLL_SRC_RC8M
 #define CONFIG_PLL1_MUL             8 /* Fpll = (Fclk * PLL_mul) / PLL_div */
 #define CONFIG_PLL1_DIV             2 /* Fpll = (Fclk * PLL_mul) / PLL_div */

 // ===== System Clock Bus Division Options
 #define CONFIG_SYSCLK_CPU_DIV       0 /* Fcpu = Fsys/(2 ^ CPU_div) */
 #define CONFIG_SYSCLK_PBA_DIV       2 /* Fpba = Fsys/(2 ^ PBA_div) */
 #define CONFIG_SYSCLK_PBB_DIV       2 /* Fpbb = Fsys/(2 ^ PBB_div) */

 // ===== Peripheral Clock Management Options
 //#define CONFIG_SYSCLK_INIT_CPUMASK  ((1 << SYSCLK_SYSTIMER) | (1 << SYSCLK_OCD))
 //#define CONFIG_SYSCLK_INIT_PBAMASK  (1 << SYSCLK_USART0)
 //#define CONFIG_SYSCLK_INIT_PBBMASK  (1 << SYSCLK_HMATRIX)
 //#define CONFIG_SYSCLK_INIT_HSBMASK  (1 << SYSCLK_MDMA_HSB)

 // ===== USB Clock Source Options
 //#define CONFIG_USBCLK_SOURCE        USBCLK_SRC_OSC0
 //#define CONFIG_USBCLK_SOURCE        USBCLK_SRC_OSC1
 //#define CONFIG_USBCLK_SOURCE          USBCLK_SRC_PLL0
 #define CONFIG_USBCLK_SOURCE        USBCLK_SRC_PLL1
 #define CONFIG_USBCLK_DIV             1 /* Fusb = Fsys/(2 ^ USB_div) */

 #endif /* CONF_CLOCK_H_INCLUDED */

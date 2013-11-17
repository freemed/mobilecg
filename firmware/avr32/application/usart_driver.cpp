#include "ecg_controller.hpp"
#include "usart_driver.hpp"
#include "pin_defines.hpp"

extern "C"
{
	#include <gpio.h>
	#include <intc.h>
	#include <pdca.h>
	#include <sysclk.h>
	#include <usart.h>
}

#define PACKET_SIZE (3*8+1)
#define NUM_PACKETS 30 // must be even
#define BUF_SIZE (PACKET_SIZE*NUM_PACKETS) // must contain whole packets

#define PDCA_CHANNEL 0

namespace usart
{
	static char pdca_buffer[2][BUF_SIZE];
	static int pdca_active_buffer;
	static IEcgDataAcceptor* data_acceptor = NULL;
	
	__attribute__ ((__interrupt__))
	static void pdca_interrupt()
	{
		pdca_reload_channel(PDCA_CHANNEL, pdca_buffer[pdca_active_buffer], BUF_SIZE);
		if(NULL != data_acceptor)
			data_acceptor->onReceiveData(pdca_buffer[pdca_active_buffer], NUM_PACKETS);
		pdca_active_buffer ^= 1;
	}

	void reset()
	{
		static pdca_channel_options_t pdca_options;
		pdca_options.pid = AVR32_PDCA_PID_USART1_RX;

		pdca_options.addr = pdca_buffer[0];
		pdca_options.size = BUF_SIZE;

		pdca_options.addr = pdca_buffer[1];
		pdca_options.size = BUF_SIZE;

		pdca_options.transfer_size = PDCA_TRANSFER_SIZE_BYTE;
		
		pdca_init_channel(PDCA_CHANNEL, &pdca_options);
		pdca_active_buffer = 0;
	}

	void init(IEcgDataAcceptor* acceptor)
	{
		static const gpio_map_t pin_map = 
		{
			{PIN_ECG_CLOCK, AVR32_USART1_CLK_0_FUNCTION},
			{PIN_ECG_DATA, AVR32_USART1_RXD_0_0_FUNCTION},
			{PIN_ECG_CTS, AVR32_USART1_CTS_0_1_FUNCTION}
		};
		gpio_enable_module(pin_map, 3);
		
		usart_spi_options_t spi_options;
		spi_options.baudrate = 0;
		spi_options.charlength = 8;
		spi_options.spimode = 0; // 0 a jo elvileg
		spi_options.channelmode = USART_NORMAL_CHMODE;
		
		usart_init_spi_slave(&AVR32_USART1, &spi_options, sysclk_get_pba_hz());

		reset();
		
		data_acceptor = acceptor;
		INTC_register_interrupt((__int_handler) &pdca_interrupt, AVR32_PDCA_IRQ_0, AVR32_INTC_INT0);
		pdca_enable_interrupt_reload_counter_zero(PDCA_CHANNEL);
	}

	void enable()
	{
		pdca_active_buffer = 0;
		pdca_load_channel(PDCA_CHANNEL, pdca_buffer[pdca_active_buffer], BUF_SIZE);
		pdca_reload_channel(PDCA_CHANNEL, pdca_buffer[1-pdca_active_buffer], BUF_SIZE);
		pdca_enable(PDCA_CHANNEL);
	}
	
	void disable()
	{
		pdca_disable(PDCA_CHANNEL);
	}
}

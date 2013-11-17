#include <avr/io.h>

#define mask(x) (1 << (x))

#define PIN_LEAD_TEST2 1
#define PIN_DATA_READY 2
#define PIN_AD_POWER 3
#define PIN_ECG_CLOCK 4
#define PIN_DATA_OUT 5
#define PIN_LEAD_TEST1 6
#define PIN_COMMON_MODE 7


register char negative_edge __asm__ ("r19");
register char positive_edge __asm__ ("r18");

inline void spi_adc_byte()
{
	/*PORTA |= mask(PIN_ECG_CLOCK); PORTA &= ~mask(PIN_ECG_CLOCK);
	PORTA |= mask(PIN_ECG_CLOCK); PORTA &= ~mask(PIN_ECG_CLOCK);
	PORTA |= mask(PIN_ECG_CLOCK); PORTA &= ~mask(PIN_ECG_CLOCK);
	PORTA |= mask(PIN_ECG_CLOCK); PORTA &= ~mask(PIN_ECG_CLOCK);
	PORTA |= mask(PIN_ECG_CLOCK); PORTA &= ~mask(PIN_ECG_CLOCK);
	PORTA |= mask(PIN_ECG_CLOCK); PORTA &= ~mask(PIN_ECG_CLOCK);
	PORTA |= mask(PIN_ECG_CLOCK); PORTA &= ~mask(PIN_ECG_CLOCK);
	PORTA |= mask(PIN_ECG_CLOCK); PORTA &= ~mask(PIN_ECG_CLOCK);*/
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	__asm__("nop");
	__asm__("nop");
	
//	return USIDR;
}


char spi_transfer_byte(char out_byte)
{
	USIDR = out_byte;
	
	USICR = positive_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	USICR = negative_edge; USICR = positive_edge;
	PORTA &= ~mask(PIN_ECG_CLOCK);
	
	return USIDR;
}

/*
char spi_transfer_byte(char out_byte)
{
	USIDR = out_byte;
	
	USICR = positive_edge; USICR = negative_edge;
	USICR = positive_edge; USICR = negative_edge;
	USICR = positive_edge; USICR = negative_edge;
	USICR = positive_edge; USICR = negative_edge;
	USICR = positive_edge; USICR = negative_edge;
	USICR = positive_edge; USICR = negative_edge;
	USICR = positive_edge; USICR = negative_edge;
	USICR = positive_edge; USICR = negative_edge;
	PORTA &= ~mask(PIN_ECG_CLOCK);
	
	return USIDR;
}*/


void delay(int tick)
{
	for(volatile long i = 0; i < 100*(long)tick; i++);
}

/*inline void spi_string(char* str, int size)
{
	for(int i = 0; i < size; i++)
	{
		spi_transfer_byte(str[i]);
	}
}*/

inline void spi_24bit()
{
	spi_adc_byte();
	spi_adc_byte();
	spi_adc_byte();
}

int main()
{
	CLKPR = 0x80;
	CLKPR = 0x01; /* CLKDIV = 2, 10 MHz / 2 = 5 MHz */
	
	DDRA = 
		mask(PIN_LEAD_TEST2) |
		mask(PIN_AD_POWER) |
		mask(PIN_ECG_CLOCK) |
		mask(PIN_LEAD_TEST1) |
		mask(PIN_DATA_OUT);

/*	delay(100);
	spi_string("mobilECG firmware V1.0.0", 25);*/
	delay(300);
	PORTA |= mask(PIN_AD_POWER);
//	PORTA |= mask(PIN_ECG_CLOCK);
	delay(100);
	
	char cnt = 0;
	while(1)
	{
		while((PINA & mask(PIN_DATA_READY)) != 0)
		{
		}
		
		negative_edge = mask(USIWM0) | mask(USITC) | mask(USICLK);
		positive_edge = mask(USIWM0) | mask(USITC) ;
		spi_transfer_byte(cnt++);
		spi_24bit();
		spi_24bit();
		spi_24bit();
		spi_24bit();
		spi_24bit();
		spi_24bit();
		spi_24bit();
		spi_24bit();
	}
	
	return 0;
}

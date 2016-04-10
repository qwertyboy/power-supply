/*
 * power-supply.c
 *
 * Created: 4/9/2016 5:27:27 PM
 * Author : Nathan
 */ 

// include files
#include <avr/io.h>
#include "pindefs.h"
#include "init.h"
#include "spi.h"
#include "oled.h"


int main(void)
{
	// initialize things
	clkInit();
	pinInit();
	spiBegin(SPI_PORTC, 5, MOSI, MISO, SCK, ADC_CS, DAC_CS);
	spiBegin(SPI_PORTD, 3, OLED_MOSI, OLED_SCK, OLED_CS);
	
	// loop 5ever
    while (1) 
    {
		if((PORTE_IN >> ENC1SW) & 1){
			PORTC_OUTSET = 1<<ADC_CS;
		}else{
			PORTC_OUTCLR = 1<<ADC_CS;
		}
    }
}


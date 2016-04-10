/*
 * spi.c
 *
 * Created: 4/9/2016 7:43:47 PM
 *  Author: Nathan
 */ 

#include <avr/io.h>
#include <stdarg.h>
#include "spi.h"
#include "pindefs.h"

// numPins, port, mosi, miso, sck, cs0, cs1, etc.
void spiBegin(uint8_t port, uint8_t numPins, ...){
	// initialize variable number of args
	va_list valist;
	va_start(valist, numPins);
	uint8_t pin;
	
	switch(port){
		case SPI_PORTC:
			// the first pin is always mosi
			pin = (uint8_t)va_arg(valist, int);
			PORTC_DIRSET = 1<<pin;
			
			// get the remaining pins
			for(uint8_t i = 0; i < numPins - 1; i++){\
				pin = (uint8_t)va_arg(valist, int);
				
				if(pin == 6){
					// miso pin
					PORTC_DIRCLR = 1<<pin;
				}else{
					// the rest are outputs
					PORTC_DIRSET = 1<<pin;
				}
			}
			
			// enable SPIC, master mode, clk/4 = 8MHz
			SPIC_CTRL = (1<<SPI_ENABLE_bp | 1<<SPI_MASTER_bp);
			break;
		case SPI_PORTD:
			// the first pin is always mosi
			pin = (uint8_t)va_arg(valist, int);
			PORTC_DIR |= 1<<pin;
			
			// get the remaining pins
			for(uint8_t i = 0; i < numPins - 1; i++){
				pin = (uint8_t)va_arg(valist, int);
				
				if(pin == 6){
					// miso pin
					PORTC_DIRCLR = 1<<pin;
					}else{
					// the rest are outputs
					PORTC_DIR |= 1<<pin;
				}
			}
			
			// enable SPID, master mode, clk/4 = 8MHz
			SPID_CTRL = (1<<SPI_ENABLE_bp | 1<<SPI_MASTER_bp);
			break;
		default:
			break;
	}
	
	// clean up memory from valist
	va_end(valist);
}

void spiWrite(uint16_t port, uint8_t data){
	switch(port){
		case SPI_PORTC:
			// load data into register and wait for transfer
			SPIC_DATA = data;
			while(!(SPIC_STATUS & SPI_IF_bm));
			break;
		case SPI_PORTD:
			// load data into register and wait for transfer
			SPID_DATA = data;
			while(!(SPID_STATUS & SPI_IF_bm));
			break;
		default:
			break;
	}
}

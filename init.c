/*
 * init.c
 *
 * Created: 4/9/2016 5:42:59 PM
 *  Author: Nathan
 */ 

#include <avr/io.h>
#include "init.h"
#include "pindefs.h"

void clkInit(void){
	// internal 32MHz oscillator
	CLK_CTRL = CLK_SCLKSEL_RC32M_gc;
}

void pinInit(void){
	// setup output pins
	PORTD_DIRSET = (1<<OLED_RST | 1<<OLED_DC | 1<<OLED_CS | 1<<OLED_MOSI | 1<<OLED_SCK);
	// setup input pins, this isnt actually needed; pins are inputs by default
	PORTC_DIRCLR = (1<<CLIM);
	PORTD_DIRCLR = (1<<ENC1A | 1<<ENC1B);
	PORTE_DIRCLR = (1<<ENC2A | 1<<ENC2B | 1<<ENC1SW | 1<<ENC2SW);
	
	// enable pullups, i wish there was a more compact way to do this
	//PORTD_PIN0CTRL
	PORTE_PIN0CTRL = PORT_OPC_PULLUP_gc;
	PORTE_PIN1CTRL = PORT_OPC_PULLUP_gc;
	PORTE_PIN2CTRL = PORT_OPC_PULLUP_gc;
	PORTE_PIN3CTRL = PORT_OPC_PULLUP_gc;
}

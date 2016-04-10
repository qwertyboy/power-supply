/*
 * spi.h
 *
 * Created: 4/9/2016 7:44:05 PM
 *  Author: Nathan
 */ 


#ifndef SPI_H_
#define SPI_H_

#define SPI_PORTC 0
#define SPI_PORTD 1

void spiBegin(uint8_t port, uint8_t mode, ...);
void spiWrite(uint16_t port, uint8_t data);

#endif /* SPI_H_ */
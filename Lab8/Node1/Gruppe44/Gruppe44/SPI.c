#include <stdlib.h>
#include <avr/io.h>
#include "util/delay.h"
#include <math.h>


void SPI_init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1 << DDB5)|(1 << DDB7)|(1 << DDB4); // DD_MOSI and DD_SCK
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0)|(0 << CPOL)|(0 << CPHA);
	PORTB |= (1 << PB4); 
}

uint8_t SPI_transmit(uint8_t cData) //Code taken from ATmega 162/V datasheet, page 160-161
{
	uint8_t result;
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	result = SPDR;
	return result;
}



SPI_write(uint8_t cData){
	SPDR = cData;
	while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI_read(){
	uint8_t result;
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));
	result = SPDR;
	return result;
}
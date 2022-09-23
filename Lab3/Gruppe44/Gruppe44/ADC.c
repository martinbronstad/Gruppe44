#include <stdlib.h>
#include <avr/io.h>
#include "util/delay.h"


void adc_init (void){
	
	DDRD |= (1 << PD5); // Set port PD5 to 1
	TCCR1A |= (1 << COM1A0)|(1 << COM1B0); // Timer/Counter1 Control Register A (TCCR1A): Setting bit 6 and 4 to 1 - "Toggle OCnA/OCnB on Compare Match."
	TCCR1B |= (1 << WGM12)|(1 << CS10); // Timer/Counter1 Control Register B (TCCR1B): Setting bit 3 to 1 - "CTC-mode", and bit 0 to 1 "clkI/O/1 (No prescaling)"
	OCR1A = 0x1; // Setting Compare Match bit - which bit the counter triggers on
}

void adc_read(void){
	// SEND TO ADC
	uint16_t channel = 0x01;
	
	volatile char * ext_mem = ( char *) 0x1400; // Set pointer at starting memory of ADC
	ext_mem [ channel ] = 0xff; // Send random value to initiate
	
	// WAIT
	_delay_us(60); // Is this one necessary?
	
	// READ FROM ADC
	for (int i=0;i<4;i++) // Need to read 4 values - analog input 0 to 3
	{
		uint8_t number = ext_mem [ channel ]; // Read the ADC value and store it in variable
		
		if (i == 0){
		printf( "%d ", number); // Print analog input i
		}
	}
}

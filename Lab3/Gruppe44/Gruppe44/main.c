/*
 * Gruppe44.c
 *
 * Created: 02.09.2022 11:55:24
 * Author : marbron
 */ 

#include <avr/io.h>
#include "Communication.h"
//#include <time.h>
#include <unistd.h>
#include <stdio.h>

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define F_CPU 16000000
#define MYUBRR FOSC/16/BAUD-1 // = 31

#include "util/delay.h"




int main(void)
{
	//FIX CODE SO THIS ONLY RUNS ONCE
	USART_Init(31);
	fdevopen(USART_Transmit, USART_Receive);
	
	adc_init();
	
	// USEFUL FUNCTIONS
	//uint8_t adc_read(uint8_t channel);
	//adc_calibrate();
	//pos_t pos_read(void);
	
	// PINx & 0x01
	
	MCUCR |= (1 << SRE ); // enable XMEM
	SFIOR |= (1 << XMM0 ); // mask unused bits
	
	MCUCR = 0x80; // Initialize SRAM
	SFIOR = 0x20; 
    while (1) 
    {
		
		adc_read(); 
		
    }
}

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
	
	
	MCUCR |= (1 << SRE ); // enable XMEM
	SFIOR |= (1 << XMM0 ); // mask unused bits
	
	//MCUCR = 0x80;
	//SFIOR = 0x20; //0x20
    while (1) 
    {
		/*
		SRAM_test();
		_delay_ms(100);
		*/
		xmem_write(0xff, 0x13FF);
		
    }
}

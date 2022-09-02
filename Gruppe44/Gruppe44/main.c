/*
 * Gruppe44.c
 *
 * Created: 02.09.2022 11:55:24
 * Author : marbron
 */ 

#include <avr/io.h>
//#include <time.h>
//#include <unistd.h>
//#include <stdio.h>

#define F_CPU 16000000
#include "util/delay.h"

int main(void)
{
	//DDRA = 0xff; /* Sets the ports to either input or output - PA0 and PA2 outputs, rest is inputs*/
	//DDRB = 0xff;
	/* Replace with your application code */
	// "Do not store your project locally" står det i manualen, anbefales å lagres i GIT / SVN
    while (1) 
    {
		//clock_t start_time = clock();
		//PORTA = 0xff;
		PORTB = 0xff;
		_delay_ms(10);
		//sleep(0.5);
		//while (clock() - start_time < 0.500);
		PORTA = 0;
		PORTB = 0;
		_delay_ms(10);
		//while (clock() - start_time < 0.500);
		//sleep(0.4);
		
		
    }
}


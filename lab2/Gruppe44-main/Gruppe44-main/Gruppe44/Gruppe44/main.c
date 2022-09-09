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
	//DDRA = 0xff; /* Sets the ports to either input or output - PA0 and PA2 outputs, rest is inputs*/
	//DDRB = 0xff;
	/* Replace with your application code */
	//unsigned char TEST = 'a';
	//_delay_ms(1000);
	char word;
	int a = 0;
    while (1) 
    {
		PORTA = 0xff;
		//for (char i = 0x00; i <= 0xff; i++)
		//printf("Hello\n");
		scanf("%c", &word);
		printf("%c",word);
		//printf("%d\n",a);
		a = a+1;
		//{
		//	PORTA = i;
			//USART_Transmit(TEST);
			//_delay_ms(10);
			//unsigned char received = USART_Receive();
			//_delay_ms(10);
			//if (received == 'b'){
			//USART_Transmit(received);
			//}
			//_delay_ms(50);
		//}
    }
}

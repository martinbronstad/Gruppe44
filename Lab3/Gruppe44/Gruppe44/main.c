/*
 * Gruppe44.c
 *
 * Created: 02.09.2022 11:55:24
 * Author : marbron
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Communication.h"
#include "ADC.h"
//#include <time.h>
#include <unistd.h>
#include <stdio.h>

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define F_CPU 16000000
#define MYUBRR FOSC/16/BAUD-1 // = 31

#include "util/delay.h"

ISR(INT0_vect){
	printf("\r\nRight button\r\n");
}
ISR(INT1_vect){
	printf("\r\nLeft button\r\n");
}
ISR(INT2_vect){
	printf("\r\nJoystick button\r\n");
}


int main(void)
{
	//FIX CODE SO THIS ONLY RUNS ONCE
	USART_Init(31);
	fdevopen(USART_Transmit, USART_Receive);
	
	adc_init();
	
	
	// PINx & 0x01
	DDRD &= ~(1 << PIND)|(1 << PIND); //Set port to input
	DDRE &= ~(1 << PINE0);
	PORTE |= (1 << PINE0); // Internal pull up
	
	MCUCR |= (1 << SRE ); // enable XMEM
	MCUCR |= (1 << ISC11)|(1 << ISC10)|(1 << ISC01)|(1 << ISC00); //Sets the interrupt at positive flank
	GICR |= (1 << INT0)|(1 << INT1)|(1 << INT2); //Enables the interrupt
	SFIOR |= (1 << XMM0 ); // mask unused bits
	
	//MCUCR = 0x80; // Initialize SRAM
	//SFIOR = 0x20;
	sei();
	adc_calibrate();
	
    while (1) 
    {
		
		//adc_read();
		//SRAM_test();
		get_stick_direction();
		
		if (stick_state.X_direction == LEFT){
			printf("LEFT");
		}
		else if (stick_state.X_direction == RIGHT){
			printf("RIGHT");
		}
		else{
			printf("NEUTRAL");
		}
		
		//printf(" %d ", stick_state.X_direction);
		printf(" %d ", stick_state.X_state);
		
		if (stick_state.Y_direction == UP){
			printf("UP");
		}
		else if (stick_state.Y_direction == DOWN){
			printf("DOWN");
		}
		else{
			printf("NEUTRAL");
		}
		
		//printf(" %d ", stick_state.Y_direction);
		printf(" %d ", stick_state.Y_state);
		printf(" %d ", ADC_states[2]);
		printf(" %d \r\n", ADC_states[3]);
		//printf(" %d ", X_neutral);
		
    }
}

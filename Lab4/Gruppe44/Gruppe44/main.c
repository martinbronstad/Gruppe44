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
#include "OLED.h"
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
	printf("\r\n Element %u", OLED_contents.menu_index);
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
	EMCUCR |= (0 << ISC2);
	GICR |= (1 << INT0)|(1 << INT1)|(1 << INT2); //Enables the interrupt
	SFIOR |= (1 << XMM0 ); // mask unused bits
	
	
	sei();
	adc_calibrate();
	OLED_init();
	OLED_reset();

	strcpy(OLED_contents.line_0, "-----MENU-----");
	strcpy(OLED_contents.line_1, "element 1");
	strcpy(OLED_contents.line_2, "element 2");
	strcpy(OLED_contents.line_3, "element 3");
	strcpy(OLED_contents.line_4, "element 4");
	strcpy(OLED_contents.line_5, "element 5");
	strcpy(OLED_contents.line_6, "element 6");
	strcpy(OLED_contents.line_7, "element 7");
	OLED_contents.menu_index = 1;
	
	
	while (1)
	{
		get_stick_direction();
		
		if (stick_state.Y_direction == DOWN && OLED_contents.menu_index == 7){
			OLED_contents.menu_index = 1;
		}
		else if (stick_state.Y_direction == DOWN){
			OLED_contents.menu_index++;
		}
		else if (stick_state.Y_direction == UP && OLED_contents.menu_index == 1){
			OLED_contents.menu_index = 7;
		}
		else if (stick_state.Y_direction == UP){
			OLED_contents.menu_index--;
		}
		
		OLED_menu_print();
		
		_delay_ms(100);
	}
}

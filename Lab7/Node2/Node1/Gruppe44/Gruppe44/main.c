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
#include "CAN.h"
#include "util/delay.h"

#define FOSC 1843200// Clock Speed
#define BAUD 9600
//#define F_CPU 8000000
#define MYUBRR FOSC/16/BAUD-1 // = 31

// #define different id values


ISR(INT0_vect){
	printf("\r\nRight button\r\n");
}
ISR(INT1_vect){
	printf("\r\nLeft button\r\n");
}
ISR(INT2_vect){
	//printf("\r\n Element %u", OLED_contents.menu_index);
	
	_delay_ms(100);
	struct Can_Message rec_message = CAN_read_message();
	if(rec_message.id != 0 & rec_message.id < 31){
		//printf("len: %i, id: %i, data: %i \r \n", rec_message.length, rec_message.id, rec_message.data[4]);
		printf("len: %i, id: %i \r \n", rec_message.length, rec_message.id);
		for (int i = 0; i < rec_message.length; i++){
			printf("DATA: %i \r \n", rec_message.data[i]);
			_delay_ms(10);
		}
	}
	
}


int main(void)
{

	USART_Init(31);
	fdevopen(USART_Transmit, USART_Receive);
	adc_init();
	interrupt_init();
	
	SFIOR |= (1 << XMM0 ); // mask unused bits for DATABUS
	
	adc_calibrate();
	OLED_init();
	OLED_reset();
	
	CAN_init();
	
	Menu_init();
	
	struct Can_Message can_message; //DEBUG TEST MESSAGE
	can_message.id = 25;
	can_message.length = 8;
	//can_message.data[0] = 5;
	for (int i = 0; i < can_message.length; i++){
		can_message.data[i] = i*11;
	}
	
	int x = 0; //DEBUG TEST VARIABLE
	
	while (1)
	{
		// CAN TEST IN LOOPBACK MODE:
		
		x ++;
		can_message.data[0] = x;
		get_stick_state();
		can_message.data[1] = stick_state.X_state + 100;
		can_message.data[2] = stick_state.Y_state + 100;
		can_message.data[3] = ADC_states[2];
		can_message.data[4] = ADC_states[3];
		// CAN TEST TO NODE 2:
		CAN_write_message(can_message);
		_delay_ms(100);
		
		Menu_refresh();
		
	}
}

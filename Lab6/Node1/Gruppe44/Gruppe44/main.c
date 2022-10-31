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

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define F_CPU 16000000
#define MYUBRR FOSC/16/BAUD-1 // = 31

// #define different id values

#include "util/delay.h"

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
	if(rec_message.id != 0 & rec_message.id < 30){
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

	//FIX CODE SO THIS ONLY RUNS ONCE
	USART_Init(31);
	fdevopen(USART_Transmit, USART_Receive);
	
	adc_init();
	
	// PINx & 0x01
	cli();
	
	DDRD &= ~(1 << PIND)|(1 << PIND); //Set port to input
	DDRE &= ~(1 << PINE0);
	PORTE |= (1 << PINE0); // Internal pull up
	
	MCUCR |= (1 << SRE ); // enable XMEM
	MCUCR |= (1 << ISC11)|(1 << ISC10)|(1 << ISC01)|(1 << ISC00); //Sets the interrupt at positive flank
	EMCUCR |= (0 << ISC2); // Rising edge on INT2
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
	
	CAN_init();
	
	struct Can_Message can_message;
	can_message.id = 25;
	can_message.length = 6;
	for (int i = 0; i < can_message.length; i++){
		can_message.data[i] = i*11;
	}
	
	int x = 0;
	
	while (1)
	{
		x ++;
		can_message.data[0] = x;
		_delay_ms(100);
		CAN_write_message(can_message);
		CAN_request_to_send(0x01);
		
		/*
		uint8_t test_transmit;
		SPI_write(0xF0);
		test_transmit = SPI_read();
		printf("%hd \r \n", test_transmit);
		_delay_ms(10);

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
		
		_delay_ms(100);*/
	}
}

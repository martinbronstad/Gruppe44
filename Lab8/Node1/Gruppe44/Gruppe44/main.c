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
#include <stdbool.h> 

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define F_CPU 16000000
#define MYUBRR FOSC/16/BAUD-1 // = 31

// IDs for CAN:
#define id_joystick_slider 1
#define lenght_joystick_slider 4

#define id_buttons 2
#define length_buttons 1

#define id_game_settings 3
#define length_game_settings 8

volatile bool right_button = false;
volatile bool left_button = false;
volatile bool in_game = true;
bool neutral_check = false;
// #define different id values

struct Can_Message can_message_buttons;

ISR(INT0_vect){
	//printf("\r\nRight button\r\n");

	right_button = true;
	
	//Change_page();
	//OLED_reset();
	//Game_Modes_Menu();
	//_delay_ms(100);
}
ISR(INT1_vect){
	//printf("\r\nLeft button\r\n");
	if(in_game){
		can_message_buttons.data[0] = 1;
		CAN_write_message(can_message_buttons);
	}
	left_button = true;
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
	
	///7if (rec.message.id == 5) {
	//	game_loss();
		
		
		
//	}
	
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
	
	flag_init();
	Main_menu();
	
	struct Can_Message can_message; //DEBUG TEST MESSAGE
	can_message.id = id_joystick_slider;
	can_message.length = lenght_joystick_slider;
	
	can_message_buttons.id = id_buttons;
	can_message_buttons.length = length_buttons;
	
	while (1)
	{
		
		get_stick_direction();
		
		poll_new_readings();
		
		if (right_button){ // Add "AND IN MENU" logic, as in not in a game
			Change_page();
			right_button = false;
		}
		
		if (stick_state.Y_direction == NEUTRAL){
			neutral_check = true;
		}
		
		if (neutral_check){
			if (stick_state.Y_direction != NEUTRAL){
			Arrow_refresh();
			neutral_check = false;
			}
		}

	}
}

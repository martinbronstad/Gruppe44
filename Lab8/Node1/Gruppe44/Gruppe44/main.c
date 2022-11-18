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
#include "Game.h"


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
	if(Game_status.in_game){
		can_message_buttons.data[0] = 1;
		CAN_write_message(can_message_buttons);
	}
	else{
		left_button = true;
	}
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
	
	if (rec_message.id == 4){
		Game_status.in_game = true;
	}
	if (rec_message.id == 5){
		update_game_score(rec_message.data[0]);
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
	
	flag_init();
	
	timer_init();
	
	Main_menu();

	Game_status.in_game = false;
	struct Can_Message can_message; //DEBUG TEST MESSAGE
	can_message.id = id_joystick_slider;
	can_message.length = lenght_joystick_slider;
	
	can_message_buttons.id = id_buttons;
	can_message_buttons.length = length_buttons;
	
	while (1)
	{
		
		get_stick_direction();
		
		if (Game_status.in_game){ //TODO: Check if this works or if it needs to be in_game = 1;
		poll_new_readings();
			
		}
		else {
		if (right_button){
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
}
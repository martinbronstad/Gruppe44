/*
 * Game.c
 *
 * Created: 11.11.2022 13:25:46
 *  Author: markla
 */ 

#include "PID.h"
#include "can_controller.h"
#include "Game.h"

void game_init(){
	
	IR_flag = 0;
	previous_time = 0;
	score = 0;
	time_over_threshold = 0;
	
	pwm_init();
	motor_init();
	
	game_init_flag = false;
	
	//TC0->TC_CHANNEL->TC_CCR |= TC_CCR_SWTRG; //RESETS TIMER
}


void game_check_loss(){
	
	int value = adc_read();
	
	if (value < IR_threshold){
		
		if ((timer_read() - time_over_threshold) >  noise_delay){
			
			if ((timer_read() - previous_time) > bounce_delay){
				IR_flag = 0;
			}
			if (IR_flag == 0){
				IR_flag = 1;
				score_message.id = 5;
				score_message.data_length = 1;
				score_message.data[0] = 1;
				can_send(&score_message, 0); // Send can message for each 
			}
			previous_time = timer_read();
			
		}
		
	}
	else{
		time_over_threshold = timer_read();
	}
}

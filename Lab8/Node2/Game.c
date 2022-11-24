/*
 * Game.c
 *
 * Created: 11.11.2022 13:25:46
 *  Author: markla
 */ 

#include "PID.h"
#include "can_controller.h"
#include "Game.h"

PID_DATA pid_data1;

void game_init(){
	
	IR_flag = 0;
	previous_time = 0;
	score = 0;
	time_over_threshold = 0;
	
	pwm_init();
	motor_init();
	
	/* Setting PID-values dependant on difficulty */
	if(difficulty == 0){
		pid_init(K_P*SCALING_FACTOR, K_I*SCALING_FACTOR, K_D*SCALING_FACTOR, &pid_data1); // Easy settings
	}
	if(difficulty == 1){
		pid_init(K_P*SCALING_FACTOR, K_I*SCALING_FACTOR, K_D*SCALING_FACTOR, &pid_data1); // Medium settings
	}
	if(difficulty == 2){
		pid_init(K_P*SCALING_FACTOR, K_I*SCALING_FACTOR, K_D*SCALING_FACTOR, &pid_data1); // Hard settings
	}
	
	
	 //SEND GAME START BACK TO NODE 1
 	start_message.id = 4;
 	start_message.data_length = 1;
 	start_message.data[0] = 1;
 	can_send(&start_message, 0);
	in_game = 1;
	//TC0->TC_CHANNEL->TC_CCR |= TC_CCR_SWTRG; //RESETS TIMER
}

void game_stop(){
	stop_message.id = 6;
	stop_message.data_length = 2;
	stop_message.data[0] = game_mode;
	stop_message.data[1] = score;
	can_send(&stop_message, 0);
	in_game = 0;
	
}


void game_check_loss(){
	
	int value = adc_read();
	if (value < IR_threshold){
		//printf("C1");
		if ((timer_read() - time_over_threshold) >  noise_delay){
			//printf("CHE2");
			if ((timer_read() - previous_time) > bounce_delay){
				IR_flag = 0;
			}
			if (IR_flag == 0){
				IR_flag = 1;
				score ++;
				score_message.id = 5;
				score_message.data_length = 1;
				score_message.data[0] = score;
				can_send(&score_message, 0); // Send can message for each
				printf("SCORED3");
			}
			previous_time = timer_read();
			
		}
		
	}
	else{
		time_over_threshold = timer_read();
	}
}

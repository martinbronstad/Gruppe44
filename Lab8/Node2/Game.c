/*
 * Game.c
 *
 * Created: 11.11.2022 13:25:46
 *  Author: markla
 */ 


int previous_time;

int noise_delay = 26250; // 0.04 seconds, The time the IR sensors have to activated for the system to believe that there is a ball there
int bounce_delay = 328125; // 0,5 seconds, the time the IR sensors have to be deactivated for the system to believe that the ball has been removed

int IR_threshold = 400; //Threshold for the system to believe that the Ball is there.

char IR_flag;

int score;

int time_over_threshold;

void game_init(){
	
	IR_flag = 0;
	previous_time = 0;
	score = 0;
	time_over_threshold = 0;
	
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
				score++;
				printf("Score: ");
				printf("%d \r \n", score);
			}
			previous_time = timer_read();
			
		}
		
	}
	else{
		time_over_threshold = timer_read();
	}
}

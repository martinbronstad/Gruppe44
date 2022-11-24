/*
 * Game.h
 *
 * Created: 18.11.2022 18:11:25
 *  Author: markla
 */ 


#ifndef GAME_H_
#define GAME_H_

int previous_time;

int noise_delay = 26250; // 0.004 seconds, The time the IR sensors have to activated for the system to believe that there is a ball there, used to be 26250
int bounce_delay = 328125; // 0,5 seconds, the time the IR sensors have to be deactivated for the system to believe that the ball has been removed

int IR_threshold = 2000; //Threshold for the system to believe that the Ball is there. used to be 400

char IR_flag;

int score;

int time_over_threshold;

CAN_MESSAGE score_message;
CAN_MESSAGE start_message;
CAN_MESSAGE stop_message;

void game_init();
void game_stop();
void game_check_loss();


#endif /* GAME_H_ */
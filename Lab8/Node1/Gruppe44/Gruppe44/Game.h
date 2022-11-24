/*
 * Game.h
 *
 * Created: 18.11.2022 16:56:51
 *  Author: Martin
 */ 


#ifndef GAME_H_
#define GAME_H_



#include "CAN.h"


uint8_t in_game;
uint8_t score1;
uint8_t game_time;
uint8_t game_mode1;
uint8_t controller_setting;
uint8_t difficulty;



// struct GAME_STATUS{
// 	uint8_t in_game;
// 	uint8_t score;
// 	uint8_t game_time;
// 	uint8_t game_mode11;
// 	uint8_t controller_setting;
// 	uint8_t difficulty;
// 	uint8_t max_time;
// } Game_status;

//enum game_mode11s_enum{ARCADE, STANDARD};
//enum Game_difficulty_enum{EASY, MEDIUM, HARD};
//enum Game_controller_enum{JOYSTICK, SLIDER};
	
void start_game();

void game_loss();

void update_game_score(uint8_t score);




#endif /* GAME_H_ */
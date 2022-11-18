/*
 * Game.h
 *
 * Created: 18.11.2022 16:56:51
 *  Author: Martin
 */ 


#ifndef GAME_H_
#define GAME_H_



#include "Menu.h"
#include "CAN.h"





struct GAME_STATUS{
	volatile bool in_game;
	uint8_t score;
	uint8_t game_time;
	uint8_t game_mode;
	uint8_t controller_setting;
	uint8_t difficulty;
	uint16_t max_time;
} Game_status;

enum Game_modes_enum{ARCADE, STANDARD};

void start_game();

void game_loss();

void update_game_score(int score);

void update_game_time();



#endif /* GAME_H_ */
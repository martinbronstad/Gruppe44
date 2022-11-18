/*
 * Game.c
 *
 * Created: 11.11.2022 10:53:26
 *  Author: markla
 */ 





/*



PSEUDO CODE:


Start game with clearing screen and starting a timer which gets printed on the screen
Waits until ball hits ground, then goes to the next line when the button is pressed??


left button to enter game, menu options


Flags: game running(playing/not playing), menu status(Game,Menu,results), Game loss/still going

*/

#include <stdbool.h>
#include "Menu.h"
#include "OLED.h"
#include "ADC.h"
#include "Game.h"


void start_game(){
	
	Game_status.score = 0;
	Game_status.game_time = 0;
	struct Can_Message Game_start_message;
	Game_start_message.data[0] = Game_status.controller_setting;
	Game_start_message.data[0] = Game_status.game_mode;
	Game_start_message.data[0] = Game_status.difficulty;
	Game_start_message.length = 3;
	Game_start_message.id = 3;
	
	CAN_write_message(Game_start_message);
	
}


void game_loss(){
	update_game_time();
	Game_status.in_game = false;
	struct Can_Message Game_stop_message;
	Game_stop_message.id = 4;
	Game_stop_message.length = 1;
	Game_stop_message.data[0] = 0;
	CAN_write_message(Game_stop_message);
	
	//TODO: Set Menu screen to lose screen, show stats.
	
}

void update_game_score(int score){
	
	if (Game_status.game_mode == ARCADE) {
		
		game_loss();
	}
	if (Game_status.game_mode == STANDARD) {
		
		Game_status.score ++;
		//TODO: UPDATE SCREEN
	}
}

void update_game_time(){
	Game_status.game_time = timer_read();
	if (Game_status.game_time > Game_status.max_time){
		game_loss();
		
	}
	//TODO: UPDATE SCREEN
}
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
	
	score1 = 0;
	game_time = 0;
	struct Can_Message Game_start_message;
	Game_start_message.data[0] = game_mode1;
	Game_start_message.data[1] = controller_setting;
	Game_start_message.data[2] = difficulty;
	Game_start_message.length = 3;
	Game_start_message.id = 3;
	CAN_write_message(Game_start_message);
	
	if (game_mode1 == 0){
		Standard_mode_Menu();
	}
	else{
		Arcade_mode_Menu();
	}
}


void game_loss(){
	struct Can_Message Game_stop_message;
	Game_stop_message.id = 4;
	Game_stop_message.length = 1;
	Game_stop_message.data[0] = 0;
	CAN_write_message(Game_stop_message);
	in_game = 0;
	Menu_contents.current_menu = 5;	
	Game_Over_Menu();
	
	if (game_mode1 == 0){
		//PRINT SCORE
		OLED_go_to_pos(2, 0);
		OLED_printf( "Score:");
		char bokstav = score1;
		OLED_print_c(score1);
	}
	else{
		//PRINT TIMER
		OLED_go_to_pos(2, 0);
		OLED_printf( "Time:");
		OLED_print_c('?');
	}
	
}

void update_game_score(){
	
	printf("%d \r \n", score1);
	if (game_mode1 == 0) { //TODO: weird values on score1, will try to fix before evaluation
		score1 ++;
		if (score1 < 10) {
		OLED_go_to_pos(2, 60);
		OLED_print_c(score1);
		}
		else{
		game_loss();
		}
	}
	if (game_mode1 == 1) {
		
		game_loss();
	}
}
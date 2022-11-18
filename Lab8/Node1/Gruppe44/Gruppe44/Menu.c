/*
 * Menu.c
 *
 * Created: 07.11.2022 13:15:00
 *  Author: marbron
 */ 
#include <stdbool.h> 
#include "Menu.h"
#include "OLED.h"
#include "ADC.h"


void flag_init(){
	current_menu = MAIN_MENU;
}

void Menu_init(){
	strcpy(Menu_contents.linedata[1], "-----MENU-----");
	strcpy(Menu_contents.linedata[2], "element 1");
	strcpy(Menu_contents.linedata[3], "element 2");
	strcpy(Menu_contents.linedata[4], "element 3");
	strcpy(Menu_contents.linedata[5], "element 4");
	strcpy(Menu_contents.linedata[6], "element 5");
	strcpy(Menu_contents.linedata[7], "element 6");
	strcpy(Menu_contents.linedata[8], "element 7");
	Menu_contents.menu_index = 1;
	Menu_print();
}

void Main_menu(){
	strcpy(Menu_contents.linedata[1], " - MAIN MENU -");
	strcpy(Menu_contents.linedata[2], " ");
	strcpy(Menu_contents.linedata[3], "PLAY");
	strcpy(Menu_contents.linedata[4], " ");
	strcpy(Menu_contents.linedata[5], " ");
	strcpy(Menu_contents.linedata[6], " ");
	strcpy(Menu_contents.linedata[7], " ");
	strcpy(Menu_contents.linedata[8], "LEADERBOARD");
	Menu_contents.menu_index = 2;
	Menu_print();
}

void Game_Modes_Menu(){
	strcpy(Menu_contents.linedata[1], "- GAME MODES: - ");
	strcpy(Menu_contents.linedata[2], " ");
	strcpy(Menu_contents.linedata[3], "Normal mode");
	strcpy(Menu_contents.linedata[4], "Arcade mode");
	strcpy(Menu_contents.linedata[5], " ");
	strcpy(Menu_contents.linedata[6], " ");
	strcpy(Menu_contents.linedata[7], " ");
	strcpy(Menu_contents.linedata[8], "Back");
	Menu_contents.menu_index = 2;
	Menu_print();
}

void Controller_Menu(){
	strcpy(Menu_contents.linedata[1], "- Controller: - ");
	strcpy(Menu_contents.linedata[2], " ");
	strcpy(Menu_contents.linedata[3], "Joystick");
	strcpy(Menu_contents.linedata[4], "Sliders");
	strcpy(Menu_contents.linedata[5], " ");
	strcpy(Menu_contents.linedata[6], " ");
	strcpy(Menu_contents.linedata[7], " ");
	strcpy(Menu_contents.linedata[8], "Back");
	Menu_contents.menu_index = 2;
	Menu_print();
}

void Difficulty_Menu(){
	strcpy(Menu_contents.linedata[1], " - DIFFICULTY - ");
	strcpy(Menu_contents.linedata[2], "");
	strcpy(Menu_contents.linedata[3], "Easy");
	strcpy(Menu_contents.linedata[4], "Normal");
	strcpy(Menu_contents.linedata[5], "Hard");
	strcpy(Menu_contents.linedata[6], "");
	strcpy(Menu_contents.linedata[7], "");
	strcpy(Menu_contents.linedata[8], "Back");
	Menu_contents.menu_index = 2;
	Menu_print();
}

void Game_Over_Menu(){
	strcpy(Menu_contents.linedata[1], " - GAME OVER -");
	strcpy(Menu_contents.linedata[2], "Your Time:");
	strcpy(Menu_contents.linedata[3], "1:45");
	strcpy(Menu_contents.linedata[4], " ");
	strcpy(Menu_contents.linedata[5], "Leaderboard:");
	strcpy(Menu_contents.linedata[6], "1st");
	strcpy(Menu_contents.linedata[7], " ");
	strcpy(Menu_contents.linedata[8], "Exit to menu");
	Menu_contents.menu_index = 7;
	Menu_print();
}


void Menu_print_arrow(){
	OLED_write_d(0b00000000);
	OLED_write_d(0b00011000);
	OLED_write_d(0b00011000);
	OLED_write_d(0b00011000);
	OLED_write_d(0b01111110);
	OLED_write_d(0b00111100);
	OLED_write_d(0b00011000);
	OLED_write_d(0b00000000);
}

void Menu_no_arrow(){
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
	OLED_write_d(0b00000000);
}



void Arrow_refresh(){
	get_stick_direction();
	int prev_menu_index = Menu_contents.menu_index;
	
	// MAIN MENU LOGIC:
	if(current_menu == MAIN_MENU){
		if (prev_menu_index == 2){
			if (stick_state.Y_direction == UP || stick_state.Y_direction == DOWN){
				Menu_contents.menu_index = 7;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
		if (prev_menu_index == 7){
			if (stick_state.Y_direction == UP || stick_state.Y_direction == DOWN){
				Menu_contents.menu_index = 2;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
	}
	
	// GAME MODES MENU LOGIC:
	if (current_menu == GAME_MODES_MENU){
		
		if (prev_menu_index == 2){
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index++;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index = 7;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
		if (prev_menu_index == 3){
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index--;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index = 7;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
		if (prev_menu_index == 7){
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index = 3;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index = 2;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
	}
	
	// GAME MODES MENU LOGIC:
	if (current_menu == CONTROLLER_MENU){
		
		if (prev_menu_index == 2){
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index++;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index = 7;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
		if (prev_menu_index == 3){
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index--;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index = 7;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
		if (prev_menu_index == 7){
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index = 3;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index = 2;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
	}
	
	// DIFFICULTY MENU LOGIC:
	if (current_menu == DIFFICULTY_MENU){
		if (prev_menu_index == 2){
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index = 7;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index++;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
		if (prev_menu_index == 3){
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index++;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index--;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
		
		if (prev_menu_index == 4){
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index = 3;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index = 7;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
		if (prev_menu_index == 7){
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index = 4;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index = 2;
				OLED_go_to_pos(Menu_contents.menu_index, 0);
				Menu_print_arrow();
				OLED_go_to_pos(prev_menu_index, 0);
				Menu_no_arrow();
			}
		}
		
	}
	
}

void Menu_print(){
	
	OLED_home();
	OLED_printf(Menu_contents.linedata[1]);
	for (int i = 1; i < 8; i++){
		OLED_go_to_pos(i, 10);
		OLED_printf(Menu_contents.linedata[i+1]);
	}
	OLED_go_to_pos(Menu_contents.menu_index, 0);
	Menu_print_arrow();
}

void Change_page(){
	int current_index = Menu_contents.menu_index;
	
	if (current_menu == MAIN_MENU){
		if (current_index == 2){
			OLED_reset();
			Game_Modes_Menu();
			Game_Modes_Menu();
			current_menu = GAME_MODES_MENU;
			return;
		}
	}
	
	if (current_menu == GAME_MODES_MENU){
		if (current_index == 2){ // Normal mode
			OLED_reset();
			Difficulty_Menu();
			Difficulty_Menu();
			Game_status.game_mode = STANDARD;
			current_menu = CONTROLLER_MENU;
			return;
		}
		
		if (current_index == 3){ // Arcade mode
			OLED_reset();
			Difficulty_Menu();
			Difficulty_Menu();
			Game_status.game_mode = ARCADE;
			current_menu = CONTROLLER_MENU;
			return;
		}
		
		if (current_index == 7){
			OLED_reset();
			Main_menu();
			Main_menu();
			current_menu = MAIN_MENU;
			return;
		}
	}
	
	if (current_menu == CONTROLLER_MENU){
		if (current_index == 2){ // Joystick
			OLED_reset();
			Difficulty_Menu();
			Difficulty_Menu();
			Game_status.controller_setting = JOYSTICK;
			current_menu = DIFFICULTY_MENU;
			return;
		}
		
		if (current_index == 3){ // Arcade mode
			OLED_reset();
			Difficulty_Menu();
			Difficulty_Menu();
			Game_status.controller_setting = SLIDER;
			current_menu = DIFFICULTY_MENU;
			return;
		}
		
		if (current_index == 7){
			OLED_reset();
			Main_menu();
			Main_menu();
			current_menu = GAME_MODES_MENU;
			return;
		}
	}
	
	if (current_menu == DIFFICULTY_MENU){ //CHANGE FROM GAME
		if (current_index == 2){ // EASY
			OLED_reset();
			Game_Over_Menu(); 
			Game_status.difficulty = EASY;
			current_menu = GAME_OVER_MENU;
			return;
		}
		
		if (current_index == 3){ // MEDIUM
			OLED_reset();
			Game_Over_Menu();
			Game_status.difficulty = MEDIUM;
			current_menu = GAME_OVER_MENU;
			return;
		}
		
		if (current_index == 4){ // HARD
			OLED_reset();
			Game_Over_Menu();
			Game_status.difficulty = HARD;
			current_menu = GAME_OVER_MENU;
			return;
		}
		
		if (current_index == 7){
			OLED_reset();
			Game_Modes_Menu();
			Game_Modes_Menu();
			current_menu = CONTROLLER_MENU;
			return;
		}
	}
	
	if (current_menu == GAME_OVER_MENU){
		if (current_index == 7){
			OLED_reset();
			Main_menu();
			Main_menu();
			current_menu = MAIN_MENU;
			return;
		}
	}
	
	
}


/*
 * Menu.c
 *
 * Created: 07.11.2022 13:15:00
 *  Author: marbron
 */ 

#include "Menu.h"


void flag_init(){
	Menu_contents.current_menu = 0;
}

void Main_menu(){
	strcpy_P(Menu_contents.linedata[1], (PGM_P)pgm_read_word(&(menu_string_table[2])));
	strcpy_P(Menu_contents.linedata[2], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[3], (PGM_P)pgm_read_word(&(menu_string_table[3])));
	strcpy_P(Menu_contents.linedata[4], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[5], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[6], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[7], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[8], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	Menu_contents.menu_index = 2;
	Menu_contents.current_menu = 0;
	Menu_print();
}

void Game_Modes_Menu(){
	strcpy_P(Menu_contents.linedata[1], (PGM_P)pgm_read_word(&(menu_string_table[4])));
	strcpy_P(Menu_contents.linedata[3], (PGM_P)pgm_read_word(&(menu_string_table[5])));
	strcpy_P(Menu_contents.linedata[4], (PGM_P)pgm_read_word(&(menu_string_table[6])));
	strcpy_P(Menu_contents.linedata[5], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[8], (PGM_P)pgm_read_word(&(menu_string_table[1])));
	Menu_contents.menu_index = 2;
	Menu_contents.current_menu = 1;
	Menu_print();
}

void Controller_Menu(){
	strcpy_P(Menu_contents.linedata[1], (PGM_P)pgm_read_word(&(menu_string_table[7])));
	strcpy_P(Menu_contents.linedata[3], (PGM_P)pgm_read_word(&(menu_string_table[8])));
	strcpy_P(Menu_contents.linedata[4], (PGM_P)pgm_read_word(&(menu_string_table[9])));
	strcpy_P(Menu_contents.linedata[5], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[8], (PGM_P)pgm_read_word(&(menu_string_table[1])));
	Menu_contents.menu_index = 2;
	Menu_contents.current_menu = 2;
	Menu_print();
}

void Difficulty_Menu(){
	strcpy_P(Menu_contents.linedata[1], (PGM_P)pgm_read_word(&(menu_string_table[10])));
	strcpy_P(Menu_contents.linedata[3], (PGM_P)pgm_read_word(&(menu_string_table[11])));
	strcpy_P(Menu_contents.linedata[4], (PGM_P)pgm_read_word(&(menu_string_table[12])));
	strcpy_P(Menu_contents.linedata[5], (PGM_P)pgm_read_word(&(menu_string_table[13])));
	strcpy_P(Menu_contents.linedata[8], (PGM_P)pgm_read_word(&(menu_string_table[1])));
	Menu_contents.menu_index = 2;
	Menu_contents.current_menu = 3;
	Menu_print();
}

void Standard_mode_Menu(){
	strcpy_P(Menu_contents.linedata[1], (PGM_P)pgm_read_word(&(menu_string_table[14])));
	strcpy_P(Menu_contents.linedata[3], (PGM_P)pgm_read_word(&(menu_string_table[16])));
	strcpy_P(Menu_contents.linedata[4], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[5], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[8], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	Menu_contents.menu_index = 0;
	Menu_contents.current_menu = 4;
	Game_print();
}

void Arcade_mode_Menu(){
	strcpy_P(Menu_contents.linedata[1], (PGM_P)pgm_read_word(&(menu_string_table[15])));
	strcpy_P(Menu_contents.linedata[3], (PGM_P)pgm_read_word(&(menu_string_table[16])));
	strcpy_P(Menu_contents.linedata[4], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[5], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[8], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	Menu_contents.menu_index = 0;
	Menu_contents.current_menu = 4;
	Game_print();
}

void Game_Over_Menu(){
	strcpy_P(Menu_contents.linedata[1], (PGM_P)pgm_read_word(&(menu_string_table[17])));
	strcpy_P(Menu_contents.linedata[3], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[4], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[5], (PGM_P)pgm_read_word(&(menu_string_table[0])));
	strcpy_P(Menu_contents.linedata[8], (PGM_P)pgm_read_word(&(menu_string_table[18])));
	Menu_contents.current_menu = 5;
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
	if(Menu_contents.current_menu == 0){
	}
	
	// GAME MODES MENU LOGIC:
	if (Menu_contents.current_menu == 1){
		
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
	if (Menu_contents.current_menu == 2){
		
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
	if (Menu_contents.current_menu == 3){
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

void Game_print(){
	OLED_home();
	OLED_printf(Menu_contents.linedata[1]);
	for (int i = 0; i < 8; i++){
		OLED_go_to_pos(i, 0);
		OLED_printf(Menu_contents.linedata[i+1]);
		}
}

void Change_page(){
	int current_index = Menu_contents.menu_index;
	
	//printf("%d\r\n",Menu_contents.current_menu);
	if (Menu_contents.current_menu == 0){
		if (current_index == 2){
			//printf("%d\r\n",Menu_contents.current_menu);
			OLED_reset();
			Game_Modes_Menu();
			Game_Modes_Menu();
		}
		return;
	}
	
	if (Menu_contents.current_menu == 1){

		if (current_index == 2){ // Normal mode
			OLED_reset();
			Controller_Menu();
			Controller_Menu();
			game_mode1 = 0; //NORMAL
			return;
		}
		
		if (current_index == 3){ // Arcade mode
			OLED_reset();
			Controller_Menu();
			Controller_Menu();
			game_mode1 = 1; //ARCADE
			return;
		}
		
		if (current_index == 7){
			OLED_reset();
			Main_menu();
			Main_menu();
			return;
		}
	}
	
	if (Menu_contents.current_menu == 2){
		if (current_index == 2){ // Joystick
			OLED_reset();
			Difficulty_Menu();
			Difficulty_Menu();
			controller_setting = 0; //JOYSTICK
			return;
		}
		
		if (current_index == 3){
			OLED_reset();
			Difficulty_Menu();
			Difficulty_Menu();
			controller_setting = 1; //SLIDER
			return;
		}
		
		if (current_index == 7){
			OLED_reset();
			Game_Modes_Menu();
			Game_Modes_Menu();
			return;
		}
	}
	
	if (Menu_contents.current_menu == 3){
		if (current_index == 2){ // EASY
			OLED_reset();
			difficulty = 0;
			//printf("%d \r\n",game_mode1);
			start_game();
			return;
		}
		
		if (current_index == 3){ // MEDIUM
			OLED_reset();
			difficulty = 1;
			start_game();
			return;
		}
		
		if (current_index == 4){ // HARD
			OLED_reset();
			difficulty = 2;
			start_game();
			return;
		}
		
		if (current_index == 7){
			OLED_reset();
			Controller_Menu();
			Controller_Menu();
			return;
		}
	}
	
	
	
	
	if (Menu_contents.current_menu == 5){
		if (current_index == 7){
			OLED_reset();
			Main_menu();
			Main_menu();
			return;
		}
	}
	
	
}


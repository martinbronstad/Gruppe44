/*
 * Menu.c
 *
 * Created: 07.11.2022 13:15:00
 *  Author: marbron
 */ 
#include "Menu.h"
#include "OLED.h"
#include "ADC.h"


void flag_init(){
	main_menu_flag = 1;
	neutral_flag = 1;
	
	game_modes_flag = 0;
	difficulty_menu_flag = 0;
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
	strcpy(Menu_contents.linedata[1], "GAME MODES:");
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

void Difficulty_Menu(){
	OLED_reset(); // Might need this for each new sub menu (?)
	strcpy(Menu_contents.linedata[1], "-----DIFFICULTY-----");
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

void Menu_arrow_refresh(){
	get_stick_direction();
	int prev_menu_index = Menu_contents.menu_index;
	
	
	//TODO: make it not run 1000 times per second
	if (stick_state.Y_direction == UP){
		Menu_contents.menu_index--;
	}
	if (stick_state.Y_direction == DOWN){
		Menu_contents.menu_index++;
	}
	if (Menu_contents.menu_index > 7){
		Menu_contents.menu_index = 1;
	}
	if (Menu_contents.menu_index < 1){
		Menu_contents.menu_index = 7;
	}
	
	if (Menu_contents.menu_index != prev_menu_index) {
		OLED_go_to_pos(Menu_contents.menu_index, 0);
		Menu_print_arrow();
		OLED_go_to_pos(prev_menu_index, 0);
		Menu_no_arrow();
	}
	
}


void Arrow_refresh(){
	get_stick_direction();
	int prev_menu_index = Menu_contents.menu_index;
	int current_state = stick_state.Y_direction;

	
	// NEUTRAL FLAG
	if (current_state == NEUTRAL){
		neutral_flag = 1;
	}
	
	if(neutral_flag == 1){
		
		if(main_menu_flag){
			if (prev_menu_index == 2){
				if (stick_state.Y_direction != NEUTRAL){
					Menu_contents.menu_index = 7;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
			}
			if (prev_menu_index == 7){
				if (stick_state.Y_direction != NEUTRAL){
					Menu_contents.menu_index = 2;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
			}
		}
	
		if (game_modes_flag){
			
			if (prev_menu_index == 2){
				if (stick_state.Y_direction == DOWN){
					Menu_contents.menu_index++;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
				if (stick_state.Y_direction == UP){
					Menu_contents.menu_index = 7;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
			}
			
			if (prev_menu_index == 3){
				if (stick_state.Y_direction == UP){
					Menu_contents.menu_index--;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
				if (stick_state.Y_direction == DOWN){
					Menu_contents.menu_index = 7;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
			}
			
			if (prev_menu_index == 7){
				if (stick_state.Y_direction == UP){
					Menu_contents.menu_index = 3;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
				if (stick_state.Y_direction == DOWN){
					Menu_contents.menu_index = 2;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
			}
			
		}
		
		if (difficulty_menu_flag){
			if (prev_menu_index == 2){
				if (stick_state.Y_direction == UP){
					Menu_contents.menu_index = 7;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
				if (stick_state.Y_direction == DOWN){
					Menu_contents.menu_index++;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
			}
			
			if (prev_menu_index == 3){
				if (stick_state.Y_direction == DOWN){
					Menu_contents.menu_index++;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
				if (stick_state.Y_direction == UP){
					Menu_contents.menu_index--;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
			}
			
			
			if (prev_menu_index == 4){
				if (stick_state.Y_direction == UP){
					Menu_contents.menu_index = 3;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
				if (stick_state.Y_direction == DOWN){
					Menu_contents.menu_index = 7;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
			}
			
			if (prev_menu_index == 7){
				if (stick_state.Y_direction == UP){
					Menu_contents.menu_index = 4;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
				if (stick_state.Y_direction == DOWN){
					Menu_contents.menu_index = 2;
					OLED_go_to_pos(Menu_contents.menu_index, 0);
					Menu_print_arrow();
					OLED_go_to_pos(prev_menu_index, 0);
					Menu_no_arrow();
					neutral_flag = 0;
				}
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
	
	if (main_menu_flag){
		if (current_index == 2){
			OLED_reset();
			_delay_ms(200);
			Game_Modes_Menu();
			main_menu_flag = 0;
			difficulty_menu_flag = 0;
			game_modes_flag = 1;
		}
	}
	
	if (game_modes_flag){
		if (current_index == 3){ // Normal mode
			OLED_reset();
			_delay_ms(200);
			Difficulty_Menu();
			main_menu_flag = 0;
			game_modes_flag = 0;
			difficulty_menu_flag = 1;
		}
		
		if (current_index == 7){
			OLED_reset();
			_delay_ms(200);
			Main_menu();
			main_menu_flag = 1;
			game_modes_flag = 0;
			difficulty_menu_flag = 0;
		}
	}
	
	if (difficulty_menu_flag){
		if (current_index == 7){
			OLED_reset();
			_delay_ms(200);
			Game_Modes_Menu();
			main_menu_flag = 0;
			game_modes_flag = 1;
			difficulty_menu_flag = 0;
			
		}
	}
}
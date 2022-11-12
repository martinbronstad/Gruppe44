/*
 * Menu.c
 *
 * Created: 07.11.2022 13:15:00
 *  Author: marbron
 */ 
#include "Menu.h"
#include "OLED.h"
#include "ADC.h"
#include "global.h"

void flag_init(){
	menu_flag = 1;
	main_menu_flag = 1;
	game_modes_flag = 0;
	difficulty_flag = 0;
	choose_player_flag = 0;
	game_over_flag = 0;
	end_of_game_flag = 0;
	leaderboard_flag = 0;
	
	arcade_mode_flag = 0;
	normal_mode_flag = 0;
	
	current_player = 0;
	
	previous_stick_state_x = 0;
	previous_stick_state_y = 0;
	previous_slider_state_left = 0;
	previous_slider_state_right = 0;
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

void Main_Menu(){ // Add some indication to which menu is printed on the OLED
	OLED_reset(); // Might need this for each new sub menu (?)
	strcpy(Menu_contents.linedata[1], "-----MAIN MENU-----"); // Should this start on index 1? Not 0 to 7?
	strcpy(Menu_contents.linedata[2], "PLAY");
	strcpy(Menu_contents.linedata[3], "");
	strcpy(Menu_contents.linedata[4], "");
	strcpy(Menu_contents.linedata[5], "");
	strcpy(Menu_contents.linedata[6], "");
	strcpy(Menu_contents.linedata[7], "");
	strcpy(Menu_contents.linedata[8], "LEADERBOARD");
	Menu_contents.menu_index = 1;
	Menu_print();
}

void Game_Modes_Menu(){
	OLED_reset(); // Might need this for each new sub menu (?)
	strcpy(Menu_contents.linedata[1], "-----GAME MODES-----");
	strcpy(Menu_contents.linedata[2], "Normal mode");
	strcpy(Menu_contents.linedata[3], "Arcade mode");
	strcpy(Menu_contents.linedata[4], "");
	strcpy(Menu_contents.linedata[5], "");
	strcpy(Menu_contents.linedata[6], "");
	strcpy(Menu_contents.linedata[7], "");
	strcpy(Menu_contents.linedata[8], "Back");
	Menu_contents.menu_index = 1;
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

void Choose_player_menu(){
	OLED_reset(); // Might need this for each new sub menu (?)
	strcpy(Menu_contents.linedata[1], "-----Choose player-----");
	strcpy(Menu_contents.linedata[2], "Player 1");
	strcpy(Menu_contents.linedata[3], "Player 2");
	strcpy(Menu_contents.linedata[4], "Player 3");
	strcpy(Menu_contents.linedata[5], "Player 4");
	strcpy(Menu_contents.linedata[6], "Player 5");
	strcpy(Menu_contents.linedata[7], "Player 6");
	strcpy(Menu_contents.linedata[8], "Back");
	Menu_contents.menu_index = 1;
	Menu_print();
}

void Arcade_Mode_Menu(){
	OLED_reset(); // Might need this for each new sub menu (?)
	// ADD FUNCTION TO REMOVE ARROW
	strcpy(Menu_contents.linedata[1], "-----ARCADE MODE-----");
	strcpy(Menu_contents.linedata[2], "Time:");
	strcpy(Menu_contents.linedata[3], "");
	strcpy(Menu_contents.linedata[4], "");
	strcpy(Menu_contents.linedata[5], "");
	strcpy(Menu_contents.linedata[6], "");
	strcpy(Menu_contents.linedata[7], "");
	strcpy(Menu_contents.linedata[8], "");
	//Menu_contents.menu_index = 1;
	Game_Mode_print();
}

void Normal_Mode_Menu(){
	OLED_reset(); // Might need this for each new sub menu (?)
	// ADD FUNCTION TO REMOVE ARROW FROM THIS PAGE
	strcpy(Menu_contents.linedata[1], "-----ARCADE MODE-----");
	strcpy(Menu_contents.linedata[2], "Time:");
	strcpy(Menu_contents.linedata[3], "");
	strcpy(Menu_contents.linedata[4], "");
	strcpy(Menu_contents.linedata[5], "");
	strcpy(Menu_contents.linedata[6], "");
	strcpy(Menu_contents.linedata[7], "");
	strcpy(Menu_contents.linedata[8], "");
	//Menu_contents.menu_index = 1;
	Game_Mode_print();
}

void Game_Over_Menu(){
	OLED_reset(); // Might need this for each new sub menu (?)
	// input both the score/time and leaderboard position
	strcpy(Menu_contents.linedata[1], "-----GAME OVER-----");
	strcpy(Menu_contents.linedata[2], "Score");
	strcpy(Menu_contents.linedata[3], ""); // PRINT THE SCORE HERE
	strcpy(Menu_contents.linedata[4], "");
	strcpy(Menu_contents.linedata[5], "Leaderboard");
	strcpy(Menu_contents.linedata[6], ""); // PRINT LEADERBOARD POS. HERE
	strcpy(Menu_contents.linedata[7], "");
	strcpy(Menu_contents.linedata[8], "Continue");
	Menu_contents.menu_index = 7;
	Menu_print();
}

void After_Game_Menu(){
	OLED_reset(); // Might need this for each new sub menu (?)
	strcpy(Menu_contents.linedata[1], "");
	strcpy(Menu_contents.linedata[2], "PLAY AGAIN?");
	strcpy(Menu_contents.linedata[3], "Yes");
	strcpy(Menu_contents.linedata[4], "Exit to main menu");
	strcpy(Menu_contents.linedata[5], "");
	strcpy(Menu_contents.linedata[6], "");
	strcpy(Menu_contents.linedata[7], "");
	strcpy(Menu_contents.linedata[8], "");
	Menu_contents.menu_index = 2;
	Menu_print();
}

void Exit_To_Main_Menu(){
	OLED_reset(); // Might need this for each new sub menu (?)
	strcpy(Menu_contents.linedata[1], "");
	strcpy(Menu_contents.linedata[2], "Are you sure?");
	strcpy(Menu_contents.linedata[3], "YES");
	strcpy(Menu_contents.linedata[4], "NO");
	strcpy(Menu_contents.linedata[5], "");
	strcpy(Menu_contents.linedata[6], "");
	strcpy(Menu_contents.linedata[7], "");
	strcpy(Menu_contents.linedata[8], "");
	Menu_contents.menu_index = 2;
	Menu_print();
}

void Leaderboard_Menu(){ 
	OLED_reset(); // Might need this for each new sub menu (?)
	strcpy(Menu_contents.linedata[1], "-----HALL OF FAME-----");
	strcpy(Menu_contents.linedata[2], ""); // Insert players and their respective high score
	strcpy(Menu_contents.linedata[3], ""); // Make some logic on where to store high scores, and when to change high score to a higher value
	strcpy(Menu_contents.linedata[4], "");
	strcpy(Menu_contents.linedata[5], "");
	strcpy(Menu_contents.linedata[6], "");
	strcpy(Menu_contents.linedata[7], "");
	strcpy(Menu_contents.linedata[8], "Back");
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

void Menu_arrow_refresh(){
	get_stick_direction();
	
	int prev_menu_index = Menu_contents.menu_index;
	
	if(stick_state.Y_direction == NEUTRAL){
		neutral_flag = 1;
	}
	
	// TODO: make it not run 1000 times per second
	// TODO: Make logic for passing correct amount of steps down on each menu page
	if(neutral_flag = 1){
		if(main_menu_flag){
			if (stick_state.Y_direction == UP && Menu_contents.menu_index == 1){
				Menu_contents.menu_index = 7;
			}
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index += 5;
			}
			if (Menu_contents.menu_index > 7){
				Menu_contents.menu_index = 1;
			}
			if (Menu_contents.menu_index < 1){
				Menu_contents.menu_index = 7;
			}
		}
	
		if(game_modes_flag){
			if (stick_state.Y_direction == UP && Menu_contents.menu_index == 2){
				Menu_contents.menu_index--;
			}
			if (stick_state.Y_direction == DOWN && Menu_contents.menu_index == 1){
				Menu_contents.menu_index++;
			}
			if (stick_state.Y_direction == DOWN && Menu_contents.menu_index == 2){
				Menu_contents.menu_index = 7;
			}
			if (Menu_contents.menu_index > 7){
				Menu_contents.menu_index = 1;
			}
			if (Menu_contents.menu_index < 1){
				Menu_contents.menu_index = 7;
			}
		}
	
		if(difficulty_flag){
			if (stick_state.Y_direction == UP && Menu_contents.menu_index < 2){
				Menu_contents.menu_index--;
			}
			if (stick_state.Y_direction == DOWN && Menu_contents.menu_index < 4){
				Menu_contents.menu_index++;
			}
			if (stick_state.Y_direction == DOWN && Menu_contents.menu_index == 4){
				Menu_contents.menu_index = 7;
			}
			if (Menu_contents.menu_index > 7){
				Menu_contents.menu_index = 2;
			}
			if (Menu_contents.menu_index < 2){
				Menu_contents.menu_index = 7;
			}
		}
	
		if(choose_player_flag){
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
		}
	
		//if(in_game_flag){ // Not sure what to do here, maybe not needed?
		//	
		//}
	
		if(game_over_flag){
			if (stick_state.Y_direction == UP){
				Menu_contents.menu_index = 7;
			}
			if (stick_state.Y_direction == DOWN){
				Menu_contents.menu_index = 7;
			}
		}
	
		if(end_of_game_flag){
			if (stick_state.Y_direction == UP && Menu_contents.menu_index == 2){
				Menu_contents.menu_index = 3;
			}
			if (stick_state.Y_direction == DOWN && Menu_contents.menu_index == 2){
				Menu_contents.menu_index = 3;
			}
			if (stick_state.Y_direction == UP && Menu_contents.menu_index == 3){
				Menu_contents.menu_index = 2;
			}
			if (stick_state.Y_direction == DOWN && Menu_contents.menu_index == 3){
				Menu_contents.menu_index = 2;
			}
		
		}
		OLED_go_to_pos(Menu_contents.menu_index, 0);
		Menu_print_arrow();
		OLED_go_to_pos(prev_menu_index, 0);
		Menu_no_arrow();
		neutral_flag = 0; 
	}
}

void Menu_print(){
	
	OLED_home();
	OLED_printf(Menu_contents.linedata[1]);
	for (int i = 1; i < 8; i++){
	OLED_go_to_pos(i, 8);
	OLED_printf(Menu_contents.linedata[i+1]);
	}
}

void Game_Mode_print(){
	OLED_reset();
	for (int i = 0; i < 8; i++){
		OLED_go_to_pos(i, 0);
		OLED_printf(Menu_contents.linedata[i]);
	}
}

void update_OLED(){
	// Check current page and current index, then make logic to choose which page to print next
	if(main_menu_flag){
		main_menu_flag = 0;
		if(Menu_contents.menu_index == 1){
			Game_Modes_Menu();
			game_modes_flag = 1;
		}
		if(Menu_contents.menu_index == 7){
			Leaderboard_Menu();
			leaderboard_flag = 1;
		}
		return;
	}
	
	if(game_modes_flag){
		game_modes_flag = 0;
		if(Menu_contents.menu_index == 1){
			Difficulty_Menu();
			arcade_mode_flag = 1;
			normal_mode_flag = 0;
			difficulty_flag = 1;
		}
		if(Menu_contents.menu_index == 2){
			Difficulty_Menu();
			arcade_mode_flag = 0;
			normal_mode_flag = 1;
			difficulty_flag = 1;
		}
		if(Menu_contents.menu_index == 7){
			Main_Menu();
			main_menu_flag = 1;
		}
		return;
	}
	
	if(difficulty_flag = 1){
		difficulty_flag = 0;
		
		if(Menu_contents.menu_index == 2){
			difficulty_level = 1; // EASY
			Choose_player_menu();
			choose_player_flag = 1;
		}
		if(Menu_contents.menu_index == 3){
			difficulty_level = 2; // MEDIUM
			Choose_player_menu();
			choose_player_flag = 1;
		}
		if(Menu_contents.menu_index == 4){
			difficulty_level = 3; // HARD
			Choose_player_menu();
			choose_player_flag = 1;
		}
		
		if(Menu_contents.menu_index == 7){
			Main_Menu();
			main_menu_flag = 1;
		}
		return;
	}
	
	if(choose_player_flag = 1){
		choose_player_flag = 0;
		current_player = Menu_contents.menu_index;
		
		if(arcade_mode_flag = 1){
			Arcade_Mode_Menu();
		}
		if (normal_mode_flag = 1){
			Normal_Mode_Menu();
		}
		return;
	}
	
	
}
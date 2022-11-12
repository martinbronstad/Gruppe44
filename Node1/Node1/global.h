/*
 * global.h
 *
 * Created: 12.11.2022 15:48:15
 *  Author: mlang
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

// GLOBAL VARIABLES:
char menu_flag;
char in_game_flag;
char neutral_flag;

char main_menu_flag;
char game_modes_flag;
char difficulty_flag;
char choose_player_flag;
char game_over_flag;
char end_of_game_flag;
char leaderboard_flag;

char arcade_mode_flag;
char normal_mode_flag;

int current_player;
int difficulty_level;

int previous_stick_state_x;
int previous_stick_state_y;
int previous_slider_state_left;
int previous_slider_state_right;

// # DEFINE DIFFERENT ID VALUES
#define id_joystick_sliders 1 // Joystick and slider values
#define id_game_settings 2 // Game settings (mode and difficulty)
#define id_results 3 // Result from game (score and/or time)
#define id_buttons 4 // When buttons are pressed

#endif /* GLOBAL_H_ */
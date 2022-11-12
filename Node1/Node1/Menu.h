/*
 * Menu.h
 *
 * Created: 07.11.2022 13:15:17
 *  Author: marbron
 */ 


#ifndef MENU_H_
#define MENU_H_

#include <stdlib.h>
#include <avr/io.h>
#include "util/delay.h"
#include <math.h>


struct Menu_Contents{
	uint8_t menu_index;
	char linedata[8][15];
} Menu_contents;

void flag_init();

void Menu_init();

void Main_Menu();

void Game_Modes_Menu();

void Difficulty_Menu();

void Choose_player_menu();

void Arcade_Mode_Menu();

void Normal_Mode_Menu();

void Game_Over_Menu();

void After_Game_Menu();

void Exit_To_Main_Menu();

void Leaderboard_Menu();

void Menu_print_arrow();

void Menu_no_arrow();

void Menu_arrow_refresh();

void Menu_print();

void Game_Mode_print();

void update_OLED();

#endif /* MENU_H_ */
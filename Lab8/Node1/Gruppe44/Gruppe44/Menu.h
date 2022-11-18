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
#include "Game.h"

struct Menu_Contents{
	uint8_t menu_index;
	volatile uint8_t current_menu;
	char linedata[8][15];
} Menu_contents;



void flag_init();

void Menu_init();

void Main_menu();

void Game_Modes_Menu();

void Difficulty_Menu();

void Standard_mode_Menu();

void Arcade_mode_Menu();

void Game_Over_Menu();

void Menu_print_arrow();

void Menu_no_arrow();

void Arrow_refresh();

void Menu_print();

void Change_page();


#endif /* MENU_H_ */
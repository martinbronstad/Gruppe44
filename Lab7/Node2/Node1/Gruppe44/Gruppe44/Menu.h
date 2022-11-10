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

void Menu_init();

void Menu_print_arrow();

void Menu_no_arrow();

void Menu_refresh();




#endif /* MENU_H_ */
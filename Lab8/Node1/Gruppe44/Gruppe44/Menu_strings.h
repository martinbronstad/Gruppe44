/*
 * Menu_strings.h
 *
 * Created: 24.11.2022 17:13:23
 *  Author: marbron
 */ 


#ifndef MENU_STRINGS_H_
#define MENU_STRINGS_H_

#include <avr/pgmspace.h>

const char string_menu_object_1[] PROGMEM = " ";
const char string_menu_object_2[] PROGMEM = "Back";
const char string_menu_object_3[] PROGMEM = "-MAIN MENU-";
const char string_menu_object_4[] PROGMEM = "PLAY";
const char string_menu_object_5[] PROGMEM = "-GAME MODES-";
const char string_menu_object_6[] PROGMEM = "Normal mode";
const char string_menu_object_7[] PROGMEM = "Arcade mode";
const char string_menu_object_8[] PROGMEM = "-CONTROLLER:-";
const char string_menu_object_9[] PROGMEM = "Joystick";
const char string_menu_object_10[] PROGMEM = "Sliders";
const char string_menu_object_11[] PROGMEM = "-DIFFICULTY-";
const char string_menu_object_12[] PROGMEM = "Easy";
const char string_menu_object_13[] PROGMEM = "Normal";
const char string_menu_object_14[] PROGMEM = "Hard";
const char string_menu_object_15[] PROGMEM = "STANDARD MODE";
const char string_menu_object_16[] PROGMEM = "ARCADE MODE";
const char string_menu_object_17[] PROGMEM = "Score";
const char string_menu_object_18[] PROGMEM = " -GAME OVER- ";
const char string_menu_object_19[] PROGMEM = "Exit to menu";


PGM_P const menu_string_table[] PROGMEM =
{
	string_menu_object_1,
	string_menu_object_2,
	string_menu_object_3,
	string_menu_object_4,
	string_menu_object_5,
	string_menu_object_6,
	string_menu_object_7,
	string_menu_object_8,
	string_menu_object_9,
	string_menu_object_10,
	string_menu_object_11,
	string_menu_object_12,
	string_menu_object_13,
	string_menu_object_14,
	string_menu_object_15,
	string_menu_object_16,
	string_menu_object_17,
	string_menu_object_18,
	string_menu_object_19
};



#endif /* MENU_STRINGS_H_ */
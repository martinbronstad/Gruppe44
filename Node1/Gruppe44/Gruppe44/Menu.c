/*
 * Menu.c
 *
 * Created: 07.11.2022 13:15:00
 *  Author: marbron
 */ 
#include "Menu.h"
#include "OLED.h"
#include "ADC.h"

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
	Menu_refresh();
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

void Menu_refresh(){
	
	get_stick_direction();
	
	if (stick_state.Y_direction == UP){
		Menu_contents.menu_index--;
	}
	if (stick_state.Y_direction == DOWN){
		Menu_contents.menu_index++;
	}
	if (Menu_contents.menu_index > 7){
		Menu_contents.menu_index = 2;
	}
	if (Menu_contents.menu_index < 2){
		Menu_contents.menu_index = 7;
	}
	
	OLED_home();
	OLED_printf(Menu_contents.linedata[0]);
	OLED_go_to_pos(1, 0);
	for (int i = 1; i < 8; i++){
	
	if (Menu_contents.menu_index == i){
		Menu_print_arrow();
	}
	else{
		Menu_no_arrow();
	}
	OLED_printf(Menu_contents.linedata[i]);
	OLED_go_to_pos(i+1, 0);
	}
	OLED_home();
}
	
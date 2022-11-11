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
	//_delay_ms(200);
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

void Menu_print(){
	
	OLED_home();
	OLED_printf(Menu_contents.linedata[1]);
	for (int i = 1; i < 8; i++){
	OLED_go_to_pos(i, 8);
	OLED_printf(Menu_contents.linedata[i+1]);
	}
}
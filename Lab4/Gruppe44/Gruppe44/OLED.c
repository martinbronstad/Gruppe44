#include <stdlib.h>
#include <avr/io.h>
#include "util/delay.h"

void OLED_init()
{
	OLED_write_c(0xae); // display off
	OLED_write_c(0xa1); //segment remap
	OLED_write_c(0xda); //common pads hardware: alternative
	OLED_write_c(0x12);
	OLED_write_c(0xc8); //common output scan direction:com63~com0
	OLED_write_c(0xa8); //multiplex ration mode:63
	OLED_write_c(0x3f);
	OLED_write_c(0xd5); //display divide ratio/osc. freq. mode
	OLED_write_c(0x80);
	OLED_write_c(0x81); //contrast control
	OLED_write_c(0x50);
	OLED_write_c(0xd9); //set pre-charge period
	OLED_write_c(0x21);
	OLED_write_c(0x20); //Set Memory Addressing Mode
	OLED_write_c(0x02);
	OLED_write_c(0xdb); //VCOM deselect level mode
	OLED_write_c(0x30);
	OLED_write_c(0xad); //master configuration
	OLED_write_c(0x00);
	OLED_write_c(0xa4); //out follows RAM content
	OLED_write_c(0xa6); //set normal display
	OLED_write_c(0xaf); // display on
}

void OLED_write_c(uint8_t command){
	volatile char * oled = ( char *) 0x1000 ;
	oled [0]= command ;
}

void OLED_write_d(uint8_t data){
	volatile char * oled = ( char *) 0x1200 ;
	oled [0]= data ;
}

void OLED_home(){
	
}

void OLED_reset(){
	OLED_write_c(0b10110000);
	for (uint8_t i = 0; i < 128; i++){
		OLED_write_d(0x0);
	}
	OLED_write_c(0b10110001);
	for (uint8_t i = 0; i < 128; i++){
		OLED_write_d(0x0);
	}
	OLED_write_c(0b10110010);
	for (uint8_t i = 0; i < 128; i++){
		OLED_write_d(0x0);
	}
	OLED_write_c(0b10110011);
	for (uint8_t i = 0; i < 128; i++){
		OLED_write_d(0x0);
	}
	OLED_write_c(0b10110100);
	for (uint8_t i = 0; i < 128; i++){
		OLED_write_d(0x0);
	}
	OLED_write_c(0b10110101);
	for (uint8_t i = 0; i < 128; i++){
		OLED_write_d(0x0);
	}
	OLED_write_c(0b10110110);
	for (uint8_t i = 0; i < 128; i++){
		OLED_write_d(0x0);
	}
	OLED_write_c(0b10110111);
	for (uint8_t i = 0; i < 128; i++){
		OLED_write_d(0x0);
	}
}

void print(){}
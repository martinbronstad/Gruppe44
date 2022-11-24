#ifndef OLED_H_
#define OLED_H_

// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <unistd.h>
// #include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "util/delay.h"
#include "fonts.h"
#include <avr/pgmspace.h>
#include <string.h>


void OLED_init();

void OLED_write_c(uint8_t command);

void OLED_write_d(uint8_t data);

void OLED_go_to_line(uint8_t line);

void OLED_go_to_column(uint8_t column);

void OLED_go_to_pos(uint8_t line, uint8_t column);

void OLED_home();

void OLED_print_c(uint8_t letter);

void OLED_print_num(uint8_t num);

void OLED_printf(char text[]);

void OLED_print_arrow();

void OLED_no_arrow();

void OLED_menu_print();

void OLED_reset();


#endif /* OLED_H_ */





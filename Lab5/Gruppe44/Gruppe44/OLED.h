
struct OLED_Contents{
	uint8_t menu_index;
	char line_0[15];
	char line_1[15];
	char line_2[15];
	char line_3[15];
	char line_4[15];
	char line_5[15];
	char line_6[15];
	char line_7[15];
} OLED_contents;

void OLED_init();

void OLED_write_c(uint8_t command);

void OLED_write_d(uint8_t data);

void OLED_gotoline(uint8_t line);

void OLED_gotocolumn(uint8_t column);

void OLED_gotopos(uint8_t line, uint8_t column);

void OLED_home();

void OLED_print_c(uint8_t letter);

void OLED_printf(char text[]);

void OLED_print_arrow();

void OLED_no_arrow();

void OLED_menu_print();

void OLED_reset();
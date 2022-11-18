#include "ADC.h"
#include <stdlib.h>
#include <avr/io.h>
#include "util/delay.h"
#include <math.h>
#include "CAN.h"

void adc_init (void){
	
	DDRD |= (1 << PD5); // Set port PD5 to 1
	TCCR1A |= (1 << COM1A0)|(1 << COM1B0); // Timer/Counter1 Control Register A (TCCR1A): Setting bit 6 and 4 to 1 - "Toggle OCnA/OCnB on Compare Match."
	TCCR1B |= (1 << WGM12)|(1 << CS10); // Timer/Counter1 Control Register B (TCCR1B): Setting bit 3 to 1 - "CTC-mode", and bit 0 to 1 "clkI/O/1 (No prescaling)"
	OCR1A = 0x1; // Setting Compare Match bit - which bit the counter triggers on
}

void adc_read(void){
	// SEND TO ADC
	volatile char * adc = ( char *) 0x1400; // Set pointer at starting memory of ADC
	adc [0] = 0xff; // Send random value to initiate
	
	// WAIT
	_delay_us(60); // Is this one necessary?
	
	// READ FROM ADC
	for (int i=0;i<4;i++) // Need to read 4 values - analog input 0 to 3
	{
		uint8_t number = adc [0]; // Read the ADC value and store it in variable
		ADC_states[i] = number;
		//if (i == 0){
		//printf( "%d ", number); // Print analog input i TODO: Change this from debugging later
		//}
	}
}

void adc_calibrate(void){
	_delay_ms(100); // Added a delay to ensure the states has settled before calibrating
	adc_read();
	X_neutral = ADC_states[0];
	Y_neutral = ADC_states[1];
	
	previous_x = ADC_states[0];
	previous_y = ADC_states[1];
	previous_right = ADC_states[2];
	previous_left = ADC_states[3];
}

void get_stick_state(void){ //Transform the stickstates from 0 <-> 255 to -100 <-> 100
	adc_read();
	uint8_t raw_x = ADC_states[0];
	uint8_t raw_y = ADC_states[1];
	//printf("%d ", raw_y);
	//uint8_t b = 51;
	if (raw_x > X_neutral){
		stick_state.X_state = (((raw_x-X_neutral) * 100 )/ (255 - X_neutral));
		//moving_average_filter_x();
	}
	else {
		stick_state.X_state = (((raw_x-X_neutral) * 100) / (X_neutral));
		//moving_average_filter_x();
	}
	
	if (raw_y > Y_neutral){
		stick_state.Y_state = (((raw_y-Y_neutral) * 100 )/ (255 - Y_neutral));
	}
	else {
		stick_state.Y_state = (((raw_y-Y_neutral) * 100) / (Y_neutral));
	}
	
}

void get_stick_direction(void){ //Checks if the output is saturated, if it is the direction is defined in an enum (0-4)
	get_stick_state();
	//printf(" %d",stick_state.Y_state);
	//uint8_t raw_x = ADC_states[0];
	//uint8_t raw_y = ADC_states[1];
	short x_value = stick_state.X_state;
	short y_value = stick_state.Y_state;
	if (x_value > 50) {
		stick_state.X_direction = RIGHT;
	}
	
	else if (x_value < -50) {
		stick_state.X_direction = LEFT;
	}
	
	else {
		stick_state.X_direction = NEUTRAL;		
	}
	if (y_value > 50) {
		stick_state.Y_direction = UP;
	}
	
	else if (y_value < -50) {
		stick_state.Y_direction = DOWN;
	}
	
	else {
		stick_state.Y_direction = NEUTRAL;
	}
}



void poll_new_readings(){
	get_stick_state();
	if(previous_x != stick_state.X_state || previous_y != stick_state.Y_state || previous_right != ADC_states[2] || previous_left != ADC_states[3]){
		struct Can_Message can_message;
		
		can_message.id = 1;
		can_message.length = 4;
		
		can_message.data[0] = stick_state.X_state + 100;
		can_message.data[1] = stick_state.Y_state + 100;
		can_message.data[2] = ADC_states[2];
		can_message.data[3] = ADC_states[3];
		// CAN TEST TO NODE 2:
		CAN_write_message(can_message);
		_delay_ms(100);
	}
	previous_x = stick_state.X_state;
	previous_y = stick_state.Y_state;
	previous_right = ADC_states[2];
	previous_left = ADC_states[3];
}
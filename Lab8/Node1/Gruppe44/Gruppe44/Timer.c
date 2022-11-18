/*
 * Timer.c
 *
 * Created: 18.11.2022 17:15:17
 *  Author: Martin
 */ 


#include <stdlib.h>
#include <avr/io.h>
#include <math.h>



timer_init(){
	TCCR1B |= 0x7; // Sets the clock scaling to CLK i/o = 1024 
}

timer_reset(){
	TCNT1 = 0x00;	
}

int timer_read(){ //TODO: Check if this actually works.
	
	int timer = TCNT1;
	return timer;
}
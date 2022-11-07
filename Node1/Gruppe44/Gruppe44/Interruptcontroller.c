/*
 * Interruptcontroller.c
 *
 * Created: 07.11.2022 13:00:54
 *  Author: marbron
 */ 


#include <avr/io.h>
#include <unistd.h>
#include <stdio.h>
#include <avr/interrupt.h>

void interrupt_init(void){
	
	cli();
	
	DDRD &= ~(1 << PIND)|(1 << PIND); //Set port to input
	DDRE &= ~(1 << PINE0);
	PORTE |= (1 << PINE0); // Internal pull up
	
	MCUCR |= (1 << SRE ); // enable XMEM
	MCUCR |= (1 << ISC11)|(1 << ISC10)|(1 << ISC01)|(1 << ISC00); //Sets the interrupt at positive flank
	EMCUCR |= (0 << ISC2); // Rising edge on INT2
	GICR |= (1 << INT0)|(1 << INT1)|(1 << INT2); //Enables the interrupt
	
	
	sei();

}

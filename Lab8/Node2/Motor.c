/*
 * Motor.c
 *
 * Created: 14.11.2022 13:12:21
 *  Author: marbron
 */ 
#include "sam.h"
#include "uart.h"

void motor_init(){
	
	/*
	PIN 32,30,27,26,25, OUPUT
	PD10 -> 32 -> DIR
	PD9 -> 30 -> EN
	PD2 -> 27 -> SEL
	PD1 -> 26 -> NOT_RST
	PD0 -> 25-> NOT_OE
	
	
	
	PIN 40-33 INPUT
	*/
	
	PMC->PMC_PCER0 |= 1 << ID_PIOC; //Allows power
	PMC->PMC_PCER0 |= 1 << ID_PIOD; //Allows power
	
	
	
	
	PIOC->PIO_PER |= PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC5 | PIO_PC6 | PIO_PC7 | PIO_PC8;
	PIOD->PIO_PER |= PIO_PD10 | PIO_PD9 | PIO_PD2 | PIO_PD1 | PIO_PD0;
	
	PIOD->PIO_OER |= PIO_PD10 | PIO_PD9 | PIO_PD2 | PIO_PD1 | PIO_PD0; //Set as output
	PIOC->PIO_PUER |= PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC5 | PIO_PC6 | PIO_PC7 | PIO_PC8; //Enable pull up resistors
	
	PIOD->PIO_SODR |= PIO_PD1; // SETS THE NOT RESET
}


uint16_t encoder_read(void){ // Target area is about 8561 -> 0, asuming the encoder is at the right most position
	uint8_t value_low;
	uint8_t value_high;
	PIOD->PIO_CODR |= PIO_PD0;
	PIOD->PIO_CODR |= PIO_PD2;
	//DELAY 20 micros
	delay_micros_10(2);
	
	value_high = PIOC->PIO_PDSR >> 1;
	PIOD->PIO_SODR |= PIO_PD2;
	//delay 20 micros
	delay_micros_10(2);
	
	value_low = PIOC->PIO_PDSR >> 1;
	PIOD->PIO_SODR |= PIO_PD0;
	
	uint16_t encoder = ((value_high << 8) | (value_low));
	
	printf("%d \r \n", encoder);
	//printf("%d \r \n", value_high);
	return encoder;
}


void motor_write(value){ // input 0-200 -> output 0-100 / 0-5V & direction
	
	PIOD->PIO_SODR |= PIO_PD9; //enables motor
	
	if (value > 101) { //Chooses direction right if over 100
		PIOD->PIO_SODR |= PIO_PD10;
		value -= 100; //Sets it to 0-100 right speed
	}
	else{
		PIOD->PIO_CODR |= PIO_PD10;
		value = 100 - value; // Sets it to 100 - 0 -> 0 - 100
	}
	
	
	dac_write(value);
	// Writes from 0-4095 -> 0-5 V
	
}
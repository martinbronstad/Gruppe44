/*
 * ADC.c
 *
 * Created: 10.11.2022 12:45:33
 *  Author: Marbron
 */ 

#include "sam.h"
#include "uart.h"



void adc_init(){
	
	
	PMC->PMC_PCER1 |= 1 << (ID_ADC - 32); //Allows power to PID 37, ADC

	//PIOA->PIO_PDA |= PIO_PA4X1_AD2; // Disables normal I/O
	
	//ADC->ADC_WPMR |= ADC_WPMR_WPEN >> 1; //Disables write protect???
	
	ADC->ADC_MR = ADC_MR_FREERUN_ON | ADC_MR_SETTLING_AST9 | ADC_MR_TRACKTIM(3) | ADC_MR_TRANSFER(3);
	// | ADC_MR_SETTLING_AST5 | ADC_MR_ANACH_NONE | ADC_MR_STARTUP_SUT8 | ADC_MR_TRACKTIM(1) | ADC_MR_TRANSFER(1) | ADC_MR_PRESCAL(1);
	
	ADC->ADC_CHER = ADC_CHER_CH2;

	ADC->ADC_CR = ADC_CR_START;
	
	
}

uint16_t adc_read(void){
	
	uint16_t value = ADC->ADC_CDR[2];
//  	if(value < 1000){
//  	printf("%d \r \n", value);
//  	}	
	return value;

}


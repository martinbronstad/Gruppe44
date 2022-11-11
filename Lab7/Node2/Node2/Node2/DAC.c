/*
 * DAC.c
 *
 * Created: 11.11.2022 15:03:14
 *  Author: markla
 */ 

#include "sam.h"
#include "uart.h"

void dac_init(void){
	
	
	PMC->PMC_PCER1 |= 1 << (ID_DACC - 32); //Allows power to PID38, DAC;

	
	
	//DACC->DACC_MR |= 
	
	
}
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
	
	
	PIOB->PIO_PDR |= PIO_PB16X1_DAC1; //Disables the PIO, so that peripheral can use it. Not sure if this is the correct implementation
	
	
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	
	DACC->DACC_CHER |= DACC_CHER_CH1;
}

void dac_write(int value){
	// Writes from 0-4095 -> 0-5 V
	DACC->DACC_CDR = value;
}

#include "sam.h"
#include "uart.h"






void timer_init(){
	
	
		PMC->PMC_PCER0 |= 1 << (ID_TC0);
		
		//PIOB->PIO_PDR |= PIO_PB26B_TCLK0; //Disables IO for the TCKL0
		
		//PIOB->PIO_ABSR |= PIO_PB26B_TCLK0; //Selects peripheral 2.
		
		TC0->TC_CHANNEL->TC_CMR |= TC_CMR_TCCLKS_TIMER_CLOCK4;
		
		TC0->TC_CHANNEL->TC_CCR |= TC_CCR_CLKEN;
		
		TC0->TC_CHANNEL->TC_CCR |= TC_CCR_SWTRG;

		
}

int timer_read(){
	
	int value = TC0->TC_CHANNEL->TC_CV;
	

	//printf("%d \r \n", value);
	
	return value;
}
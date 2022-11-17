
#include "sam.h"
#include "uart.h"






void timer_init(){
	
	
		PMC->PMC_PCER0 |= 1 << (ID_TC0);
		
		//PIOB->PIO_PDR |= PIO_PB26B_TCLK0; //Disables IO for the TCKL0
		
		//PIOB->PIO_ABSR |= PIO_PB26B_TCLK0; //Selects peripheral 2.
		
		TC0->TC_CHANNEL->TC_CMR |= TC_CMR_TCCLKS_TIMER_CLOCK4; //TIMER = MSCKL / 128
		
		TC0->TC_CHANNEL->TC_CCR |= TC_CCR_CLKEN;
		
		TC0->TC_CHANNEL->TC_CCR |= TC_CCR_SWTRG;

		
}

int timer_read(){
	
	int value = TC0->TC_CHANNEL->TC_CV;
	

	//printf("%d \r \n", value);
	
	return value;
}

void delay_micros_10(int length){ // a simple delay function, delays by length * 10 ms, 10 ms is 6.56 counts, rounded up to 7
	
	int startime = timer_read();
	
	while (timer_read() < (startime + (length * 7)))
	{
		timer_read();
	}
}

uint32_t timer_ms_read(){
	
	uint32_t value = TC0->TC_CHANNEL->TC_CV;
	value = value/656; // 656 000 ticks each second -> 656 ticks each millisecond

	//printf("%d \r \n", value);
	
	return value;
}
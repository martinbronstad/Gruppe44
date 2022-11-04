/*
 * Node2.c
 *
 * Created: 31.10.2022 11:56:33
 * Author : markla
 */ 


#include "sam.h"
#include <unistd.h>
#include <stdio.h>





int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	
	
	
	configure_uart(); //STARTS THE UART
	
	can_init(0x1292177,1,2);
	
	WDT->WDT_MR = WDT_MR_WDDIS; //DISABLES THE WATCHDOG
	
	PIOA->PIO_PER = PIO_PA19 | PIO_PA20; // PIN I/O SELECT
	PIOA->PIO_OER = PIO_PA19 | PIO_PA20; // PIN OUTPUT SELECT
	
	PIOA->PIO_SODR = PIO_PA19; //PIN SET OUTPUT DATA REGISTER
	//PIOA->PIO_SODR = PIO_PA20;
	
	int i = 1;
	
	while (1) 
    {
		CAN0_Handler();
		//i++;
		//printf("%d \r \n", i);
		
    }
}



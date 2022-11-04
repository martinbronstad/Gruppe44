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
	pwm_init();
	int i = 1;
	
	while (1) 
    {
		//CAN0_Handler();
		i++;
		REG_PWM_CDTY5 = 0x1600;
		REG_PWM_CDTY6 = 0x1600;
		REG_PWM_CDTYUPD5 = 0x1600;
		REG_PWM_CDTYUPD6 = 0x1600; //used to actually change pwm, 0x3345 = 0 V, 0x00 = 5V
		printf("i : %d\n\r", i);
		if (i == 0x3345){
			i = 0;
		}
		//printf("%d \r \n", i);
		
    }
}



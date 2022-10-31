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

    /* Replace with your application code */
	configure_uart();
	int i = 1;
	
	PIOA->PIO_PER = PIO_PA19 | PIO_PA20; // PIN I/O SELECT
	PIOA->PIO_OER = PIO_PA19 | PIO_PA20; // PIN OUTPUT SELECT
	
	PIOA->PIO_SODR = PIO_PA19; //PIN SET OUTPUT DATA REGISTER
	PIOA->PIO_SODR = PIO_PA20;
	
	while (1) 
    {
		
		i++;
		printf("%d \r \n", i);
    }
}



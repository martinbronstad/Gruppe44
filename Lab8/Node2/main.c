/*
 * Node2.c
 *
 * Created: 31.10.2022 11:56:33
 * Author : markla
 */ 


#include "sam.h"
#include <unistd.h>
#include <stdio.h>
#include "PID.h"

//RECEIVED_DATA pid_reference_data;
RECEIVED_DATA received_data_node1;
pid_data PID_DATA;



int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	
	
	
	configure_uart(); //STARTS THE UART
	
	can_init(0x1292177,1,2);
	
	pwm_init();
	
	adc_init();
	
	timer_init();
		
	game_init();
	
	dac_init();
	
	motor_init();
	
	//motor_write(0);
	
	
	WDT->WDT_MR = WDT_MR_WDDIS; //DISABLES THE WATCHDOG
	
	PIOA->PIO_PER = PIO_PA19 | PIO_PA20; // PIN I/O SELECT
	PIOA->PIO_OER = PIO_PA19 | PIO_PA20; // PIN OUTPUT SELECT
	
	PIOA->PIO_SODR = PIO_PA19; //PIN SET OUTPUT DATA REGISTER
	//PIOA->PIO_SODR = PIO_PA20;
	int i = 1;
	float T = 20; // Running time in ms (0.02 sec)
	uint32_t prev_time_reading = 0;
	
	while (1) 
    {
		//adc_read();
		//CAN0_Handler();
		//timer_read();
		//game_check_loss();
		//encoder_read();
		//dac_write(0);
		//i++;
		//REG_PWM_CDTY5 = 0x010;
		//REG_PWM_CDTY6 = 0x010;
		//pwm_set(984);
		//REG_PWM_CDTYUPD5 = 0x1800;
		//REG_PWM_CDTYUPD6 = 0x1800; //used to actually change pwm, 0x3345 = 0 V, 0x00 = 5V
		
		//printf("i : %d\n\r", i);
		//if (i == 0x3345){
		//	i = 0;
		//}
		//printf("%d \r \n", i);
		
		
		// TESTING:
		//uint32_t testing_value = timer_ms_read();
		//printf("Time in ms: %d \r \n", testing_value);
		
		CAN0_Handler();
		motor_write(100);
		//printf(" encoder: %d \r \n", (encoder_read())); // (encoder_read())/43.5)
		
		//When in game: 
		if (timer_ms_read() - prev_time_reading >= 20) // run if loop each 0.02 seconds
		{

			uint32_t sampling_time_reading = timer_ms_read() - prev_time_reading;
			pid_controller1(received_data_node1.joystick_y, &PID_DATA);
			prev_time_reading = timer_ms_read();
		}
		
    }
}



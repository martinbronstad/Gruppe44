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
PID_DATA pid_data1;




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
	
	solenoid_init();
	
	pid_init(K_P, K_I, K_D, &pid_data1);
	
	
	
	WDT->WDT_MR = WDT_MR_WDDIS; //DISABLES THE WATCHDOG
	
	PIOA->PIO_PER = PIO_PA19 | PIO_PA20; // PIN I/O SELECT
	PIOA->PIO_OER = PIO_PA19 | PIO_PA20; // PIN OUTPUT SELECT
	
	PIOA->PIO_SODR = PIO_PA19; //PIN SET OUTPUT DATA REGISTER
	//PIOA->PIO_SODR = PIO_PA20;
	int i = 1;
	int T = 20; // Running time in ms (0.02 sec)
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
		
		CAN0_Handler();
		
		//When in game: 
		if (timer_ms_read() - prev_time_reading >= sampling_interval) // run if loop each 0.02 seconds, 20
		{

			//uint32_t sampling_time_reading = timer_ms_read() - prev_time_reading;
			pid_controller1(received_data_node1.joystick_y, &pid_data1);
			//pwm_set_servo(received_data_node1.joystick_x);
			//printf("Encoder %d \r\n",encoder_read());
			prev_time_reading = timer_ms_read();
			
			if (solenoid_flag == 1){
				solenoid_fire();
				solenoid_flag = 0;
			}
			
		}
		
    }
}



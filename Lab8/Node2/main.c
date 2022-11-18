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
	
	/* Initialize uart and CAN*/
	configure_uart(); 
	can_init(0x1292177,1,2);
	
	/* Initialize various functions: */
	//pwm_init();
	adc_init();
	timer_init();
	game_init();
	dac_init();
	//motor_init();
	solenoid_init();
	//pid_init(K_P*SCALING_FACTOR, K_I*SCALING_FACTOR, K_D*SCALING_FACTOR, &pid_data1);
	
	
	//DISABLE WATCHDOG
	WDT->WDT_MR = WDT_MR_WDDIS; 
	
	// PIN I/O SELECT
	PIOA->PIO_PER = PIO_PA19 | PIO_PA20; 
	// PIN OUTPUT SELECT
	PIOA->PIO_OER = PIO_PA19 | PIO_PA20; 
	
	//PIN SET OUTPUT DATA REGISTER
	PIOA->PIO_SODR = PIO_PA19; 
	
	uint32_t prev_time_reading = 0;
	
	in_game = 0;
	
	while (1) 
    {
		
		CAN0_Handler();
		
		/* In game: */
		if(in_game){
			game_check_loss();
			
			if (timer_ms_read() - prev_time_reading >= sampling_interval){ // run IF-loop each 0.02 seconds
				
				// Joystick control:
				if(use_slider == 0){
					pid_controller1(received_data_node1.joystick_y, &pid_data1);
					
				}
				else{ // Slider control:
					pid_controller1((received_data_node1.slider_right)*0.78, &pid_data1); // value*0.78: 0-255 -> 0-200
				}
				
				//pid_controller1(received_data_node1.joystick_y, &pid_data1);
				//pwm_set_servo(received_data_node1.joystick_x);
				prev_time_reading = timer_ms_read();
				
				if (solenoid_flag){
					solenoid_fire();
					solenoid_flag = false;
				}
				
			}
				
		}
		
		/* Idle: */
		else{
			// Disable motor and PWM
			motor_disable();
			pwm_disable();
		}
		
    }
}

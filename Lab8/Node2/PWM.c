/*
 * PWM.c
 *
 * Created: 04.11.2022 10:53:55
 *  Author: marbron
 */ 


#include <stdint.h>

#include "sam.h"
#include "uart.h"



void pwm_init(void) {
	
	
	PMC->PMC_PCER1 |= 1 << (ID_PWM - 32); //Allows power to PID36, PWM;

	PIOC->PIO_PDR |= PIO_PC18B_PWMH6 | PIO_PC19B_PWMH5; //Disables the PIO, so that peripheral can use it. Not sure if this is the correct implementation
	PIOC->PIO_ABSR |= PIO_PC18B_PWMH6 | PIO_PC19B_PWMH5; //Selects peripheral 2.
	
	PWM->PWM_WPCR |= 0xFC; // SELECTS GROUP 0-6; WPRGx
	PWM->PWM_WPCR |= PWM_WPCR_WPCMD(0); //Unlock user interface
	
	PWM->PWM_CLK = PWM_CLK_DIVA(1) | PWM_CLK_DIVB(1) | PWM_CLK_PREA(7) | PWM_CLK_PREB(7); //TODO: check if this is correct, MCK/128
	
	PWM->PWM_DIS = PWM_DIS_CHID5 | PWM_DIS_CHID6;
	
	REG_PWM_CMR5 = PWM_CMR_CPRE_CLKA; //CLOCK A, LEFT ALIGNED
	REG_PWM_CMR6 = PWM_CMR_CPRE_CLKB; //CLOCK B, LEFT ALIGNED
	
	REG_PWM_CPRD5 = 0x3345; //SETS THE PERIOD TO 20MS, 58MHZ*20ms = X * CPRD
	REG_PWM_CPRD6 = 0x3345;
	
	REG_PWM_CDTY5 = 0x3345; // 
	REG_PWM_CDTY6 = 0x3345; //used to actually change pwm, 0x3345 = 0 V, 0x00 = 5V
	

	PWM->PWM_ENA = PWM_ENA_CHID5 | PWM_ENA_CHID6; //ENABLE
	
}

void pwm_set(int value) {
	// SETS THE PWM VALUE, CAPPED TO 0,9ms - 2.1 ms
	if (value > 1378){
		value = 1378;
		
	}
	if (value < 591){
		value = 591;
	}
	
	REG_PWM_CDTY5 = (0x3345 - value);	
}

void pwm_set_servo(int value){
	//SETS THE PWM VALUE BASED OF JOYSTICK, GETS 0-200 in, ~591-1378 out
	
	value = value*4 + 502; // Calculated value 591
	
	pwm_set(value);
	
}

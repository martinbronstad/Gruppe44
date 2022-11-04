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
	
	
	PMC->PMC_PCER0 = 1 << ID_PWM; //Allows power
	PIOA->PIO_ABSR = PIO_PC18B_PWMH6 | PIO_PC19B_PWMH5; //Selects peripheral 2.
	PIOA->PIO_PDR = PIO_PC18B_PWMH6 | PIO_PC19B_PWMH5; //Disables the PIO, so that peripheral can use it. Not sure if this is the correct implementation
	PWM->PWM_WPCR =PWM_WPCR_WPCMD(1); //Unlock user interface
	PWM->PWM_CLK = PWM_CLK_DIVA(1) | PWM_CLK_DIVB(1) | PWM_CLK_PREA(7) | PWM_CLK_PREB(7); //TODO: check if this is correct, MCK/128
	
	REG_PWM_CMR5 = PWM_CMR_CPRE_CLKA; //CLOCK A, LEFT ALIGNED
	REG_PWM_CMR6 = PWM_CMR_CPRE_CLKB; //CLOCK B, LEFT ALIGNED
	
	REG_PWM_CPRD5 = 0x3345; //SETS THE PERIOD TO 20MS, 58MHZ*20ms = X * CPRD
	REG_PWM_CPRD6 = 0x3345;
	
	REG_PWM_CPRDUPD5 = 0x3345; //USE AFTER VALIDATION OF THE CHANNEL?
	REG_PWM_CPRDUPD6 = 0x3345;
	
	REG_PWM_CDTY5 = 0x3345;
	REG_PWM_CDTY6 = 0x3345; //used to actually change pwm, 0x3345 = 0 V, 0x00 = 5V
	
	//PWM->PWM_IER1 = PWM_IER1_CHID0 | PWM_IER1_FCHID0;
	//PWM->PWM_IER2 = WRDYE 1680 000
	
	
	PWM->PWM_ENA = PWM_ENA_CHID5 | PWM_ENA_CHID6; //ENABLE
	
	
}

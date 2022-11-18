/*
 * interrupt.c
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include "can_interrupt.h"
#include <stdio.h>
#include "sam.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "PID.h" 

#define DEBUG_INTERRUPT 0

RECEIVED_DATA received_data_node1;

/**
 * \brief CAN0 Interrupt handler for RX, TX and bus error interrupts
 *
 * \param void
 *
 * \retval 
 */
void CAN0_Handler( void )
{
	//if(DEBUG_INTERRUPT)printf("CAN0 interrupt\n\r");
	char can_sr = CAN0->CAN_SR; 
	
	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2) )//Only mailbox 1 and 2 specified for receiving
	{
		CAN_MESSAGE message;
		
		if(can_sr & CAN_SR_MB1)  //Mailbox 1 event
		{
			can_receive(&message, 1);

		}
		else if(can_sr & CAN_SR_MB2) //Mailbox 2 event
		
		{
			can_receive(&message, 2);
		}
		else
		{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}

		if(DEBUG_INTERRUPT)printf("message id: %d\n\r", message.id);
		if(DEBUG_INTERRUPT)printf("message data length: %d\n\r", message.data_length);
		
	
		
		for (int i = 0; i < message.data_length; i++)
		{
			if(DEBUG_INTERRUPT)printf("%d ", message.data[i]);
		}
		if (message.id == 1){
			received_data_node1.joystick_x = message.data[0];
			received_data_node1.joystick_y = message.data[1];
			received_data_node1.slider_left = message.data[2];
			received_data_node1.slider_right = message.data[3];
			
			//if(DEBUG_INTERRUPT)printf("\r \n joystick x %d \r \n", received_data_node1.joystick_x);
			//if(DEBUG_INTERRUPT)printf(" joystick y %d \r \n", received_data_node1.joystick_y);
			//if(DEBUG_INTERRUPT)printf(" slider left %d \r \n", received_data_node1.slider_left);
			//if(DEBUG_INTERRUPT)printf(" slider right %d \r \n", received_data_node1.slider_right);
			
			//pwm_set_servo(message.data[0]);
			//pid_controller1(message.data[1]); // Need to store the value somewhere thats accessible from main
		}
		if (message.id == 2){
			//solenoid_fire();
			solenoid_flag = 1;
		}
		//can_send(&message, 0); //REPLIES WITH THE SAME MESSAGE BACK
		if(DEBUG_INTERRUPT)printf("\n\r");
	}
	
	if(can_sr & CAN_SR_MB0)
	{
		//if(DEBUG_INTERRUPT) printf("CAN0 MB0 ready to send \n\r");
		
	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;

	}

	if(can_sr & CAN_SR_ERRP)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}
	
	NVIC_ClearPendingIRQ(ID_CAN0);
	//sei();*/
}

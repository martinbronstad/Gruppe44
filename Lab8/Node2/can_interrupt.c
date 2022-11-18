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
RECEIVED_GAME_SETTINGS received_game_settings_node1;


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
		
		/* Joystick and slider values: */
		if(message.id == 1){
			received_data_node1.joystick_x = message.data[0];
			received_data_node1.joystick_y = message.data[1];
			received_data_node1.slider_left = message.data[2];
			received_data_node1.slider_right = message.data[3];
			
		}
		
		/* Left button: */
		if(message.id == 2){
			solenoid_flag = true;
		}
		
		/* Game settings: */
		if(message.id == 3){ 
			received_game_settings_node1.use_slider = message.data[0];
			received_game_settings_node1.game_mode = message.data[1];
			received_game_settings_node1.difficulty = message.data[2];
		}
		
		/* Game start: */
		if(message.id == 4){
			if(message.data[0] == 1){
				in_game = true;
				game_init_flag = true;
			}
			else{
				in_game = false;
			}
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
	//sei();
}

/*
 * PID.h
 *
 * Created: 17.11.2022 09:39:35
 *  Author: markla
 */ 

#include <stdint.h>

#ifndef PID_H_
#define PID_H_

#define SCALING_FACTOR  512

#define max_u 51200 // Scaling factor * 100
#define max_up 10000
#define max_ui 10000
#define max_ud 10000

#define sampling_interval 20

#define K_P 1.0
#define K_I 1.0
#define K_D 1.0

//int16_t error;
//int16_t prev_error;
//int16_t prev_prev_error;
//int16_t prev_output;

//int16_t prev_time;
//int16_t cumulative_error;
//int16_t T;

typedef struct received_data
{
	uint8_t joystick_x;
	uint8_t joystick_y;
	uint8_t slider_left;
	uint8_t slider_right;
} RECEIVED_DATA;

typedef struct PID_DATA{
	uint16_t KP;
	uint16_t KI;
	uint16_t KD;
	
	int16_t sampling_time;
	int16_t prev_error;
	int16_t prev_ui;
} pid_data;



void pid_init(int16_t KP, int16_t KI, int16_t KD, struct PID_DATA *pid);

void pid_controller1(uint8_t reference, struct PID_DATA *pid);


#endif /* PID_H_ */
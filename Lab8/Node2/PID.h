/*
 * PID.h
 *
 * Created: 17.11.2022 09:39:35
 *  Author: markla
 */ 

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef PID_H_
#define PID_H_

#define SCALING_FACTOR  1000
#define encoder_range 8500 // Box 8 0-8000, Box 15 0-1900, Box 14 0-8700, box 19 0-1800

#define max_u SCALING_FACTOR*100 // Scaling factor * 100
#define max_up SCALING_FACTOR*60
#define max_ui SCALING_FACTOR*20
#define max_ud SCALING_FACTOR*20

#define sampling_interval 20

#define K_P 0.8
#define K_I 0.4
#define K_D 0.1

volatile bool solenoid_flag;
volatile bool in_game; 
volatile bool game_init_flag;

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

// typedef struct received_game_settings
// {
// 	uint8_t use_slider; // 0 for using joystick, 1 for using slider
// 	uint8_t game_mode; // 0 Normal mode, 1 Arcade mode
// 	uint8_t difficulty; // 1 Easy, 2 Medium, 3 Hard
// } RECEIVED_GAME_SETTINGS;

typedef struct pid_data{
	uint32_t KP;
	uint32_t KI;
	uint32_t KD;
	
	int32_t sampling_time;
	int32_t prev_error;
	int32_t prev_ui;
} PID_DATA;


uint8_t use_slider; // 0 for using joystick, 1 for using slider
uint8_t game_mode; // 0 Normal mode, 1 Arcade mode
uint8_t difficulty; // 1 Easy, 2 Medium, 3 Hard

void pid_init(int32_t P_factor, int32_t I_factor, int32_t D_factor, struct pid_data *pid);

void pid_controller1(uint8_t reference, struct pid_data *pid);


#endif /* PID_H_ */
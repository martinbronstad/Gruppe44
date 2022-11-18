/*
 * PID.c
 *
 * Created: 16.11.2022 04:21:38
 *  Author: marti
 */ 

#include "PID.h"

void pid_init(int32_t P_factor, int32_t I_factor, int32_t D_factor, struct pid_data *pid){ // Code is based on code from AVR221: Discrete PID Controller on tinyAVR and megaAVR devices. 
	
	pid->KP = 0.8 * SCALING_FACTOR; // 0.8 
	pid->KI = 0.4 * SCALING_FACTOR; // 0.4
	pid->KD = 0.1 * SCALING_FACTOR; // 0.1
	
	pid->sampling_time = sampling_interval;
	pid->prev_error = 0;
	pid->prev_ui = 0;

}


void pid_controller1(uint8_t reference, struct pid_data *pid){ //based on lab notes
	// Sensor reading y:
	int32_t sensor_value = encoder_read(); // y: 0-200 (43.5)
	if (sensor_value > 10000)sensor_value = 0;
	sensor_value = (sensor_value*200)/encoder_range; // Box 15 - 0-1900
	
	reference = 200 - reference;
	
	// e = r - y
	int32_t error = reference - sensor_value;
	if(error < 5 & error > -5){
		error = 0;
	}
	
	// Calculate outputs P-term, I-term, D-term
	int32_t output_p = pid->KP*error;
	int32_t output_i = 0.02 * pid->KI * error + pid->prev_ui;
	int32_t output_d = (pid->KD / 0.02) * (error - pid->prev_error);
	
	// Anti windup and saturation
	if (output_p > max_up) {
		output_p = max_up;
	}
	else if (output_p < -max_up){
		output_p = -max_up;
	}
	
	if (output_d > max_ud) {
		output_d = max_ud;
	}
	else if (output_d < -max_ud){
		output_d = -max_ud;
	}
	
	if (output_i > max_ui) {
		output_i = max_ui;
	}
	else if (output_i < -max_ui){
		output_i = -max_ui;
	}
	
	// Update values
	pid->prev_error = error;
	pid->prev_ui = output_i;
	
	// u = up + ui + ud
	int32_t output = output_p + output_i + output_d;
	
	if (output > max_u) {
		output = max_u;
	}
	else if (output < -max_u){
		output = -max_u;
	}
	
	output = output/SCALING_FACTOR;
	int u = (int)output + 100;
	
// 	printf("reference: %d ",reference);
// 	//printf("sensor value: %d ",sensor_value);
// 	printf("error: %d ", error);
// 	
// 	//printf("KP: %d ",pid->KP); 
// 	//printf("KI: %d ",pid->KI);
// 	//printf("KD: %d \r\n",pid->KD);
// 	
// 	printf("up: %d ",output_p);
// 	printf("ui: %d ",output_i);
// 	printf("ud: %d ",output_d);
// 	
// 	printf("output: %d ", output);
// 	printf("encoder: %d ",encoder_read());
// 	printf("u: %d \r\n",u);
	motor_write(u);
	
}
	
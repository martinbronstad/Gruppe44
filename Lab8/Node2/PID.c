/*
 * PID.c
 *
 * Created: 16.11.2022 04:21:38
 *  Author: marti
 */ 

#include "PID.h"


void pid_init(int16_t KP, int16_t KI, int16_t KD, struct PID_DATA *pid){ // From example in lab lectures
	
	/*
		kp = 10000;
		kd = 256;
		ki = 256;
		
		max_up = 100;
		max_ud = 100;
		max_ui = 100;
		
		sampling_time = 0;
		prev_time = 0;
		cumulative_error = 0;
		T = 0.02;
	*/
	
	// NEW VERSION:
	
	pid->KP = K_P*SCALING_FACTOR;
	pid->KI = K_I*SCALING_FACTOR;
	pid->KD = K_D*SCALING_FACTOR;
	pid->sampling_time = sampling_interval;
	pid->prev_error = 0;
	pid->prev_ui = 0;
}



void pid_controller1(uint8_t reference, struct PID_DATA *pid){ //based on lab notes
	// Reference: 0 - 200
	// Encoder: 0 (right) - 8700 (left)
	// Joystick Y: down - 0 // up // 200
	/*
	reference = 200 - reference; // reverse the input reference

	//int output = 0;
	//int16_t T = sampling_time_reading; // Sample time in ms
	//int16_t sensor_value = encoder_read(); // y: 0-200 (43.5)
	//if (sensor_value > 10000)sensor_value = 0;
	//sensor_value = sensor_value/9.5; // Box 15 - 0-1900
	//int16_t error = sensor_value - reference;
	//cumulative_error = cumulative_error + error; // Sum of the errors from previous steps
	//printf(" error: %d",error);
	
	int16_t up = kp*error;
	int16_t ui = sampling_time_reading * ki * error + prev_ui; // Based on the fact that if the difference between the prev ui and the new is T*ki + e[n]
	//ui = T * ki * cumulative_error;
	int16_t ud = (kd  * (error - prev_error)) / sampling_time_reading;
	
	if (up > max_up) { //anti windup and such.
		up = max_up;
	}
	else if (up < -max_up){
		up = -max_up;
	}
	
	if (ud > max_ud) {
		ud = max_ud;
	}
	else if (up < -max_ud){
		ud = -max_ud;
	}
	
	if (ui > max_ui) {
		ui = max_ui;
	}
	else if (ui < -max_ui){
		ui = -max_ui;
	}
	
	output = (int)(up + ud + ui); // convert output to int
	
	if (output > 100) {
		output = 100;
	}
	else if (output < -100){
		output = -100;
	}
	
	
	printf("error: %d \r \n", error);
	
	printf("\r \n kp: %d ", kp);
	printf("ki: %d ", ki);
	printf("kd: %d \r \n", kd);
	
	printf("\r \n up: %d ", up);
	printf("ui: %d ", ui);
	printf("ud: %d ", ud);
	printf(" output: %d \r \n", output);
	motor_write(output + 100);
	
	// UPDATE VARIABLES:
	prev_ui = ui;
	prev_error = error;*/
	
	//NEW VERSION:
	
	// Sensor reading y:
	int16_t sensor_value = encoder_read(); // y: 0-200 (43.5)
	if (sensor_value > 10000)sensor_value = 0;
	sensor_value = sensor_value/9.5; // Box 15 - 0-1900
	
	// e = r - y
	int16_t error = reference - sensor_value;
	
	// Calculate outputs P-term, I-term, D-term
	int16_t output_p = pid->KP*error;
	int16_t output_i = pid->sampling_time * pid->KI * (error + pid->prev_ui);
	int16_t output_d = (pid->KD / pid->sampling_time) * (error - pid->prev_error);
	
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
	
	printf("reference: %d ",reference);
	printf("sensor value: %d ",sensor_value);
	printf("error: %d \r\n", error);
	
	printf("KP: %d ",K_P*SCALING_FACTOR); // This gives 10, so not sure why KP, KI and KD = 0?
	printf("KI: %d ",pid->KI);
	printf("KD: %d \r\n",pid->KD);
	
	printf("up: %d ",output_p);
	printf("ui: %d ",output_i);
	printf("ud: %d \r\n",output_d);
	
	printf("output: %d \r\n", output);
	
	motor_write((int)output + 100);
	
}
	
/*
void pid_controller2(int reference){ //incremental regulator, based on bachelor, not sure if implemented correctly
	int output = 0;
	int sensor_value = encoder_read();
	int error = sensor_value - reference;
	
	up = kp*(error - prev_error);
	ui = ki*error;
	ud = kd*(error - 2*prev_error + prev_prev_error);
	
	if (up > max_up) { //anti windup and such.
		up = max_up;
	}
	else if (up < -max_up){
		up = -max_up;
	}
	
	if (ud > max_ud) {
		ud = max_ud;
	}
	else if (up < -max_ud){
		ud = -max_ud;
	}
	
	if (ui > max_ui) {
		ui = max_ui;
	}
	else if (ui < -max_ui){
		ui = -max_ui;
	}
	
	output = up + ui + ud + prev_output;
	
	int prev_prev_error = prev_error;
	int prev_error = error;
	int prev_output = output;
	
	
	if (output > 100) {
		output = 100;
	}
	else if (output < -100){
		output = -100;
	}
	
	//printf("Output: %d \r \n", output);
	motor_write(output + 100);
	
	
	
	
}
*/


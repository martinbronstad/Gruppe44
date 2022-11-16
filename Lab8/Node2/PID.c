/*
 * PID.c
 *
 * Created: 16.11.2022 04:21:38
 *  Author: marti
 */ 


int kp; //Kinda messy way to set up variables, should be done in another way.
int kd;
int ki;
int up;
int ud;
int ui;

int max_up;
int max_ud;
int max_ui;

int prev_error;
int prev_prev_error;
int prev_output;
int prev_ui;

int sampling_time = 0; //TODO: calculate this and add it


void pid_init(void){ // TODO: see what values to put in.
	
	kp = 1;
	kd = 1;
	ki = 1;
	
	int max_up = 100;
	int max_ud = 100;
	int max_ui = 100;
}






void pid_controller1(int referance){ //based on lab notes
	int output = 0;
	int sensor_value = encoder_read();
	int error = sensor_value - referance;
	
	up = kp*error;
	ui = sampling_time * ki * error + prev_ui; // Based on the fact that if the difference between the prev ui and the new is T*ki + e[n]
	ud = (kd / sampling_time) * (error - prev_error);
	
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
	
	
	int prev_ui = ui;
	int prev_error = error;
	
	output = up + ud + ui;
	
	if (output > 100) {
		output = 100;
	}
	else if (output < -100){
		output = -100;
	}
	
	motor_write(output + 100);
	
	
}

void pid_controller2(int referance){ //incremental regulator, based on bachelor, not sure if implemented correctly
	int output = 0;
	int sensor_value = encoder_read();
	int error = sensor_value - referance;
	
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
	
	motor_write(output + 100);
	
	
	
	
	
}
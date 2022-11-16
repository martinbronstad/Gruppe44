/*
 * PID.c
 *
 * Created: 16.11.2022 04:21:38
 *  Author: marti
 */ 


float kp; //Kinda messy way to set up variables, should be done in another way.
float kd;
float ki;
float up;
float ud;
float ui;

int max_up;
int max_ud;
int max_ui;

int prev_error;
int prev_prev_error;
int prev_output;
float prev_ui;

float sampling_time = 0; //TODO: calculate this and add it
float prev_time = 0;
int cumulative_error = 0;
float T = 0.02;


void pid_init(void){ // TODO: see what values to put in.
	
	kp = 0.01;
	kd = 0.01;
	ki = 0.01;
	
	int max_up = 100;
	int max_ud = 100;
	int max_ui = 100;
}





// Position based PID controller
// Implement a function/interrupt such that the algorithm runs at a regular timing ref. lab lecture notes
void pid_controller1(int reference){ //based on lab notes
	// Reference: 0 - 200
	// Encoder: 0 (right) - 8700 (left)
	// Joystick Y: down - 0 // up // 200
	
	reference = 200 - reference; // reverse the input reference
	
	//sampling_time  = timer_read() - prev_time; // 656 000 iterations each second
	//printf(" T: %d", sampling_time);
	
	if((timer_read() - prev_time)/656 > 20){ // Runs every 20ms ( T = 0.02)
		//printf(" reference: %d", reference);
		int testing_time = (timer_read() - prev_time)/656;
		printf(" T: %d", testing_time);
		int output = 0;
		int T = 0.038;
		int sensor_value = (encoder_read())/43.5; // y: 0-200
		if (sensor_value > 10000)sensor_value = 0;
		int error = sensor_value - reference;
		cumulative_error = cumulative_error + error; // Sum of the errors from previous steps
		//printf(" error: %d",error);
	
		up = kp*error;
		//ui = sampling_time * ki * error + prev_ui; // Based on the fact that if the difference between the prev ui and the new is T*ki + e[n]
		// ui = sampling_time * ki * (error + prev_error); 
		ui = T * ki * cumulative_error;
		ud = (kd / T) * (error - prev_error);
	
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
	
		printf("up: %d ", up);
		printf("ui: %d ", ui);
		printf("ud: %d ", ud);
		printf(" output: %d \r \n", output);
		motor_write(output + 100);
		
		// UPDATE VARIABLES:
		prev_ui = ui;
		prev_error = error;
		prev_time = timer_read() ; // For the next iteration
	}
	
}

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
#ifndef ADC_H_
#define ADC_H_

struct Stick_state{
	short X_state;
	short Y_state;
	short X_direction;
	short Y_direction;
} stick_state;

int ADC_states[4];

short mov_avg_x[4];
short mov_avg_y[4];

int X_neutral;
int Y_neutral;

enum direction{NEUTRAL, UP, LEFT, RIGHT, DOWN};

void adc_init (void);
void adc_read(void);
void adc_calibrate(void);
void get_stick_state(void);
void get_stick_direction(void);
void moving_average_filter_x(void);

#endif /* ADC_H_ */


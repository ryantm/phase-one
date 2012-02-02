#include <pololu/3pi.h>
unsigned int sensors[5];

int main()
{
	pololu_3pi_init(2000); // initialize 3pi
	play("L16 ceg>c");
  print("Phase 1");
  delay_ms(1000);
  clear();

	print("Battery");
	lcd_goto_xy(0,1);
	print_long(read_battery_millivolts_3pi());

	wait_for_button_press(MIDDLE_BUTTON);

	int motor_speed = 50;
	int offset = 2; //motors don't spin the same speed, must calibrate

	set_motors(motor_speed,motor_speed+offset);
	while(1)
		{
			read_line_sensors(sensors, IR_EMITTERS_ON);
			if (sensors[3] > 1500) // edge detected!
				{
					set_motors(0,0); // stop
					play("L16 ceg>c");
					set_motors(-motor_speed,-motor_speed-offset); // back up
					delay_ms(1000);
					set_motors(-motor_speed,motor_speed+offset); // turn around
					delay_ms(670);
					set_motors(motor_speed, motor_speed+offset); // resume forward
				}
		}
	return 0;
}

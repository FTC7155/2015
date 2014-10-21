#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Motor,  mtr_S1_C1_1,     leftWheel1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftWheel2,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     leftWheel3,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightWheel1,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     rightWheel2,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     rightWheel3,   tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);

		motor[leftWheel1] = joystick.joy1_y1;
		motor[leftWheel2] = joystick.joy1_y1;
		motor[leftWheel3] = joystick.joy1_y1;

		motor[rightWheel1 = joystick.joy1_y2;
		motor[rightWheel2] = joystick.joy1_y2;
		motor[rightWheel3] = joystick.joy1_y2;

	}
}

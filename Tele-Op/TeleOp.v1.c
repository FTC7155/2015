#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Motor,  mtr_S1_C1_1,     leftWheel1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftWheel2,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     leftWheel3,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightWheel1,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     rightWheel2,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     rightWheel3,   tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 Harvard-Westlake Middle School Robotics Team
 FTC7155
 Tele-Op Code
 Authors: Jonathan Damico, Nomi Ringoach
 Version 1
 Revised November 3, 2014
*/

#include "JoystickDriver.c"

task main() //Main task for code
{
	while(true)
 	{
		//Get joystick settings and positions
        getJoystickSettings(joystick);

		//Set left wheels
        motor[leftWheel1] = joystick.joy1_y1;
		motor[leftWheel2] = joystick.joy1_y1;
		motor[leftWheel3] = joystick.joy1_y1;

        //Set right wheels
		motor[rightWheel1] = joystick.joy1_y2;
		motor[rightWheel2] = joystick.joy1_y2;
		motor[rightWheel3] = joystick.joy1_y2;

	}
}

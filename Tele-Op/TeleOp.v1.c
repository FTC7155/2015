#pragma config(Hubs,  S1, HTServo,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S2_C1_1,     rightWheel1,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     rightWheel2,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     rightLift,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     leftLift,      tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     leftWheel1,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_2,     leftWheel2,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 Harvard-Westlake Middle School Robotics Team
 FTC7155
 Tele-Op Code
 Authors: Jonathan Damico, Nomi Ringoach
 Version 1
 Since November 3, 2014
*/

#include "JoystickDriver.c"

task main() //Main task for code
{
	waitForStart();

	while(true)
 	{
		//Get joystick settings and positions
    getJoystickSettings(joystick);

		//Set left wheels
    motor[leftWheel1] = joystick.joy1_y1;
		motor[leftWheel2] = joystick.joy1_y1;

    //Set right wheels
		motor[rightWheel1] = joystick.joy1_y2;
		motor[rightWheel2] = joystick.joy1_y2;

	}
}

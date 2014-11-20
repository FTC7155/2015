#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rightLift,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightWheel2,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     leftWheel1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     rightWheel1,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_1,     leftWheel2,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_2,     leftLift,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    hook,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
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

task main() { //Main task for code

	waitForStart();

	while(true) {

		//Get joystick settings and positions
        getJoystickSettings(joystick);

   	    //set motor speeds
        //makes sure that we are converting the 127 point signal
        //from the joystick to the 100 point signal used by the robot
        float rightWheels = joystick.joy1_y2;
        float leftWheels = joystick.joy1_y1;

        //rightWheels *=100/128;
        //leftWheels*=100/128;

		//Set left wheels
        motor[leftWheel1] = leftWheels;
		motor[leftWheel2] = leftWheels;

        //Set right wheels
		motor[rightWheel1] = rightWheels;
		motor[rightWheel2] = rightWheels;

		//TEMP - Control for lift
		if(joy1Btn(Btn7)){
			motor[leftLift]=100;
			motor[rightLift]=100;
		} if(joy1Btn(Btn5)){
			motor[leftLift]=-100;
			motor[rightLift]=-100;
		} else {
			motor[leftLift]=0;
			motor[rightLift]=0;
		}
	}
}

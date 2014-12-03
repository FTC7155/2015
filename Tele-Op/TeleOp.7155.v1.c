#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          rightIntake,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftIntake,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     leftWheel1,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     rightWheel1,   tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     leftLift,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     rightLift,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C2_1,     leftWheel2,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     rightWheel2,   tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    leftHook,             tServoStandard)
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

task hook () {
	//Hook
	bool hookUp = false;
	while(true) {
		getJoystickSettings(joystick);
		if(joy1Btn(Btn2)&&!hookUp) {
			servo[leftHook]=155;
			servo[rightHook]=65;
			hookUp=true;
			//while(joy1Btn(Btn2)) {}
			wait1Msec(270);
		} if(joy1Btn(Btn2)&&hookUp) {
			servo[leftHook]=65;
			servo[rightHook]=160;
			hookUp=false;
			//while(joy1Btn(Btn2)) {}
			wait1Msec(270);
		}
	}
}


task main() { //Main task for code

	waitForStart();

	startTask(hook);

	while(true) {

  	//Get joystick settings and positions
    getJoystickSettings(joystick);

		//Set left wheels
    motor[leftWheel1] = joystick.joy1_y1;
		motor[leftWheel2] = joystick.joy1_y1;

    //Set right wheels
		motor[rightWheel1] = joystick.joy1_y2;
		motor[rightWheel2] = joystick.joy1_y2;

		//Control for lift
		if(joy1Btn(Btn5)){
			motor[leftLift]=-127;
			motor[rightLift]=127;
		} else if(joy1Btn(Btn7)){
			motor[leftLift]=50;
			motor[rightLift]=-50;
		} else {
			motor[leftLift]=-5;
			motor[rightLift]=5;
		}

		//Control for Intake
		if(joy1Btn(Btn6)){
			motor[leftIntake] = 127;
			motor[rightIntake] = 127;
		} else if(joy1Btn(Btn8)) {
			motor[leftIntake] = -127;
			motor[rightIntake] = -127;
		} else {
			motor[leftIntake] = 0;
			motor[rightIntake] = 0;
		}
	}
}

#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          rightIntake,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftIntake,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     leftWheel1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightWheel1,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     leftLift,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     rightLift,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C2_1,     leftWheel2,    tmotorTetrix, openLoop, reversed)
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
Authors: Jonathan Damico, Nomi Ringach (who did absolutely nothing, except a random tab once...)
Version 1
Since November 3, 2014
*/

#include "JoystickDriver.c"

#include "drivers/hitechnic-sensormux.h"	// just files to make the SMUX work.

//SMUX prob wont work needs fixes
const tMUXSensor leftIR = msensor_S3_3;
const tMUXSensor rightIR = msensor_S3_1;
const tMUXSensor touch = msensor_S3_2;

//Task to control all the movement of the hook for the robot during tele-op
task hook () {

	//Boolean statement to determine if the hook is up. Initilization.
	bool hookUp = false;

	//Loop this part of the code forever
	while(true) {

		//Update the Joysticks
		getJoystickSettings(joystick);

		//Put hook up
		if(joy1Btn(Btn2)&&!hookUp) { 	//If the A Button is pressed, and the hook isn't up
			servo[leftHook]=155;				//Set left hook to up position
			servo[rightHook]=65;				//Set right hook to up position
			hookUp=true;								//Tell the program that the hook is up
			wait1Msec(300);							//Wait so that we can give the hook time to go up, and so the button doesn't get "stuck"
		}

		//Put hook down
		if(joy1Btn(Btn2)&&hookUp) {
			servo[leftHook]=50;
			servo[rightHook]=173;
			hookUp=false;
			//while(joy1Btn(Btn2)) {}
			wait1Msec(300);
		}
	}
}

//UNUSED - Test control for the lift
task lift () {
	int height = 1;
	int liftTarget;
	while(true) {
		switch(height) {
		case 1: liftTarget = 0; 		nMotorEncoderTarget[leftLift] = liftTarget; nMotorEncoderTarget[rightLift] = liftTarget; break;
		case 2: liftTarget = -1600;	nMotorEncoderTarget[leftLift] = liftTarget; nMotorEncoderTarget[rightLift] = liftTarget; break;
		case 3: liftTarget = -3200; nMotorEncoderTarget[leftLift] = liftTarget; nMotorEncoderTarget[rightLift] = liftTarget; break;
		}

		if(nMotorEncoder[leftLift]>nMotorEncoderTarget[leftLift]) {
			motor[leftLift] = -127;
			motor[rightLift] = 127;
			} else if (nMotorEncoder[leftLift]<nMotorEncoderTarget[leftLift]) {
			motor[leftLift] = 127;
			motor[rightLift] = -127;
			} else if (nMotorEncoder[leftLift] == nMotorEncoderTarget[leftLift]) {
			motor[leftLift] = 0;
			motor[rightLift] = 0;
		}

		if(joy1Btn(Btn5)){
			if(height == 3)
				height=1;
			else if(height == 2)
				height=3;
			else if(height == 1)
				height=2;
			while(joy1Btn(Btn5)) {}
		}
		if(joy1Btn(Btn7)) {
			if(height == 3)
				height=2;
			else if(height == 2)
				height=1;
			else if(height == 1)
				height=3;
			while(joy1Btn(Btn5)) {}
		}
		//displayCenteredBigTextLine(4, "%d, %d", height, liftTarget);
		//OLD Control for lift
		/*
		if(joy1Btn(Btn5)&& nMotorEncoder[leftLift]>-3700){
		motor[leftLift]=-127;
		motor[rightLift]=127;
		} else if(joy1Btn(Btn7) && nMotorEncoder[leftLift]<-10){
		motor[leftLift]=127;
		motor[rightLift]=-127;
		} else {
		motor[leftLift] = 0;
		motor[rightLift] = 0;
		}
		*/
		displayCenteredBigTextLine(1, "%d, %d", nMotorEncoder[leftLift], height);

		while(nMotorRunState[leftLift] != runStateIdle) {}
	}
}
task intake () {
	bool liftCondition = false;
	while(true) {
		getJoystickSettings(joystick);
		//Control for Intake
		if(joy1Btn(Btn6) && !liftCondition){
			motor[leftIntake] = 127;
			motor[rightIntake] = 127;
			liftCondition = true;
			wait1Msec(300);
			} else if(joy1Btn(Btn8) && !liftCondition) {
			motor[leftIntake] = -50;
			motor[rightIntake] = -50;
			liftCondition = true;
			wait1Msec(300);
			} else if (liftCondition && (joy1Btn(Btn8) || joy1Btn(Btn6))){
			motor[leftIntake] = 0;
			motor[rightIntake] = 0;
			liftCondition = false;
			wait1Msec(300);
		}
	}
}
task init () {
	while(true){
		if(SensorValue[touch]==1){
			motor[leftLift]=30;
			motor[rightLift]=-30;
		}
	}
}

task main() { //Main task for code

	//Initialize Motors

	/*motor[leftLift] = 1;
	motor[rightLift] = -1;
	wait1Msec(2000);
	motor[leftLift] = 0;
	motor[rightLift] = 0;
	*/

	//StartTask(init);

	waitForStart();

	//StopTask(init);


	nMotorEncoder[leftLift] = 0;
	nMotorEncoder[rightLift] = 0;

	//bool liftCondition = false;
	//int height = 1;
	//int liftTarget;
	startTask(intake);
	startTask(hook);

	//startTask(lift);

	while(true) {

		//Get joytick settings and positions
		getJoystickSettings(joystick);


		//Set left wheels
		motor[leftWheel1] = joystick.joy1_y1;
		motor[leftWheel2] = joystick.joy1_y1;

		//Set right wheels
		motor[rightWheel1] = joystick.joy1_y2;
		motor[rightWheel2] = joystick.joy1_y2;

		if(joy1Btn(Btn5)&& nMotorEncoder[leftLift]>-3700){
			motor[leftLift]=-127;
			motor[rightLift]=127;
			} else if(joy1Btn(Btn7) && nMotorEncoder[leftLift]<-10){
			motor[leftLift]=100;
			motor[rightLift]=-100;
			} else {
			motor[leftLift] = 0;
			motor[rightLift] = 0;
		}
		displayCenteredBigTextLine(1, "%d, %d", nMotorEncoder[leftLift], nMotorEncoder[rightLift]);


	}
}

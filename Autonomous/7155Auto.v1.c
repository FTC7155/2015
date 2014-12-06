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

#pragma systemFile

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///////////// Harvard-Westlake Middle School Robotics Team              /////////////
///////////// FTC7155                                                   /////////////
///////////// Autonomous Code                                           /////////////
/////////////                                                           /////////////
///////////// Authors:  Jonathan Damico, Nomi Ringoach, Sebastian Ko    /////////////
/////////////           Jack Reily, Alex Kahn                           /////////////
///////////// Version:  1                                               /////////////
///////////// Since:    November 3, 2014                                /////////////
///////////// Revised:  December 1, 2014                                /////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#include "drivers/hitechnic-sensormux.h"	// just files to make the SMUX work.
#include "drivers/hitechnic-irseeker-v2.h"

//SMUX prob wont work needs fixes
const tMUXSensor leftIR = msensor_S3_3;
const tMUXSensor rightIR = msensor_S3_1;
const tMUXSensor touch = msensor_S3_2;

//////////////////////////////////////////////////////////////////////////////////////
/////									            AUTO SETUP				                             /////
//////////////////////////////////////////////////////////////////////////////////////
/////Change this depending if the robot is starting on the ramp or on the ground./////
/* */bool startOnRamp = true;																									   /////
/////																																						 /////
/////Use this if we want to knock down the cascade.														   /////
/* */bool knockDownCascade = true;																							 /////
/////																																						 /////
/////Set True if we want to score a goal.																				 /////
/* */bool scoreInGoal = true;																										 /////
//////////////////////////////////////////////////////////////////////////////////////

//Recursion
int leftHistory[1], rightHistory[1], numberOfSteps, changeInTime;

//Converts meters to an encoder value
//#Needs Calibration#//
float toEncoderValues (float inches){
	inches*=90;
	return(inches);
}

//Sets all of the left wheels to a value
void setAllLeftMotors (int speed) {
	motor[leftWheel1] = speed;
	motor[leftWheel2] = speed;
}

//Sets all of the right wheels to a value
void setAllRightMotors (int speed) {
	motor[rightWheel1] = speed;
	motor[rightWheel2] = speed;
}

//Sets all of the wheels to a value
void setAllMotors(int speed) {
	setAllLeftMotors(speed);
	setAllRightMotors(speed);
}

//Sets all of the left wheels encoders to a value
void setAllLeftMotorEncoders (float encoderValue) {
	nMotorEncoder[leftWheel1] = encoderValue;
	nMotorEncoder[leftWheel2] = encoderValue;
}

//Sets all of the right wheel encoders to a value
void setAllRightMotorEncoders (float encoderValue) {
	nMotorEncoder[rightWheel1] = encoderValue;
	nMotorEncoder[rightWheel2] = encoderValue;
}

//Sets all of the base encoders to a value
void setAllMotorEncoders(float encoderValue) {
	setAllLeftMotorEncoders(encoderValue);
	setAllRightMotorEncoders(encoderValue);
}

//Sets all of the base encoders to a value
void setAllMotorEncoderTargets(int target) {
	nMotorEncoderTarget[rightWheel1] = target;
	nMotorEncoderTarget[leftWheel1] = target;
}

//Sets both sides of lift motors to the desired speed
void setAllLiftMotors (float speed) {
	motor[leftLift]=-speed;
	motor[rightLift]=speed;
}

//Used to tell the robot to drive a certain distance
void drive (int target) {
	setAllMotorEncoders(0);
	if(target>0){
		setAllMotors(30);
		while((nMotorEncoder[leftWheel1] < target) && (nMotorEncoder[rightWheel1] < target)) {
			if(nMotorEncoder[leftWheel1]<nMotorEncoder[rightWheel1]) {
				motor[rightWheel1]+=10;
				motor[rightWheel2]+=10;
				} else if(nMotorEncoder[leftWheel1]>nMotorEncoder[rightWheel1]) {
				motor[leftWheel1]+=10;
				motor[leftWheel2]+=10;
				} else {
				setAllMotors(30);
			}
		}
	} else {
		setAllMotors(-30);
		while(nMotorRunState[leftWheel1] == runStateRunning && nMotorRunState[rightWheel1] == runStateRunning) {
			/*if(nMotorEncoder[leftWheel1]<nMotorEncoder[rightWheel1]) {
				motor[leftWheel1]+=10;
				motor[leftWheel2]+=10;
				} else if(nMotorEncoder[leftWheel1]<nMotorEncoder[rightWheel1]) {
				motor[rightWheel1]+=10;
				motor[rightWheel2]+=10;
				} else {
				setAllMotors(30);
			}*/
		}
	}
	setAllMotors(0);
}

void setAllLiftMotorEncoderTargets (int value) {
	nMotorEncoderTarget[leftLift] = value;
	nMotorEncoderTarget[rightLift] = value;
}

//Used to turn a number of degrees
//#Needs Calibration#//
void turn(int degrees) {
	float distance = degrees/2*PI;
	if(degrees>0){
		nMotorEncoderTarget[leftWheel1] += distance;
		nMotorEncoderTarget[rightWheel1] -= distance;
		setAllLeftMotors(75);
		setAllRightMotors(-75);
		} else {
		nMotorEncoderTarget[leftWheel1] -= distance;
		nMotorEncoderTarget[rightWheel1] += distance;
		setAllLeftMotors(-75);
		setAllRightMotors(75);
	}
	while(nMotorRunState[leftWheel1]!=runStateIdle) {}
	setAllMotors(0);
}

void lift (int position) {
	int target;
	if(position==1)
		target=720;
	else if(position==2)
		target=1200;
	else if(position==3)
		target=2000;
	setAllLiftMotorEncoderTargets(target);
	if(nMotorEncoderTarget[leftLift]<nMotorEncoder[leftLift])
		setAllLiftMotors(-75);
	else
		setAllLiftMotors(75);
}

//Used to drive off the ramp, activated by the public boolean instance field, startOnRamp
void driveOffRamp() {
	drive(70);
	turn(-90);
	drive(47);
}

//Used to drive to the IR Beacon
//#Needs Calibration#//
void driveToIR() {
	while(SensorValue[leftIR]!=7 && SensorValue[rightIR]!=3){
		while(SensorValue[leftIR]==0 || SensorValue[rightIR]==0) {
			setAllLeftMotors(-50);
			setAllRightMotors(50);
		}
		while(SensorValue[leftIR]<5 && SensorValue[leftIR]!=0) {
			setAllLeftMotors(-50);
			setAllRightMotors(50);
		}
		while(SensorValue[rightIR]>5 && SensorValue[rightIR]!=0) {
			setAllLeftMotors(50);
			setAllRightMotors(-50);
		}
		setAllMotors(50);
	}

}

//Deposit the balls into the high goal on the center field structure.
void depositBalls() {
	//Jack
	//Make lift go up (Below)
	lift(36);
	wait1Msec(2000);
	lift(-36);
}

//Move to the goal so we can pick it hookUpGoal
void moveToGoal() {
	//Sebastian
	turn(135);
	drive(23);
}

//pick up the goal
void hookUpGoal() {
	servo[leftHook]=65;
	servo[rightHook]=160;
}

//unhook the goal from the robot
void unhookGoal() {
	servo[leftHook]=155;
	servo[rightHook]=65;
}

//move the goal to the parking zone
//Alex
void moveGoalToZone() {
	drive(32);
}

void driveToCascade () {
	turn(-90);
	drive(12);
	turn(90);
	drive(12);
}

void driveBackFromCascade () {
	turn(-180);
	drive(36);
	turn(-90);
}

/*
Idea: It might be better to record the current endocer turns, and subtract on the way down.
*/

task recursionRecorder () {
	int numberOfSteps = 0;
	int changeInTime = 20;

	while(true) {
		leftHistory[numberOfSteps] = motor[leftWheel1];
		rightHistory[numberOfSteps] = motor[rightWheel1];
		numberOfSteps++;
		wait1Msec(changeInTime);
	}
}

void recursionPlayback () {
	stopTask(recursionRecorder);
	while(--numberOfSteps>0) {
		setAllRightMotors(-rightHistory[numberOfSteps]);
		setAllLeftMotors(-leftHistory[numberOfSteps]);
		wait1Msec(changeInTime);
	}
}

task main() {
	nMotorEncoder[leftLift] = 0;
	nMotorEncoder[rightLift] = 0;
	while(nMotorEncoder[leftLift]>-100) {
		motor[leftLift]=-127;
		motor[rightLift]=127;
	}
	motor[leftLift] = 0;
	motor[rightLift] = 0;
	setAllMotors(127);
	wait1Msec(1500);
	setAllMotors(50);
	wait1Msec(200);
	setAllMotors(0);
	while(nMotorEncoder[leftLift]>-3000) {
		setAllLiftMotors(127);
	}
	setAllLiftMotors(0);
	setAllMotors(20);
	wait1Msec(1200);
	setAllMotors(0);
	motor[leftIntake] = -60;
	motor[rightIntake] = -60;
	wait1Msec(1500);
	motor[leftIntake] = 0;
	motor[rightIntake] = 0;

	//driveOffRamp();
	/*
	bSystemLeaveServosEnabledOnProgramStop=true;
	if(startOnRamp)
	driveOffRamp();
	if(knockDownCascade) {
	startTask(recursionRecorder);
	driveToIR();
	driveToCascade();
	recursionPlayback();
	}
	if(scoreInGoal) {
	moveToGoal();
	hookUpGoal();
	moveGoalToZone();
	unhookGoal();
	}
	*/
}

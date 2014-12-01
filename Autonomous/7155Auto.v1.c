#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     SMUX,           sensorI2CCustom)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          leftIntake,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightIntake,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightWheel2,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     leftLift,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     rightLift,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S4_C1_1,     leftWheel1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     rightWheel1,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_1,     leftWheel2,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    hook,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
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
///////////// Revised:  November 20, 2014                               /////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#include "drivers/hitechnic-sensormux.h"	// just files to make the SMUX work.
#include "drivers/hitechnic-irseeker-v2.h"

//SMUX prob wont work needs fixes
const tMUXSensor leftIR = msensor_S3_1;
const tMUXSensor rightIR = msensor_S3_2;

//Change this depending if the robot is starting on the ramp or on the ground.
bool startOnRamp = true;

//Converts meters to an encoder value
//#Needs Calibration#//
float toEncoderValues (float inches){
	inches*=90;
	return(inches);
}

//Sets all of the left wheels to a value
void setAllLeftMotors (float speed) {
	motor[leftWheel1] = speed;
	motor[leftWheel2] = speed;
}

//Sets all of the right wheels to a value
void setAllRightMotors (float speed) {
	motor[rightWheel1] = speed;
	motor[rightWheel2] = speed;
}

//Sets all of the wheels to a value
void setAllMotors(float speed) {
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

//Sets all of the left wheels encoders to a value
void setAllLeftMotorEncoderTargets (float target) {
	nMotorEncoderTarget[leftWheel1] = target;
	nMotorEncoderTarget[leftWheel2] = target;
}

//Sets all of the right wheel encoders to a value
void setAllRightMotorEncoderTargets (float target) {
	nMotorEncoderTarget[rightWheel1] = target;
	nMotorEncoderTarget[rightWheel2] = target;
}

//Sets all of the base encoders to a value
void setAllMotorEncoderTargets(float target) {
	setAllLeftMotorEncoderTargets(target);
	setAllRightMotorEncoderTargets(target);
}

//Sets both sides of lift motors to the desired speed
void setAllLiftMotors (float speed) {
	motor[leftLift]=speed;
	motor[rightLift]=speed;
}

//Used to tell the robot to drive a certain distance
void drive (float inches) {
	setAllMotorEncoders(0);
	setAllMotorEncoderTargets(toEncoderValues(inches));
	setAllMotors(50);
	while(nMotorRunState[leftWheel1] != runStateIdle) {}
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
	servo[hook]=180;
}

//unhook the goal from the robot
void unhookGoal() {
	servo[hook]=90;
}

//move the goal to the parking zone
void moveGoalToZone() {
	//Alex
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

task main() {
	if(startOnRamp)
		driveOffRamp();
	driveToIR();
	driveToCascade();
	driveBackFromCascade();
	moveToGoal();
	hookUpGoal();
	moveGoalToZone();
	unhookGoal();

}

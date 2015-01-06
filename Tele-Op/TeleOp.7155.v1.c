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
#pragma config(Servo,  srvo_S1_C1_3,    leftTip,              tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    rightTip,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_5,    VRCD,                 tServoContinuousRotation)
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

//Task to control all the movement of the hook for the robot during tele-op
task tip () {

	//Boolean statement to determine if the hook is up. Initilization.
	bool tipUp = false;

	//Loop this part of the code forever
	while(true) {

		//Put hook up
		if(joy1Btn(Btn3)&&!tipUp) { 	//If the A Button is pressed, and the hook isn't up
			servo[leftTip]=155;				//Set left hook to up position
			servo[rightTip]=65;				//Set right hook to up position
			tipUp=true;								//Tell the program that the hook is up
			wait1Msec(300);							//Wait so that we can give the hook time to go up, and so the button doesn't get "stuck"
		}

		//Put hook down
		if(joy1Btn(Btn3)&&tipUp) {
			servo[leftTip]=50;
			servo[rightTip]=173;
			tipUp=false;
			//while(joy1Btn(Btn2)) {}
			wait1Msec(300);
		}
	}
}

task intake () {

	bool liftCondition = false;

	while(true) {
		//Control for Intake
		if(joy1Btn(Btn6) && !liftCondition){
			motor[leftIntake] = 75;
			motor[rightIntake] = 75;
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

task imposs () {
	//        100 = Tempo
	//          6 = Default octave
	//    Quarter = Default note length
	//        10% = Break between notes
	//
	PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
	PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
	PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
	PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
	PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
	PlayTone(  988,    7); wait1Msec(  75);  // Note(E, Duration(32th))
	PlayTone( 1047,    7); wait1Msec(  75);  // Note(F, Duration(32th))
	PlayTone( 1109,    7); wait1Msec(  75);  // Note(F#, Duration(32th))
	PlayTone( 1175,    7); wait1Msec(  75);  // Note(G, Duration(32th))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
	PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	PlayTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(16th))
	PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	PlayTone( 1109,   14); wait1Msec( 150);  // Note(F#, Duration(16th))
	PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
	PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	PlayTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(16th))
	PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	PlayTone( 1109,   14); wait1Msec( 150);  // Note(F#, Duration(16th))
	PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(  880,  108); wait1Msec(1200);  // Note(D, Duration(Half))
	PlayTone(    0,    7); wait1Msec(  75);  // Note(Rest, Duration(32th))
	PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(  831,  108); wait1Msec(1200);  // Note(C#, Duration(Half))
	PlayTone(    0,    7); wait1Msec(  75);  // Note(Rest, Duration(32th))
	PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
	PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	PlayTone(  784,  108); wait1Msec(1200);  // Note(C, Duration(Half))
	PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	PlayTone(  932,   14); wait1Msec( 150);  // Note(A#5, Duration(16th))
	PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	StopTask(imposs);
}

void wheels () {
	//Set left wheels
	motor[leftWheel1] = joystick.joy1_y1;
	motor[leftWheel2] = joystick.joy1_y1;

	//Set right wheels
	motor[rightWheel1] = joystick.joy1_y2;
	motor[rightWheel2] = joystick.joy1_y2;

}

bool lift (bool limits) {
	if(joy1Btn(Btn10)) {
		limits = false;
		playTone(1000, 10);
	}
	if(joy1Btn(Btn9)) {
		nMotorEncoder[leftLift] = 0;
		limits = true;
		playTone(1500, 10);
	}

	if(limits){
		if(joy1Btn(Btn5)&& nMotorEncoder[leftLift]>-3150){
			motor[leftLift]=-127;
			motor[rightLift]=127;
			} else if(joy1Btn(Btn7) && nMotorEncoder[leftLift]<-10){
			motor[leftLift]=100;
			motor[rightLift]=-100;
			} else {
			motor[leftLift] = 0;
			motor[rightLift] = 0;
		}
		} else {
		if(joy1Btn(Btn5)) {
			motor[leftLift]=-127;
			motor[rightLift]=127;
			} else if(joy1Btn(Btn7)){
			motor[leftLift]=100;
			motor[rightLift]=-100;
			} else {
			motor[leftLift] = 0;
			motor[rightLift] = 0;
		}
	}
	displayCenteredBigTextLine(1, "%d, %d", nMotorEncoder[leftLift], nMotorEncoder[rightLift]);

	return limits;
}

void fun () {
	if(joy1Btn(Btn4))
		startTask(imposs);
}

task main() { //Main task for code

	bool limits = true;

	waitForStart();

	playSound(soundFastUpwardTones);

	nMotorEncoder[leftLift] = 0;
	nMotorEncoder[rightLift] = 0;

	startTask(intake);
	startTask(hook);
	startTask(tip);

	while(true) {

		//Get joytick settings and positions
		getJoystickSettings(joystick);

		fun();
		wheels();
		limits = lift(limits);

	}
}

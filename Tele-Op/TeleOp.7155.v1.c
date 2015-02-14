#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     pretake,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     lift1,         tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     lift2,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     leftWheel1,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     leftWheel2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C2_1,     rightWheel1,   tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C2_2,     rightWheel2,   tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S3_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_4,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S3_C1_5,    leftHook,             tServoStandard)
#pragma config(Servo,  srvo_S3_C1_6,    waterspout,           tServoStandard)
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

void putHookUp () {
	servo[leftHook]=207;				//Set left hook to up position
	servo[rightHook]=52;				//Set right hook to up position
}

void putHookDown() {
	servo[leftHook]=73;
	servo[rightHook]=174;
}

void waterspoutRelease () {
	servo[waterspout] = 62;
}

void waterspoutCatch () {
	servo[waterspout] = 165;
}

void waterspoutStart () {
	servo[waterspout] = 255;
}

//Task to control all the movement of the hook for the robot during tele-op
task hook () {

	//Boolean statement to determine if the hook is up. Initilization.
	bool hookUp = false;
	bool spoutCatch = true;

	//Loop this part of the code forever
	while(true) {

		//Put hook up
		if(joy1Btn(Btn2)&&!hookUp) { 	//If the A Button is pressed, and the hook isn't up
			putHookUp();
			hookUp=true;								//Tell the program that the hook is up
			wait1Msec(300);							//Wait so that we can give the hook time to go up, and so the button doesn't get "stuck"
		}

		//Put hook down
		if(joy1Btn(Btn2)&&hookUp) {
			putHookDown();
			hookUp=false;
			//while(joy1Btn(Btn2)) {}
			wait1Msec(300);
		}

		if(joy1Btn(Btn3)&&!spoutCatch) {
			waterspoutCatch();
			spoutCatch=true;
			wait1Msec(300);
		}

		if(joy1Btn(Btn3)&&spoutCatch) {
			waterspoutRelease();
			spoutCatch=false;
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
	playTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	playTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
	playTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	playTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
	playTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	playTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
	playTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	playTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
	playTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	playTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
	playTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
	playTone(  988,    7); wait1Msec(  75);  // Note(E, Duration(32th))
	playTone( 1047,    7); wait1Msec(  75);  // Note(F, Duration(32th))
	playTone( 1109,    7); wait1Msec(  75);  // Note(F#, Duration(32th))
	playTone( 1175,    7); wait1Msec(  75);  // Note(G, Duration(32th))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	playTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
	playTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	playTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	playTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	playTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(16th))
	playTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	playTone( 1109,   14); wait1Msec( 150);  // Note(F#, Duration(16th))
	playTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	playTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
	playTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	playTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	playTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
	playTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(16th))
	playTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	playTone( 1109,   14); wait1Msec( 150);  // Note(F#, Duration(16th))
	playTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	playTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(  880,  108); wait1Msec(1200);  // Note(D, Duration(Half))
	playTone(    0,    7); wait1Msec(  75);  // Note(Rest, Duration(32th))
	playTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(  831,  108); wait1Msec(1200);  // Note(C#, Duration(Half))
	playTone(    0,    7); wait1Msec(  75);  // Note(Rest, Duration(32th))
	playTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
	playTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
	playTone(  784,  108); wait1Msec(1200);  // Note(C, Duration(Half))
	playTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
	playTone(  932,   14); wait1Msec( 150);  // Note(A#5, Duration(16th))
	playTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	stopTask(imposs);
}

void wheels () {
	if(abs(joystick.joy1_y1)>10) {
		//Set left wheels
		motor[leftWheel1] = joystick.joy1_y1;
		motor[leftWheel2] = joystick.joy1_y1;
		} else {
		motor[leftWheel1] = 0;
		motor[leftWheel2] = 0;
	}

	if(abs(joystick.joy1_y2)>10) {
		//Set right wheels
		motor[rightWheel1] = joystick.joy1_y2;
		motor[rightWheel2] = joystick.joy1_y2;
		} else {
		motor[rightWheel1] = 0;
		motor[rightWheel2] = 0;
	}
}

bool lift (bool limits) {
	if(joy1Btn(Btn10)) {
		limits = false;
		playTone(1000, 10);
	}
	if(joy1Btn(Btn9)) {
		nMotorEncoder[lift1] = 0;
		limits = true;
		playTone(1500, 10);
	}

	if(limits){
		if(joy1Btn(Btn5)&& nMotorEncoder[lift1]>-3150){
			motor[lift1] = 127;
			motor[lift2] = 127;
			} else if(joy1Btn(Btn6) && nMotorEncoder[lift1]<-10){
			motor[lift1] = -100;
			motor[lift2] = -100;
			} else {
			motor[lift1] = 0;
			motor[lift2] = 0;
		}
		} else {
		if(joy1Btn(Btn5)) {
			motor[lift1] = 127;
			motor[lift2] = 127;
			} else if(joy1Btn(Btn6)){
			motor[lift1] = -100;
			motor[lift2] = -100;
			} else {
			motor[lift1] = 0;
			motor[lift2] = 0;
		}
	}
	//displayCenteredBigTextLine(1, "%d, %d", nMotorEncoder[lift1], nMotorEncoder[lift2]);

	return limits;
}

void fun () {
	if(joy1Btn(Btn4))
		startTask(imposs);
}

task badger {
	bool badgerOn = false;
	bool badgerIn = false;
	//Loop this part of the code forever
	while(true) {
		if(joy1Btn(Btn8)&&!badgerOn) {
			motor[intake] = 127;
			motor[pretake] = 127;
			badgerOn=true;
			badgerIn = true;
			wait1Msec(300);
		} else if(joy1Btn(Btn7)&&!badgerOn) {
			motor[intake] = -127;
			motor[pretake] = -127;
			badgerOn=true;
			badgerIn = false;
			wait1Msec(300);
		} else if((joy1Btn(Btn7) || joy1Btn(Btn8)) && badgerOn) {
			motor[intake] = 0;
			motor[pretake] = 0;
			badgerOn=false;
			badgerIn=false;
			wait1Msec(300);
		}
		if(nMotorRunState[intake] == runStateIdle&&badgerOn){
			if(badgerIn){
				motor[intake] = -30;
				wait1Msec(200);
				motor[intake] = 127;
			} else {
				motor[intake] = 30;
				wait1Msec(200);
				motor[intake] = -127;
			}
		}
	}
}

void init() {
	putHookDown();
	waterspoutStart();
}

task main() { //Main task for code

	bool limits = true;

	init();

	waitForStart();


	playSound(soundFastUpwardTones);

	startTask(hook);
	startTask(badger);

	while(true) {

		//Get joytick settings and positions
		getJoystickSettings(joystick);

		fun();
		wheels();
		limits = lift(limits);

		wait1Msec(25);
	}
}

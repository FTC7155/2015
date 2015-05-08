 #pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     pretake,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     lift1,         tmotorTetrix, openLoop, encoder)
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

void setAllLeftWheels (int target) {
	motor[leftWheel1] = target;
	motor[leftWheel2] = target;
}

void setAllRightWheels (int target) {
	motor[rightWheel1] = target;
	motor[rightWheel2] = target;
}

void setAllWheels (int target) {
	setAllLeftWheels(target);
	setAllRightWheels(target);
}
void setAllLifts (int target) {
	motor[lift1] = target;
	motor[lift2] = target;
}

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

void setLift (int target) {
	bool okay = false;
	while(!okay) {
		int test = abs(nMotorEncoder[lift1]);
		int adjTarget = abs(target);
		if(nMotorEncoder[lift1]>target) {
			setAllLifts(100);
			} else if (nMotorEncoder[lift1]<target) {
			setAllLifts(-100);
			} else if ((test>(adjTarget-10)) && (test<(adjTarget+10))) {
			setAllLifts(0);
		}
	}
}

void driveStraight (int distance) {
	nMotorEncoder[leftWheel1] = 0;
	nMotorEncoder[rightWheel2] = 0;
	int thirds = distance/3;
	int traveled = thirds;
	while(nMotorEncoder[rightWheel2]<traveled) {
		setAllRightWheels(50);
		setAllLeftWheels(43);
		displayCenteredTextLine(1, "%d, %d", nMotorEncoder[rightWheel2], traveled);
	}
	traveled+=thirds;
	while(nMotorEncoder[rightWheel2]<traveled) {
		setAllLeftWheels(20);
		setAllRightWheels(25);
		displayCenteredTextLine(1, "%d, %d", nMotorEncoder[rightWheel2], traveled);
	}
	traveled+=thirds;
	while(nMotorEncoder[rightWheel2]<traveled) {
		setAllLeftWheels(7);
		setAllRightWheels(10);
		displayCenteredTextLine(1, "%d, %d", nMotorEncoder[rightWheel2], traveled);
	}
}

void driveBackwards (int distance) {
	nMotorEncoder[leftWheel1] = 0;
	nMotorEncoder[rightWheel2] = 0;
	int fifths = distance/5;
	int traveled =	0 - fifths;
	while(nMotorEncoder[rightWheel2]>traveled) {
		setAllRightWheels(-50);
		setAllLeftWheels(-43);
		displayCenteredTextLine(1, "%d, %d", nMotorEncoder[rightWheel2], traveled);
	}
	traveled-=2*fifths;
	while(nMotorEncoder[rightWheel2]>traveled) {
		setAllLeftWheels(-20);
		setAllRightWheels(-25);
		displayCenteredTextLine(1, "%d, %d", nMotorEncoder[rightWheel2], traveled);
	}
	traveled-=2*fifths;
	while(nMotorEncoder[rightWheel2]>traveled) {
		setAllLeftWheels(-7);
		setAllRightWheels(-10);
		displayCenteredTextLine(1, "%d, %d", nMotorEncoder[rightWheel2], traveled);
	}
}


void putUpLift() {
	nMotorEncoder[lift1] = 0;

	while(nMotorEncoder[lift1]<5000){
		setAllLifts(100);
	}
}

void turnToParkingZone() {
	setAllLeftWheels(50);
	wait1Msec(100);
	setAllWheels(0);
}

void moveToParkingZone() {
	nMotorEncoder[leftWheel1] = 0;
	nMotorEncoder[rightWheel1] = 0;

	float Kp = 0.5;
	float Ki = 0.2;
	float Kd = 0.1;
	int targetValue = 300; //Calib Needed
	float error, speed, integral, derivative, previousError = 0;
	while(true) {
		//P
		error = targetValue - nMotorEncoder[leftWheel1];

		//I
		integral += error;

		if(error == 0 || abs(error) > 40)
			integral=0;

		//D
		derivative = error-previousError;

		previousError = error;

		setAllWheels(Kp * error + Ki * integral + Kd * derivative);
	}
}
void imposs () {
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
  return;
}
task main()
{
	waterspoutCatch();
	putHookUp();
	waitForStart();
	imposs();
}

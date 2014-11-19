#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightWheel2,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorF,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     leftWheel1,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     rightWheel1,   tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     leftWheel2,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_2,     motorK,        tmotorTetrix, openLoop)
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
 Revised November 3, 2014
*/

#include "HTIRS2-driver.h"

//Change this depending if the robot is starting on the ramp or on the ground.
public bool startOnRamp = true;

//Converts meters to an encoder value
//#Needs Calibration#//
float toInches (float inches){

}

//Used to turn a number of degrees
//#Needs Calibration#//
void turn(int degrees) {

}

//Sets all of the left wheels to a value
void setAllLeftMotors (float speed) {
    motor[leftWheel1] = speed;
    motor[leftwheel2] = speed;
}

//Sets all of the right wheels to a value
void setAllRightMotors (float speed) {
    motor[rightWheel1] = speed;
    motor[rightwheel2] = speed;
}

//Sets all of the wheels to a value
void setAllMotors(float speed) {
    setAllLeftMotors(speed);
    setAllRightMotors(speed);
}

//Used to tell the robot to drive a certain distance
void drive (float inches) {
    setAllMotors(100);
    wait1MSec(toInches(inches));
    setAllMotors(0);
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
    while(sensor[leftIR]!=7 && sensor[rightIR]!=3){
        while(sensor[leftIR]=0 || sensor[rightIR]=0) {
            setAllLeftMotors(-50);
            setAllRightMotors(50);
        }
        while(sensor[leftIR]<5 && sensor[leftIR]!=0) {
            setAllLeftMotors(-50);
            setAllRightMotors(50);
        }
        while(sensor[rightIR]>5 && sensor[rightIR]!=0) {
            setAllLeftMotors(50);
            setAllRightMotors(-50);
        }
        setAllMotors(50);
    }

}

//Deposit the balls into the high goal on the center field structure.s
void depositBalls() {
    //Jack
}

//Move to the goal so we can pick it up
void moveToGoal() {
    //Sebastian
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

task main() {
    if(startOnRamp)
        driveOffRamp();
    driveToIR();
    depositBalls();
    knockBallsDown();
    moveToGoal();
    hookUpGoal();
    moveGoalToZone();

}

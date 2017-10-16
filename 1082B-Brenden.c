#pragma config(Sensor, dgtl1,  LeftDriveE,     sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  RightDriveE,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  BarE,           sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  LeftMobE,       sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  LeftTopL,       sensorTouch)
#pragma config(Sensor, dgtl10, RightTopL,      sensorTouch)
#pragma config(Sensor, dgtl11, RightMobE,      sensorQuadEncoder)
#pragma config(Motor,  port1,           BottomLeft,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           BackLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           FrontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           TopLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           TopRight,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           FrontRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           BackRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          BottomRight,   tmotorVex393_HBridge, openLoop, reversed)
#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

void pre_auton()
{
  bStopTasksBetweenModes = true;

}
void resetDrive(){//resets encoders - obvious
SensorValue[LeftDriveE] = 0;
SensorValue[RightDriveE] = 0;}

void resetMob(){//resets encoders - obvious
SensorValue[LeftMobE] = 0;
SensorValue[RightMobE] = 0;}

void reset(){//resets encoders - obvious
SensorValue[LeftDriveE] = 0;
SensorValue[RightDriveE] = 0;
SensorValue[LeftMobE] = 0;
SensorValue[RightMobE] = 0;}

void Mob(int speed){//change so that encoders will stay the same in here
motor[FrontLeft]  = speed;
motor[BackLeft]   = speed;
motor[FrontRight] = speed;
motor[BackRight]  = speed;}

void Move(int right,int left){//change movement so that the encoders will stay the same
motor[TopLeft]     = left;
motor[BottomLeft]  = left;
motor[TopRight]    = right;
motor[BottomRight] = right;
}

void PullBack(){//pulls mobile goal towards bot, change if going forward
Mob(-80);
waitUntil(SensorValue[RightTopL] == 1);
Mob(0);}

void PushForward(){
resetMob();
Mob(80);
waitUntil(SensorValue[RightMobE] >= 500);/*arbitrary number, change later*/
Mob(0);}

void linear(int distance,int speed){
resetDrive();
Move(speed,speed);
waitUntil(SensorValue[RightDriveE] >= distance);
Move(0,0);
}

void turn(int distance,int speed){//turns on the spot, and encoder value is checked with the positive one
resetDrive();
Move(speed,-speed);
if(speed >= 0){
waitUntil(SensorValue[LeftDriveE] >= distance);
}
else{
waitUntil(SensorValue[RightDriveE] >= distance);
}
Move(0,0);}

task autonomous()
{//use linear and turn for movement
AutonomousCodePlaceholderForTesting();//remove when making drive - we will be using the jumper
switch(SensorValue[/*Analog sensor*/]){
case 0:
blueAuton();
break;	
case 1:
redAuton();
break;
}}

task Drive(){
while(true){
motor[TopLeft]     = vexRT[Ch2] + vexRT[Ch1];
motor[BottomLeft]  = vexRT[Ch2] + vexRT[Ch1];
motor[TopRight]    = vexRT[Ch2] - vexRT[Ch1];
motor[BottomRight] = vexRT[Ch2] - vexRT[Ch1];
}}

task Mobile(){
while(true){
motor[FrontLeft]  = vexRT[Ch3];
motor[BackLeft]   = vexRT[Ch3];
motor[FrontRight] = vexRT[Ch3];
motor[BackRight]  = vexRT[Ch3];
if (vexRT[Ch3] >= 10 && SensorValue[RightTopL] == 1){//keeps it up unless you pull back, reduces strain on motors
Mob(10);
}}}

task usercontrol()
{
startTask(Drive);
startTask(Mobile);
waitUntil(false);
}

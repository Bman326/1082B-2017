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


task autonomous()
{
AutonomousCodePlaceholderForTesting();
}
task drive(){
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
}}

task usercontrol()
{
startTask(drive);
startTask(Mobile);
waitUntil(false);
}

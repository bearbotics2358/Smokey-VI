
/*
 * Position Tracking Class
 *  
 * This class tracks the position of the robot
 * based on its starting point, this class requires
 * the speed jaguars for encoder readings and the
 * gyro for angle of robot
 * 
 */

#include "PositionTracker.h"

//Constructor
PositionTracker::PositionTracker(CANJaguar *lfJaguar, CANJaguar *lbJaguar, CANJaguar *rfJaguar, CANJaguar *rbJaguar, BBGyro *gyro)
{

	a_robotX = 0.0;
	a_robotY = 0.0;
	ap_lfJaguar = lfJaguar;
	ap_lbJaguar = lbJaguar;
	ap_rfJaguar = rfJaguar;
	ap_rbJaguar = rbJaguar;
	ap_gyro = gyro;
}

//Destructor
PositionTracker::~PositionTracker(void)
{

	ap_lfJaguar = NULL;
	ap_lbJaguar = NULL;
	ap_rfJaguar = NULL;
	ap_rbJaguar = NULL;
	ap_gyro = NULL;
}

//Updates the position tracker; must be called every cycle
void PositionTracker::Update()
{
	double inputGyroAngle = ap_gyro->GetOffsetAngle();
	double avgEncDelta = (3.14159265/32000) * (ap_rfJaguar->GetSpeed() + ap_lfJaguar->GetSpeed() + ap_rbJaguar->GetSpeed() + ap_lbJaguar->GetSpeed()); //converted from rpm to feet per cycle (50 cycles = 1 second, diameter = 4.5 in) 
	
	double deltaX = avgEncDelta * sin(inputGyroAngle);
	double deltaY = avgEncDelta * cos(inputGyroAngle);

	a_robotX += deltaX;
	a_robotY += deltaY;
	
	printf("x: %f\ty: %f\n", a_robotX, a_robotY);
}

//Resets the position and gyro
void PositionTracker::Reset(void)
{
	a_robotX = 0.0;
	a_robotY = 0.0;
	
	ap_gyro->Reset();
}

//Returns the X coordinate of the robot
double PositionTracker::GetRobotX(void)
{
	return a_robotX;
}

//Returns the Y coordinate of the robot
double PositionTracker::GetRobotY(void)
{
	return a_robotY;
}


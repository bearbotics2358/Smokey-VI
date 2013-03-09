/*
 * Bearbotics Gyro Class
 *  
 * This hosts the code for reading 
 * and preforming calculations with
 * the gyroscope data
 *
 */

#include "BBGyro.h"

//Constructor
BBGyro::BBGyro(bool verbose)
:Gyro(GYRO_PORT)
{	
	a_verbose = verbose;
	a_gyroOffset = 0.0;
	a_gyroAngle = 0.0;
}

//Destructor
BBGyro::~BBGyro()
{
	this->~Gyro();
	
}

//Updates the BBGyro; Must be called every teleop cycle
void BBGyro::Update()
{
	double gyroAngle = this->GetAngle();
	
	if(a_gyroOffset == 0.0){
		a_gyroOffset = -1 * gyroAngle;
	}
	a_gyroAngle +=a_gyroOffset;
	while(gyroAngle > 360.0)
			gyroAngle -= 360.0;
		while(gyroAngle < -360.0)
			gyroAngle += 360.0;
	if(a_verbose == true){
		printf("Gyro Angle: %f\n", gyroAngle);
	}
	
	a_gyroAngle = gyroAngle; // * 3.14159265 / 180.0;
}

//Returns the offsetted angle retrieved from the gyro
double BBGyro::GetOffsetAngle()
{
	return a_gyroAngle;
}

void BBGyro::Reset()
{
	a_gyroOffset = 0.0;
	a_gyroAngle = 0.0;
	Gyro::Reset();
}

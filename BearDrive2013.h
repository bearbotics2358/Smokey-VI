#ifndef _BEAR_DRIVE_2013_H_
#define _BEAR_DRIVE_2013_H_

#include <Joystick.h>
#include <CANJaguar.h>
#include <PIDController.h>
#include <math.h>

#include "BBPIDController.h"
#include "MagEncoder.h"
#include "BBGyro.h"
#include "Prefs.h"

class BearDrive2013
{
	public:
		BearDrive2013( Joystick *driveStick,  BBGyro *gyro);
		~BearDrive2013(void);
		
		void Enable(void);
		void Disable(void);
		void Update(void);
	
		void CalcSwerve_FullRotation(double joyX, double joyY, double joyAngle, double wheelAngle, double gyroAngle, double *angleOut, double *speedOut);

	private:
	
		double a_counter;

		Joystick *ap_driveStick;
		BBGyro *ap_gyro;

		CANJaguar *ap_lbDrive;
		CANJaguar *ap_lfDrive;
		CANJaguar *ap_rbDrive;
		CANJaguar *ap_rfDrive;

		CANJaguar *ap_lbSwerve;
		BBPIDController *ap_lbSwerveController;
		AnalogChannel *ap_lbPIDSource;
	
		CANJaguar *ap_lfSwerve;
		BBPIDController *ap_lfSwerveController;
		AnalogChannel *ap_lfPIDSource;
	
		CANJaguar *ap_rbSwerve;
		BBPIDController *ap_rbSwerveController;
		AnalogChannel *ap_rbPIDSource;
	
		CANJaguar *ap_rfSwerve;
		BBPIDController *ap_rfSwerveController;
		AnalogChannel *ap_rfPIDSource;


};
#endif  // _BEAR_DRIVE_2013_H_

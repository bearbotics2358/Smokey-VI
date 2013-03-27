#ifndef _BEAR_DRIVE_2013_H_
#define _BEAR_DRIVE_2013_H_

#include <Joystick.h>
#include <CANJaguar.h>
#include <PIDController.h>
#include <math.h>

//#include "PositionTracker.h"
#include "BBPIDController.h"
#include "MagEncoder.h"
#include "BBGyro.h"
#include "Prefs.h"
#include "configPID.h"
#include "configDbl.h"
#include "configAuto.h"
#include "twirl_speed.h"

// angle of drive wheel locations
#define ANGLE_RF 51.8
#define ANGLE_RB 128.2
#define ANGLE_LB 231.8
#define ANGLE_LF 308.2

class BearDrive2013
{
	public:
		BearDrive2013( Joystick *driveStick,  BBGyro *gyro);
		~BearDrive2013(void);
		
		void Enable(void);
		void Disable(void);
		void Update(void);
	
		void AutonDrive(double dx, double dy);
		void AutonUpdate();
		void AutonEnable();

		void CalcSwerve_FullRotation(double joyX, double joyY, double joyAngle, double wheelAngle, double gyroAngle, double *angleOut, double *speedOut);


	private:
	
		UINT8 mode; //0 for skid, 1 for swerve

		double a_dyBuffer;
		double a_dxBuffer;


		double a_counter;

		Joystick *ap_driveStick;
		BBGyro *ap_gyro;

		configPID *ap_drivePID;
		configPID *ap_steeringPID;
		configAuto *ap_autoCfg;

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

	//	PositionTracker *ap_posTracker;
};
#endif  // _BEAR_DRIVE_2013_H_

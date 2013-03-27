#ifndef _SMOKEY_V_I_H_
#define _SMOKEY_V_I_H_

#include <IterativeRobot.h>
#include <Compressor.h>
#include <Joystick.h>
#include <time.h>
#include <timer.h>
//
#include "BearDrive2013.h"
#include "Prefs.h"
#include "Shooter.h"
#include "Feeder.h"
#include "Hanger.h"
#include "Camera.h"
#include "BBGyro.h"
#include "configAuto.h"

//#define Image_Processing

#if defined (Image_Processing)
#include "Vision2013/ImageProcessor.h"
#endif

class SmokeyVI : public IterativeRobot
{
	public:
		SmokeyVI(void);
		~SmokeyVI(void);
		
		
		/********************* Init Routines *********************/
		
		void RobotInit(void);
		void DisabledInit(void);
		void AutonomousInit(void);
		void TeleopInit(void);
		
		/********************* Periodic Routines *********************/
	
		void DisabledPeriodic(void);
		void AutonomousPeriodic(void);
		void TeleopPeriodic(void);
		
	private:
		typedef enum
		{
			AUTO_STATE_SHOOTING,
			AUTO_STATE_DELAY_1,
			AUTO_STATE_DELAY_2,
			AUTO_STATE_DELAY_3,
			AUTO_STATE_FEEDING,
			AUTO_STATE_RETRACTING,
			AUTO_STATE_IDLE,
			AUTO_STATE_MOVING,
		} AutonState;

	
		Joystick *ap_driveStick;
		Joystick *ap_shootStick;
		
		BearDrive2013 *ap_drive;
		Shooter *ap_shooter;
		//Camera *ap_camera;
		Compressor *ap_compressor;
		Hanger *ap_hanger;
		Feeder *ap_feeder;
		BBGyro *ap_gyro;
		configAuto *ap_configAuto;
		
		#if defined (Image_Processing)
		ImageProcessor *ap_ImageProcessor;
		#endif	
			
		AutonState a_state;

		int a_shotCounter;
	
		Timer *ap_autonTimer;
};

START_ROBOT_CLASS(SmokeyVI);

#endif //_SMOKEY_V_I_H_

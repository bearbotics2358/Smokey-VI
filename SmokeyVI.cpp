#include "SmokeyVI.h"

#define FILTER_SIZE (10)

SmokeyVI::SmokeyVI(void)
{
	#if defined (Image_Processing)
	ap_ImageProcessor = new ImageProcessor(true);
	#endif
	
	ap_driveStick = new Joystick(DRIVE_STICK_PORT);
	ap_shootStick = new Joystick(SHOOTER_STICK_PORT);
	ap_gyro = new BBGyro(false);
	ap_compressor = new Compressor(COMPRESSOR_SWITCH_PORT, COMPRESSOR_RELAY_PORT);
	ap_feeder = new Feeder(ap_driveStick);
	ap_hanger = new Hanger(ap_driveStick);
	//  ap_camera = new Camera(true);
	ap_autonTimer = new Timer();
	ap_shooter = new Shooter(ap_shootStick);
	ap_drive = new BearDrive2013(ap_driveStick, ap_gyro);

}
	
SmokeyVI::~SmokeyVI(void)
{
		
	 delete ap_drive;
	 ap_drive = NULL;
		
	delete ap_shooter;
	ap_shooter = NULL;

	delete ap_autonTimer;
	ap_autonTimer = NULL;
				
	// delete ap_camera;
	// ap_camera = NULL;
	
	delete ap_hanger;
	ap_hanger = NULL;
	
	delete ap_feeder;
	ap_feeder = NULL;
		
	delete ap_compressor;
	ap_compressor = NULL;
		
	delete ap_gyro;
	ap_gyro = NULL;
	
	delete ap_shootStick;
	ap_shootStick = NULL;
		
	delete ap_driveStick;
	ap_driveStick = NULL;

	#if defined (Image_Processing)
	delete ap_ImageProcessor;
	ap_ImageProcessor = NULL;
	#endif
	
}
	
// ********INIT ROUTINES*******//
void SmokeyVI::RobotInit(void)
{
	
}

void SmokeyVI::DisabledInit(void)
{
	ap_drive->Disable();
	ap_compressor->Stop();
}

void SmokeyVI::AutonomousInit(void)
{
	ap_autonTimer->Reset();
	ap_autonTimer->Start();	

}

void SmokeyVI::TeleopInit(void)
{
//	printf("working 1 \n");
	 ap_drive->Enable();
	#if defined (Image_Processing)
	printf("Camera Processing Enabled");
	#endif
	
	ap_compressor->Start();
}
	
	
// ********PERIODIC ROUTINES*******//
void SmokeyVI::DisabledPeriodic(void)
{

}

void SmokeyVI::AutonomousPeriodic(void)
{

}

void SmokeyVI::TeleopPeriodic(void)
{
	
	ap_gyro->Update();
	ap_drive->Update();
	ap_shooter->Update();
	ap_feeder->Update();
	ap_hanger->Update();
	//printf("Compressor Switch: %d\n", ap_compressor->GetPressureSwitchValue());
	
	#if defined (Image_Processing)
	printf(" %d\n", ap_ImageProcessor->getRectangles());
	#endif
}

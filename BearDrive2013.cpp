#include "BearDrive2013.h"

// updated 3/9/2013
// for new speed encoders 360 CPR, old were 250

BearDrive2013::BearDrive2013(Joystick *driveStick, BBGyro *gyro)
{
		a_counter = 0;

		ap_driveStick = driveStick;
		ap_gyro = gyro;
  
		ap_lbDrive = new CANJaguar(LB_DRIVE_ID, CANJaguar::kSpeed);
		ap_lbDrive->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
		ap_lbDrive->ConfigEncoderCodesPerRev(360);
		ap_lbDrive->SetPID(-0.4, 0.0, 0.0);

		ap_lfDrive = new CANJaguar(LF_DRIVE_ID, CANJaguar::kSpeed);
		ap_lfDrive->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
		ap_lfDrive->ConfigEncoderCodesPerRev(360);
		ap_lfDrive->SetPID(-0.4, 0.0, 0.0);

		ap_rbDrive = new CANJaguar(RB_DRIVE_ID, CANJaguar::kSpeed);
		ap_rbDrive->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
		ap_rbDrive->ConfigEncoderCodesPerRev(360);
		ap_rbDrive->SetPID(-0.4, 0.0, 0.0);

		ap_rfDrive = new CANJaguar(RF_DRIVE_ID, CANJaguar::kSpeed);
		ap_rfDrive->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
		ap_rfDrive->ConfigEncoderCodesPerRev(360);
		ap_rfDrive->SetPID(-0.4, 0.0, 0.0);
  
		
		ap_lbSwerve = new CANJaguar(LB_SWERVE_ID, CANJaguar::kPercentVbus );
		ap_lbPIDSource = new AnalogChannel(LB_SWERVE_ENC);
		ap_lbSwerveController = new BBPIDController((-0.2 * 0.6) / 10.0, 1 / 2.0 * (-0.06) * 0.0 ,(-0.06/ 8.0) * 0.0, ap_lbPIDSource, ap_lbSwerve, 0.001);
	//	ap_lbSwerveController = new BBPIDController(-0.06, 0.0, 0.0, ap_lbPIDSource, ap_lbSwerve);
		ap_lbSwerveController->SetInputRange(0.0, 1023.0);
		ap_lbSwerveController->SetContinuous(true);
		
		ap_lfSwerve = new CANJaguar(LF_SWERVE_ID, CANJaguar::kPercentVbus );
		ap_lfPIDSource = new AnalogChannel(LF_SWERVE_ENC);
		ap_lfSwerveController = new BBPIDController((0.2 * 0.6)/ 10.0, 1 / 2.0 * (0.06) * 0.0 ,(0.06/ 8.0) * 0.0, ap_lfPIDSource ,ap_lfSwerve, 0.001);
	//	ap_lfSwerveController = new BBPIDController(0.06, 0.0, 0.0, ap_lfPIDSource, ap_lfSwerve);
		ap_lfSwerveController->SetInputRange(0.0, 1023.0);
		ap_lfSwerveController->SetContinuous(true);

		ap_rbSwerve = new CANJaguar(RB_SWERVE_ID, CANJaguar::kPercentVbus );
		ap_rbPIDSource = new AnalogChannel(RB_SWERVE_ENC);
		ap_rbSwerveController = new BBPIDController((-0.2 * 0.6) / 10.0, 1 / 2.0 * (-0.06) * 0.0 ,(-0.06/ 8.0) * 0.0, ap_rbPIDSource, ap_rbSwerve, 0.001);
	//	ap_rbSwerveController = new BBPIDController(-0.06, 0.0, 0.0, ap_rbPIDSource, ap_rbSwerve);
		ap_rbSwerveController->SetInputRange(0.0, 1023.0);
		ap_rbSwerveController->SetContinuous(true);
		
		ap_rfSwerve = new CANJaguar(RF_SWERVE_ID, CANJaguar::kPercentVbus );
		ap_rfPIDSource = new AnalogChannel(RF_SWERVE_ENC);
		ap_rfSwerveController = new BBPIDController((0.2 * 0.6)/ 10.0, 1 / 2.0 * (0.06) * 0.0 ,(0.06/ 8.0) * 0.0, ap_rfPIDSource, ap_rfSwerve, 0.001);
	//	ap_rfSwerveController = new BBPIDController(0.06, 0.0, 0.0, ap_rfPIDSource, ap_rfSwerve);
		ap_rfSwerveController->SetInputRange(0.0, 1023.0);
		ap_rfSwerveController->SetContinuous(true);

}

BearDrive2013::~BearDrive2013()
{
	
		delete ap_lbDrive;
		ap_lbDrive = NULL;

		delete ap_lfDrive;
		ap_lfDrive = NULL;

		delete ap_rbDrive;
		ap_rbDrive = NULL;

		delete ap_rfDrive;
		ap_rfDrive = NULL;
	
		delete ap_lbSwerve;
		ap_lbSwerve = NULL;
		delete ap_lbSwerveController;
		ap_lbSwerveController = NULL;
		delete ap_lbPIDSource;
		ap_lbPIDSource = NULL;

		delete ap_lfSwerve;
		ap_lfSwerve = NULL;
		delete ap_lfSwerveController;
		ap_lfSwerveController = NULL;
		delete ap_lfPIDSource;
		ap_lfPIDSource = NULL;

		delete ap_rbSwerve;
		ap_rbSwerve = NULL;
		delete ap_rbSwerveController;
		ap_rbSwerveController = NULL;
		delete ap_rbPIDSource;
		ap_rbPIDSource = NULL;
		
		delete ap_rfSwerve;
		ap_rfSwerve = NULL;
		delete ap_rfSwerveController;
		ap_rfSwerveController = NULL;
		delete ap_rfPIDSource;
		ap_rfPIDSource = NULL;
		
		ap_gyro = NULL;
		ap_driveStick = NULL;
}

void BearDrive2013::CalcSwerve_FullRotation(double joyX, double joyY, double joyAngle, double wheelAngle, double gyroAngle, double *angleOut, double *speedOut)
	{
		double speed;
		if(fabs(joyX) > fabs(joyY))  // Calculate speed based on joystick position
		{
			speed = fabs(joyX);
		}
		else
		{
			speed = fabs(joyY);
		}

		if(fabs(speed) < 0.1)		// Deadband
		{
			speed = 0.0;
		}

		double angle = joyAngle + 270.0;  // Adjust joystick angle for calculations
		if(angle > 360.0)
		{
			angle -= 360.0;
		}

		


	
		
		angle = 360.0 - angle;		// Reverse angle
		while(gyroAngle > 360.0)
			gyroAngle -= 360.0;
		while(gyroAngle < -360.0)
			gyroAngle += 360.0;
			
		//	angle += -gyroAngle;  //Field oriented	
		*angleOut = angle;

		// adjust "gain" of joystick based on raw value
		// low gain when nearer 0, higher gain once threshold passed
		*speedOut = speed / 3;
	}
	
	
void BearDrive2013::Update()
{
	double joyX = ap_driveStick->GetX() ;
	double joyY = ap_driveStick->GetY() ;
	double joyAngle = ap_driveStick->GetDirectionDegrees();
	double wheelAngle = 360.0 - (ap_rfSwerve->GetPosition() * 360.0);
	double angle, speed;
	
	CalcSwerve_FullRotation(joyX, joyY, joyAngle, wheelAngle, ap_gyro->GetOffsetAngle(), &angle, &speed);

	if(ap_driveStick->GetRawButton(7))	// Orient wheels for spin
	{
		ap_lbDrive->Set(joyX*1100.0, 1);
		ap_lfDrive->Set(joyX*-1100.0, 1);
		ap_rbDrive->Set(joyX*1100.0, 1);
		ap_rfDrive->Set(joyX*1100.0, 1);
		
		
		ap_lbSwerveController->Calculate();
		ap_lfSwerveController->Calculate();
		ap_rbSwerveController->Calculate();
		ap_rfSwerveController->Calculate();
				
		ap_lbSwerveController->SetSetpoint(135 *(1023.0/360.0));
		ap_lfSwerveController->SetSetpoint(45 * (1023.0/360.0));
		ap_rbSwerveController->SetSetpoint(45 * (1023.0/360.0));// ((135.0 / 180.0) * 0.485) + 0.265
		ap_rfSwerveController->SetSetpoint(135 * (1023.0/360.0));
		
	}
	else
	{
		ap_lbDrive->Set(speed*3500.0  , 1);
		ap_lfDrive->Set(speed*3500.0 * (-1), 1);
		ap_rbDrive->Set(speed*3500.0 * (-1), 1);
		ap_rfDrive->Set(speed*3500.0 * (-1), 1);
	
	
	
		ap_lbSwerveController->Calculate();
		ap_lfSwerveController->Calculate();
		ap_rbSwerveController->Calculate();
		ap_rfSwerveController->Calculate();
	
		ap_lbSwerveController->SetSetpoint(angle * (1023.0/360.0));
		ap_lfSwerveController->SetSetpoint(angle * (1023.0/360.0));
		ap_rbSwerveController->SetSetpoint(angle * (1023.0/360.0));
		ap_rfSwerveController->SetSetpoint(angle * (1023.0/360.0));
		
		
		 
		
		
		
		
		 printf( "Raw encoder: %f\t joystick: %f\t gyro: %f\n", ap_lbPIDSource->PIDGet() , angle, ap_gyro->GetOffsetAngle());
//	printf("Joystick: %f\t  Lf Encoder: %f\t Lb Encoder: %f\t Rf Encoder: %f\t Rb Encoder: %f\n",angle, ap_lfPIDSource->PIDGet(), ap_lbPIDSource->PIDGet(),ap_rfPIDSource->PIDGet(),ap_rbPIDSource->PIDGet());
	}
	if(ap_driveStick->GetRawButton(8)){
		ap_gyro->Reset();
	}
	
	CANJaguar::UpdateSyncGroup(1);
	
	
}


void BearDrive2013::Enable()
{
		
		 ap_lbDrive->EnableControl();
		 ap_lfDrive->EnableControl();
		 ap_rbDrive->EnableControl();
		 ap_rfDrive->EnableControl();
	
		 ap_lbSwerveController->Enable();
		 ap_lfSwerveController->Enable();
		 ap_rfSwerveController->Enable();
		 ap_rbSwerveController->Enable();
		 ap_gyro->Reset();
		  
		/*
		ap_rbSwerve->Set(0.2);
		printf(" voltage: %f\n", ap_rbSwerve->GetOutputVoltage());
		 while(1) {
		 	double angle;
		 	ap_rbSwerve->Set(0.2);
		 	angle = ap_rbPIDSource->PIDGet();
		 	printf(" voltage: %f\n", ap_rbSwerve->GetOutputVoltage());
		 	if((angle >= 170) && (angle <= 190)) {
		 		break;
		 	}		 	
		 } 
		 ap_rbSwerve->Set(0);
	*/
}
	
void BearDrive2013::Disable()
{
	ap_lbDrive->DisableControl();
	ap_lfDrive->DisableControl();
	ap_rbDrive->DisableControl();		
	ap_rfDrive->DisableControl();
		
	ap_lbSwerveController->Disable();		
	ap_lfSwerveController->Disable();
	ap_rfSwerveController->Disable();
	ap_rbSwerveController->Disable();
}
	
	
	


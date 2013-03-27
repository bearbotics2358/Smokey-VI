#include "BearDrive2013.h"

// updated 3/9/2013
// for new speed encoders 360 CPR, old were 250

BearDrive2013::BearDrive2013(Joystick *driveStick, BBGyro *gyro)
{
	a_counter = 0;

	ap_driveStick = driveStick;
	ap_gyro = gyro;

	ap_drivePID = new configPID("/ni-rt/system/config/DrivePid.cfg");
	ap_steeringPID = new configPID("/ni-rt/system/config/SteerPid.cfg");
	//ap_autoCfg = new configAuto("/ni-rt/system/config/Autonomous.cfg");
  
	ap_lbDrive = new CANJaguar(LB_DRIVE_ID, CANJaguar::kPercentVbus);
	//ap_lbDrive->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
	//ap_lbDrive->ConfigEncoderCodesPerRev(360);
	//ap_lbDrive->SetPID(-0.4, 0.0, 0.0);
	ap_lbDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);

	ap_lfDrive = new CANJaguar(LF_DRIVE_ID, CANJaguar::kPercentVbus);
	//ap_lfDrive->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
	//ap_lfDrive->ConfigEncoderCodesPerRev(360);
//	ap_lfDrive->SetPID(-0.4, 0.0, 0.0);
	ap_lfDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);

	ap_rbDrive = new CANJaguar(RB_DRIVE_ID, CANJaguar::kPercentVbus);
	 //ap_rbDrive->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
	// ap_rbDrive->ConfigEncoderCodesPerRev(360);
	// ap_rbDrive->SetPID(-0.4, 0.0, 0.0);
	 ap_rbDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);

	ap_rfDrive = new CANJaguar(RF_DRIVE_ID, CANJaguar::kPercentVbus);
	//ap_rfDrive->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
	//ap_rfDrive->ConfigEncoderCodesPerRev(360);
//	ap_rfDrive->SetPID(-0.4, 0.0, 0.0);
	ap_rfDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);
		
	ap_lbSwerve = new CANJaguar(LB_SWERVE_ID, CANJaguar::kPercentVbus );
	ap_lbPIDSource = new AnalogChannel(LB_SWERVE_ENC);
	// ap_lbSwerveController = new BBPIDController((-0.2 * 0.6) / 10.0, 1 / 2.0 * (-0.06) * 0.0 ,(-0.06/ 8.0) * 0.0, ap_lbPIDSource, ap_lbSwerve, 0.001);
	//ap_lbSwerveController = new BBPIDController(-0.06, 0.0, 0.0, ap_lbPIDSource, ap_lbSwerve);
	ap_lbSwerveController = new BBPIDController(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D, ap_lbPIDSource, ap_lbSwerve);
	ap_lbSwerveController->SetInputRange(0.0, 1023.0);
	ap_lbSwerveController->SetContinuous(true);

	ap_lfSwerve = new CANJaguar(LF_SWERVE_ID, CANJaguar::kPercentVbus );
	ap_lfPIDSource = new AnalogChannel(LF_SWERVE_ENC);
		// ap_lfSwerveController = new BBPIDController((0.2 * 0.6)/ 10.0, 1 / 2.0 * (0.06) * 0.0 ,(0.06/ 8.0) * 0.0, ap_lfPIDSource ,ap_lfSwerve, 0.001);
		// ap_lfSwerveController = new BBPIDController(0.06, 0.0, 0.0, ap_lfPIDSource, ap_lfSwerve);
	ap_lfSwerveController = new BBPIDController(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D, ap_lfPIDSource, ap_lfSwerve);
	ap_lfSwerveController->SetInputRange(0.0, 1023.0);
	ap_lfSwerveController->SetContinuous(true);

	ap_rbSwerve = new CANJaguar(RB_SWERVE_ID, CANJaguar::kPercentVbus );
	ap_rbPIDSource = new AnalogChannel(RB_SWERVE_ENC);
	// ap_rbSwerveController = new BBPIDController((0.2 * 0.6) / 10.0, 1 / 2.0 * (0.06) * 0.0 ,(0.06/ 8.0) * 0.0, ap_rbPIDSource, ap_rbSwerve, 0.001);
	// ap_rbSwerveController = new BBPIDController(-0.06, 0.0, 0.0, ap_rbPIDSource, ap_rbSwerve);
	ap_rbSwerveController = new BBPIDController(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D, ap_rbPIDSource, ap_rbSwerve);
	ap_rbSwerveController->SetInputRange(0.0, 1023.0);
	ap_rbSwerveController->SetContinuous(true);

	ap_rfSwerve = new CANJaguar(RF_SWERVE_ID, CANJaguar::kPercentVbus );
	ap_rfPIDSource = new AnalogChannel(RF_SWERVE_ENC);
	// ap_rfSwerveController = new BBPIDController((0.2 * 0.6)/ 10.0, 1 / 2.0 * (0.06) * 0.0 ,(0.06/ 8.0) * 0.0, ap_rfPIDSource, ap_rfSwerve, 0.001);
	// ap_rfSwerveController = new BBPIDController(0.06, 0.0, 0.0, ap_rfPIDSource, ap_rfSwerve);
	ap_rfSwerveController = new BBPIDController(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D, ap_rfPIDSource, ap_rfSwerve);
	ap_rfSwerveController->SetInputRange(0.0, 1023.0);
	ap_rfSwerveController->SetContinuous(true);

//	ap_posTracker = new PositionTracker(ap_lfDrive, ap_lbDrive, ap_rfDrive, ap_rbDrive, ap_gyro, ap_lfPIDSource, ap_lbPIDSource, ap_rfPIDSource, ap_rbPIDSource);
}

BearDrive2013::~BearDrive2013()
{
	
//	delete ap_posTracker;
//	ap_posTracker = NULL;

	 delete ap_lbDrive;
	 ap_lbDrive = NULL;

	delete ap_lfDrive;
	ap_lfDrive = NULL;

	delete ap_rbDrive;
	ap_rbDrive = NULL;

	delete ap_rfDrive;
	ap_rfDrive = NULL;

	delete ap_drivePID;
	ap_drivePID = NULL;

	delete ap_steeringPID;
	ap_steeringPID = NULL;
	
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
	double angle = joyAngle + 300.0;  // Adjust joystick angle for calculations
	if(angle > 360.0)
	{
		angle -= 360.0;
	}

	angle = 360.0 - angle;		// Reverse angle
	while(gyroAngle > 360.0)
		gyroAngle -= 360.0;
	while(gyroAngle < -360.0)
		gyroAngle += 360.0;
		
	// angle += gyroAngle;  //Field oriented
	if(true){
		angle += gyroAngle;
	}
	*angleOut = angle;

	// adjust "gain" of joystick based on raw value
	// low gain when nearer 0, higher gain once threshold passed
	double g = 0.50;
	if(speed <= 0.5){
		*speedOut = speed * g;
	}else{
		*speedOut = ((speed - 0.50)*(1.0 - 0.50 * g) * 2) + (0.50 * g);
	}
}
	

void BearDrive2013::Update()
{
	double joyX = ap_driveStick->GetX() ;
	double joyY = ap_driveStick->GetY() ;
	double joyAngle = ap_driveStick->GetDirectionDegrees();

	double gyroAngle = ap_gyro->GetOffsetAngle();
	double gyro_joy = gyroAngle - joyAngle;

	if(ap_driveStick->GetRawButton(2)){

		ap_lbSwerveController->SetSetpoint(90 * (1023.0/360.0));
		ap_lfSwerveController->SetSetpoint(90 * (1023.0/360.0));
		ap_rbSwerveController->SetSetpoint(90 * (1023.0/360.0));// ((135.0 / 180.0) * 0.485) + 0.265
		ap_rfSwerveController->SetSetpoint(90 * (1023.0/360.0));

		ap_lbSwerveController->Calculate();
		ap_lfSwerveController->Calculate();
		ap_rbSwerveController->Calculate();
		ap_rfSwerveController->Calculate();

		if(true){

			double SpeedRatio = (sin(gyroAngle) * joyY + cos(gyroAngle) * joyX);
			double MultRatio = (sin(gyroAngle) * joyX + cos(gyroAngle) * joyY);

			ap_lbDrive->Set(SpeedRatio*0.7 * (1 + MultRatio) / 2, 1);
			ap_lfDrive->Set(SpeedRatio*0.7 * (1 + MultRatio) / 2, 1);
			ap_rbDrive->Set(SpeedRatio*0.7 * (1 - MultRatio) / 2, 1);
			ap_rfDrive->Set(SpeedRatio*0.7 * (1 - MultRatio) / 2, 1);


		}else{
			ap_lbDrive->Set(joyY*0.7 * (1 + joyX) / 2, 1);
			ap_lfDrive->Set(joyY*0.7 * (1 + joyX) / 2, 1);
			ap_rbDrive->Set(joyY*0.7 * (1 - joyX) / 2, 1);
			ap_rfDrive->Set(joyY*0.7 * (1 - joyX) / 2, 1);
		}

	}else if(ap_driveStick->GetRawButton(2)){
	double wheelAngle = 360.0 - (ap_rfSwerve->GetPosition() * 360.0);
	double angle, speed;
	
	// for twirl
	// gyro angle - joystick angle

		// cycloid angle
	int t_rf;
	int t_rb;
	int t_lb;
	int t_lf;

	// wheel angles for twirl
	double angle_rf;
	double angle_rb;
	double angle_lb;
	double angle_lf;

	// wheel speeds for twirl
	double speed_rf;
	double speed_rb;
	double speed_lb;
	double speed_lf;

	CalcSwerve_FullRotation(joyX, joyY, joyAngle, wheelAngle, ap_gyro->GetOffsetAngle(), &angle, &speed);

	if(ap_driveStick->GetRawButton(7))	// Orient wheels for twist
	{
		printf("DO THE TWIST");

		ap_lbDrive->Set(joyX*0.7, 1);
		ap_lfDrive->Set(joyX*-0.7, 1);
		ap_rbDrive->Set(joyX*-0.7, 1);
		ap_rfDrive->Set(joyX*0.7, 1);
		
		ap_lbSwerveController->SetSetpoint(135 *(1023.0/360.0));
		ap_lfSwerveController->SetSetpoint(45 * (1023.0/360.0));
		ap_rbSwerveController->SetSetpoint(15 * (1023.0/360.0));// ((135.0 / 180.0) * 0.485) + 0.265
		ap_rfSwerveController->SetSetpoint(105 * (1023.0/360.0));
		
		ap_lbSwerveController->Calculate();
		ap_lfSwerveController->Calculate();
		ap_rbSwerveController->Calculate();
		ap_rfSwerveController->Calculate();
		/*
	} else if(ap_driveStick->GetRawButton(9)) {
		//twirl


		printf("TWIRL");
		// cycloid angle
		t_rf = (int)(gyro_joy - 90 + ANGLE_RF + 0.5);
		t_rb = (int)(gyro_joy - 90 + ANGLE_RB + 0.5);
		t_lb = (int)(gyro_joy - 90 + ANGLE_LB + 0.5);
		t_lf = (int)(gyro_joy - 90 + ANGLE_LF + 0.5);

		if(t_rf < 0) {
			t_rf += 360;
		} else if(t_rf >= 360) {
			t_rf -= 360;
		}

		if(t_rb < 0) {
			t_rb += 360;
		} else if(t_rb >= 360) {
			t_rb -= 360;
		}

		if(t_lb < 0) {
			t_lb += 360;
		} else if(t_lb >= 360) {
			t_lb -= 360;
		}

		if(t_lf < 0) {
			t_lf += 360;
		} else if(t_lf >= 360) {
			t_lf -= 360;
		}

		// wheel angles for twirl
		angle_rf = t_rf/2.0 - 90.0 - gyro_joy;
		angle_rb = t_rb/2.0 - 90.0 - gyro_joy;
		angle_lb = t_lb/2.0 - 90.0 - gyro_joy;
		angle_lf = t_lf/2.0 - 90.0 - gyro_joy;

		if(angle_rf < 0.0) {
			angle_rf += 360.0;
		} else if(angle_rf >= 360.0) {
			angle_rf -= 360.0;
		}

		if(angle_rb < 0.0) {
			angle_rb += 360.0;
		} else if(angle_rb >= 360.0) {
			angle_rb -= 360.0;
		}

		if(angle_lb < 0.0) {
			angle_lb += 360.0;
		} else if(angle_lb >= 360.0) {
			angle_lb -= 360.0;
		}

		if(angle_lf < 0.0) {
			angle_lf += 360.0;
		} else if(angle_lf >= 360.0) {
			angle_lf -= 360.0;
		}


		// wheel speeds for twirl
		speed_rf = twirl_speed[t_rf] * speed;
		speed_rb = twirl_speed[t_rb] * speed;
		speed_lb = twirl_speed[t_lb] * speed;
		speed_lf = twirl_speed[t_lf] * speed;

		ap_lbDrive->Set(speed_lb * 360.0  , 1);
		ap_lfDrive->Set(speed_lf * 360.0 * (-1), 1);
		ap_rbDrive->Set(speed_rb * 360.0 * (-1), 1);
		ap_rfDrive->Set(speed_rf * 360.0 * (-1), 1);

		ap_lbSwerveController->SetSetpoint(angle_lb * (1023.0/360.0));
		ap_lfSwerveController->SetSetpoint(angle_lf * (1023.0/360.0));
		ap_rbSwerveController->SetSetpoint(angle_rb * (1023.0/360.0));
		ap_rfSwerveController->SetSetpoint(angle_rf * (1023.0/360.0));

		ap_lbSwerveController->Calculate();
		ap_lfSwerveController->Calculate();
		ap_rbSwerveController->Calculate();
		ap_rfSwerveController->Calculate();
*/
	}
	else
	{
		 ap_lbDrive->Set(speed * (0.7) , 1);
		 ap_lfDrive->Set(speed * (-0.7), 1);
		 ap_rbDrive->Set(speed * (0.7), 1);
		 ap_rfDrive->Set(speed * (-0.7), 1);

		// ap_rbDrive->Set(speed*0.25);
	
	//	printf("Speed: %f", ap_lfDrive->GetSpeed());

		//printf("Normal");

		 ap_lbSwerveController->SetSetpoint(angle * (1023.0/360.0));
		 ap_lfSwerveController->SetSetpoint(angle * (1023.0/360.0));
		 ap_rbSwerveController->SetSetpoint(angle * (1023.0/360.0));
		 ap_rfSwerveController->SetSetpoint(angle * (1023.0/360.0));
		
		 ap_lbSwerveController->Calculate();
		 ap_lfSwerveController->Calculate();
		 ap_rbSwerveController->Calculate();
		 ap_rfSwerveController->Calculate();



		// printf( "Raw encoder: %f\t joystick: %f\t gyro: %f\n", ap_lbPIDSource->PIDGet() , angle, ap_gyro->GetOffsetAngle());
		printf("Joystick: %f\t  lb Encoder: %f\n ",angle, ap_lbPIDSource->PIDGet());
		printf("gyro: %f\n",ap_gyro->GetOffsetAngle());
	}
	if(ap_driveStick->GetRawButton(8)){
		ap_gyro->Reset();
	}
	
	CANJaguar::UpdateSyncGroup(1);
	
	// ap_posTracker->Update();
	// printf("X: %f\n Y: %f\n", ap_posTracker->GetRobotX(),ap_posTracker->GetRobotY());
	}
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

		 ap_drivePID->readFile();

		 ap_lbDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);
		 ap_lfDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);
		 ap_rfDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);
		 ap_rbDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);

		 ap_steeringPID->readFile();

		 ap_lbSwerveController->SetPID(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D);
		 ap_lfSwerveController->SetPID(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D);
		 ap_rfSwerveController->SetPID(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D);
		 ap_rbSwerveController->SetPID(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D);
		 //		 ap_posTracker->Reset();


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

void BearDrive2013::AutonUpdate()
{
//	ap_posTracker->Update();

//	a_dxBuffer -= ap_posTracker->GetRobotDX();
//s	a_dyBuffer -= ap_posTracker->GetRobotDY();


	if(a_dyBuffer > 0.01 || a_dxBuffer > 0.01){

		double angle;
		if(a_dxBuffer <= 0){
			angle = 0.0;
		}else{
			angle = tan(a_dyBuffer / a_dxBuffer) + 90;
		}
		printf("dy: %f\ndx: %f", a_dyBuffer, a_dxBuffer);
/*
		ap_lbDrive->Set(0.1 *6000.0 * (-1) , 1);
		ap_lfDrive->Set(0.1*6000.0 * (1), 1);
		ap_rbDrive->Set(0.1*6000.0 * (-1), 1);
		ap_rfDrive->Set(0.1*6000.0 * (1), 1);

		ap_lbSwerveController->SetSetpoint(angle * (1023.0/360.0));
		ap_lfSwerveController->SetSetpoint(angle * (1023.0/360.0));
		ap_rbSwerveController->SetSetpoint(angle * (1023.0/360.0));
		ap_rfSwerveController->SetSetpoint(angle * (1023.0/360.0));

		ap_lbSwerveController->Calculate();
		ap_lfSwerveController->Calculate();
		ap_rbSwerveController->Calculate();
		ap_rfSwerveController->Calculate();

		CANJaguar::UpdateSyncGroup(1);
		*/
	}

}

void BearDrive2013::AutonEnable()
{
	//ap_autoCfg->readFile();

	 ap_lbDrive->EnableControl();
	 ap_lfDrive->EnableControl();
	 ap_rbDrive->EnableControl();
	 ap_rfDrive->EnableControl();

	 ap_lbSwerveController->Enable();
	 ap_lfSwerveController->Enable();
	 ap_rfSwerveController->Enable();
	 ap_rbSwerveController->Enable();
	 ap_gyro->Reset();

//	 ap_posTracker->Reset();
	 a_dyBuffer = 0.0;
	 a_dxBuffer = 0.0;

	 ap_drivePID->readFile();

 	 ap_lbDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);
	 ap_lfDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);
	 ap_rfDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);
	 ap_rbDrive->SetPID(ap_drivePID->P, ap_drivePID->I, ap_drivePID->D);

	 ap_steeringPID->readFile();

	 ap_lbSwerveController->SetPID(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D);
	 ap_lfSwerveController->SetPID(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D);
	 ap_rfSwerveController->SetPID(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D);
	 ap_rbSwerveController->SetPID(ap_steeringPID->P, ap_steeringPID->I, ap_steeringPID->D);

}

void BearDrive2013::AutonDrive(double dx, double dy)
{
		if(dx == 1){
			ap_lfDrive->Set(100.0 * (1), 1);
			ap_rfDrive->Set(100.0 * (1), 1);
		}else{
			ap_lfDrive->Set(0.0 * (1), 1);
			ap_rfDrive->Set(0.0 * (1), 1);
		}
		ap_lbSwerveController->SetSetpoint(90* (1023.0/360.0));
		ap_lfSwerveController->SetSetpoint(90* (1023.0/360.0));
		ap_rbSwerveController->SetSetpoint(90* (1023.0/360.0));
		ap_rfSwerveController->SetSetpoint(90* (1023.0/360.0));

		ap_lbSwerveController->Calculate();
		ap_lfSwerveController->Calculate();
		ap_rbSwerveController->Calculate();
		ap_rfSwerveController->Calculate();

		CANJaguar::UpdateSyncGroup(1);

}

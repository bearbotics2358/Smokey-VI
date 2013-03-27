#include "Shooter.h"

Shooter::Shooter(Joystick *joystick)
{
	ap_joystick = joystick;
	
	ap_shooter1 = new Victor(SHOOTER1_PORT);
	ap_shooter2 = new Victor(SHOOTER2_PORT);
	
	a_speed = 0.425;
	a_lock = false;
	
}

Shooter::~Shooter()
{
	ap_joystick = NULL;

	delete ap_shooter1;
	ap_shooter1 = NULL;
	
	delete ap_shooter2; 
	ap_shooter2 = NULL;
}

void Shooter::AutoShoot(double speed)
{
	ap_shooter1->Set(speed);
	ap_shooter2->Set(speed);
}

void Shooter::AutoStop()
{
	ap_shooter1->Set(0.0);
	ap_shooter2->Set(0.0);
}

void Shooter::Update()
{
	if(ap_joystick->GetRawButton(SHOOTER_SPEED_UP) && !a_lock && a_speed < 1.0){		
		a_speed += 0.05;
		a_lock = true;
	} else if(ap_joystick->GetRawButton(SHOOTER_SPEED_DOWN) && !a_lock && a_speed > 0.0){
		a_speed -= 0.05;
		a_lock = true;

	} else if(ap_joystick->GetRawButton(SHOOTER_RESET)){
		a_speed = 0.425;
		a_lock = false;
	
	} else if(!ap_joystick->GetRawButton(SHOOTER_SPEED_UP) && !ap_joystick->GetRawButton(SHOOTER_SPEED_DOWN)){
		a_lock = false;
	}
	
	if(ap_joystick->GetRawButton(SHOOTER_RUN)){
		ap_shooter1->Set(a_speed);
		ap_shooter2->Set(a_speed);
	} else {
		ap_shooter1->Set(0.0);
		ap_shooter2->Set(0.0);
	}		
	
	printf("Shooter Speed: %f\t", a_speed);
}


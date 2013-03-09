#include "Hanger.h"


//Constructor
Hanger::Hanger(Joystick *joystick)
{
	ap_joystick = joystick;
	
	ap_extend = new Solenoid(HANGER_EXTEND_PORT);
	ap_retract = new Solenoid(HANGER_RETRACT_PORT);
}


//Destructor
Hanger::~Hanger()
{
	ap_joystick = NULL;

	delete ap_extend;
	ap_extend = NULL;
	
	delete ap_retract;
	ap_retract = NULL;
}

void Hanger::Update()
{
	if(ap_joystick->GetRawButton(HANGER_BUTTON) == true){
		ap_retract->Set(false);
		ap_extend->Set(true);
	}else if(ap_joystick->GetRawButton(HANGER_RETRACT_BUTTON) == true){
		ap_extend->Set(false);	
		ap_retract->Set(true);		
	}
	
}

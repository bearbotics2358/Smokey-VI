#include "Feeder.h"


//Constructor
Feeder::Feeder(Joystick *joystick)
{
	ap_joystick = joystick;
	
	ap_extend = new Solenoid(FEEDER_EXTEND_PORT);
	ap_retract = new Solenoid(FEEDER_RETRACT_PORT);
}


//Destructor
Feeder::~Feeder()
{
	ap_joystick = NULL;

	delete ap_extend;
	ap_extend = NULL;
	
	delete ap_retract;
	ap_retract = NULL;
}

void Feeder::Update()
{
	if(ap_joystick->GetRawButton(FEEDER_BUTTON) == true){
		ap_retract->Set(false);
		ap_extend->Set(true);
	}else //if(ap_joystick->GetRawButton(FEEDER_RETRACT_BUTTON) == true)
	{		
		ap_retract->Set(true);
		ap_extend->Set(false);

	}
	
}

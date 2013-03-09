#ifndef _FEEDER_H_
#define _FEEDER_H_

#include <Solenoid.h>
#include <Joystick.h>

#include "Prefs.h"

class Feeder{

	private:
		Solenoid *ap_extend;
		Solenoid *ap_retract;
		Joystick *ap_joystick;
		
	public:
		Feeder(Joystick *joystick);
		~Feeder();
		
		void Update();
		
};

#endif //_FEEDER_H_

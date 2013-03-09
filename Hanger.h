#ifndef _HANGER_H_
#define _HANGER_H_

#include <Solenoid.h>
#include <Joystick.h>

#include "Prefs.h"

class Hanger{

	private:
		Solenoid *ap_extend;
		Solenoid *ap_retract;
		Joystick *ap_joystick;
		
	public:
		Hanger(Joystick *joystick);
		~Hanger();
		
		void Update();
		
};

#endif //_HANGER_H_

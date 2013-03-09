#ifndef SHOOTER_H
#define SHOOTER_H

#include <Joystick.h>	
#include <Victor.h>

#include "Prefs.h"

class Shooter{
	private:
		Joystick *ap_joystick;

		Victor *ap_shooter1;
		Victor *ap_shooter2;
		
		double a_speed; // shooter Victor Voltage setting
		bool a_lock; // button pressed
		
	public:
		Shooter(Joystick *joystick);
		~Shooter();
		void Update();
		
		
};

#endif //SHOOTER_H

#ifndef COLLECTOR_H
#define COLLECTOR_H
#include <WPILib.h>

class Collector
{
	public:
	Collector(UINT8 port1);
		~Collector();
	void Update(Joystick *CollectorStick);
	private: 
	Jaguar *ap_Collector;
};

#endif

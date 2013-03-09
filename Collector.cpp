#include "Collector.h"

Collector::Collector(UINT8 port1)
{
	ap_Collector = new Jaguar(port1);
}

Collector::~Collector()
{
	delete ap_Collector;
	ap_Collector = NULL;
}

void Collector::Update(Joystick *CollectorStick)
{
	if (CollectorStick->GetRawButton(2)){
		ap_Collector->Set(1);
	}
}

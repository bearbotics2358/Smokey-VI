#include "WPILib.h"
#include "MagEncoder.h"

MagEncoder::MagEncoder(UINT32 channel)
:AnalogChannel(channel)
{

}

MagEncoder::~MagEncoder()
{
}

double MagEncoder::PIDGet()
{
	if (StatusIsFatal()) return 0.0;
	return GetAverageValue() * 0.53319115;
}

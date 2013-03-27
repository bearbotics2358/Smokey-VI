#ifndef POSITION_TRACKER_H
#define POSITION_TRACKER_H

#include <CANJaguar.h>
#include <PIDController.h>
#include <math.h>
#include "BBGyro.h"
#include "AnalogChannel.h"
#include "Prefs.h"

class PositionTracker
{
public:
	PositionTracker(CANJaguar *lfJaguar, CANJaguar *lbJaguar, CANJaguar *rfJaguar, CANJaguar *rbJaguar, BBGyro *gyro, AnalogChannel *lfPIDSource, AnalogChannel *lbPIDSource, AnalogChannel *rfPIDSource, AnalogChannel *rbPIDSource);
	~PositionTracker();
	void Update();
	void Reset();
	double GetRobotX();
	double GetRobotY();
	double GetRobotDX();
	double GetRobotDY();
	
private:
	double a_deltaX;
	double a_deltaY;

	double a_robotX;
	double a_robotY;
	BBGyro *ap_gyro;
	CANJaguar *ap_lfJaguar;
	CANJaguar *ap_lbJaguar;
	CANJaguar *ap_rfJaguar;
	CANJaguar *ap_rbJaguar;
	AnalogChannel *ap_lfPIDSource;
	AnalogChannel *ap_lbPIDSource;
	AnalogChannel *ap_rfPIDSource;
	AnalogChannel *ap_rbPIDSource;
};

#endif //POSITION_TRACKER_H

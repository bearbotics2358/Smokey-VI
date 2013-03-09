#ifndef POSITION_TRACKER_H
#define POSITION_TRACKER_H

#include <CANJaguar.h>
#include <math.h>
#include "BBGyro.h"
#include "Prefs.h"

class PositionTracker
{
	public:
	PositionTracker(CANJaguar *lfJaguar, CANJaguar *lbJaguar, CANJaguar *rfJaguar, CANJaguar *rbJaguar, BBGyro *gyro);
	~PositionTracker();
	void Update();
	void Reset();
	double GetRobotX();
	double GetRobotY();
	
	private:
	
	double a_robotX;
	double a_robotY;
	BBGyro *ap_gyro;
	CANJaguar *ap_lfJaguar;
	CANJaguar *ap_lbJaguar;
	CANJaguar *ap_rfJaguar;
	CANJaguar *ap_rbJaguar;
	
};

#endif //POSITION_TRACKER_H

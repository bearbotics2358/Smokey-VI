#ifndef _GYRO_H_
#define _GYRO_H_

#include <Gyro.h>

#include "Prefs.h"

class BBGyro : public Gyro
{
	private:
		bool a_verbose;
		double a_gyroOffset;
		double a_gyroAngle;
		
	public:
		BBGyro(bool verbose);
		~BBGyro();
		
		void Update();
		void Reset();
		double GetOffsetAngle();
};

#endif //_GYRO_H_

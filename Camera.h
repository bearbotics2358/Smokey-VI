#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <nivision.h>

class AxisCamera;

class Camera
{
public:
	Camera(bool verbose);
	~Camera(void);
	
	void ProcessPicture(void);
	void ProcessRectangles(void);

	double GetTargetCenter(void)
	{
		return a_targetCenter;
	}
	
	double GetDistance(void)
	{
		return a_distance;
	}
	
	double GetAngle(void)
	{
		return a_angle;
	}
	
	bool GetSide(void)
	{
		return a_side;
	}
	
private:
	static const double PI = 3.141592654;
	static const double KV = 56.5;
	static const double KH = 57.4;
	
	void CheckIMAQError(int res, const char *desc);
	
	bool a_verbose;
	
	AxisCamera *ap_camera;
	
	MeasureParticlesReport *ap_particles;
	int a_highRect, a_leftRect, a_rightRect;
	double a_targetCenter;
	double a_distance, a_angle;
	bool a_side;										// Side of field from centerline; true: right, false: left
};

#endif // _CAMERA_H_

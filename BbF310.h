#ifndef _BB_F310_H_
#define _BB_F310_H_

#include "Framework/Gamepad.h"

class F310;

class BbF310 : public Gamepad
{
public:
	typedef enum
	{
		kNormalGain,
		kLowGain,
	} ControlMode;
	
	BbF310(F310 *gamepad);
	BbF310(F310 *gamepad, double rightSensitivity, double leftSensitivity);
	virtual ~BbF310(void);
	
	void SetMode(ControlMode mode);
	
	void SetRightSensitivity(double sensitivity);
	void SetLeftSensitivity(double sensitivity);
	double GetRightSensitivity(void);
	double GetLeftSensitivity(void);
	
	float GetRightX(void);
	float GetRightY(void);
	
	float GetLeftX(void);
	float GetLeftY(void);
	
	float GetDPadX(void);
	float GetDPadY(void);
	
	bool GetXButton(void);
	bool GetAButton(void);
	bool GetBButton(void);
	bool GetYButton(void);
	
	bool GetRightBumper(void);
	bool GetLeftBumper(void);
	
	bool GetRightTrigger(void);
	bool GetLeftTrigger(void);
	
	bool GetBackButton(void);
	bool GetStartButton(void);
	bool GetRightStickButton(void);
	bool GetLeftStickButton(void);
	
private:
	F310 *ap_gamepad;
	double a_rightSensitivity;
	double a_leftSensitivity;
	ControlMode a_mode;
};

#endif

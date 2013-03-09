#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

class Gamepad
{
public:
	virtual float GetRightX(void) = 0;
	virtual float GetRightY(void) = 0;
	
	virtual float GetLeftX(void) = 0;
	virtual float GetLeftY(void) = 0;
	
	virtual float GetDPadX(void) = 0;
	virtual float GetDPadY(void) = 0;
	
	virtual bool GetXButton(void) = 0;
	virtual bool GetAButton(void) = 0;
	virtual bool GetBButton(void) = 0;
	virtual bool GetYButton(void) = 0;
	
	virtual bool GetRightBumper(void) = 0;
	virtual bool GetLeftBumper(void) = 0;
	
	virtual bool GetRightTrigger(void) = 0;
	virtual bool GetLeftTrigger(void) = 0;
	
	virtual bool GetBackButton(void) = 0;
	virtual bool GetStartButton(void) = 0;
	virtual bool GetRightStickButton(void) = 0;
	virtual bool GetLeftStickButton(void) = 0;
};

#endif

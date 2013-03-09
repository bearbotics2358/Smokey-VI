#ifndef _VIRTUAL_GAMEPAD_H_
#define _VIRTUAL_GAMEPAD_H_

#include "Framework/Gamepad.h"

class BbVirtualGamepad : public Gamepad
{
public:
	BbVirtualGamepad(void);
	virtual ~BbVirtualGamepad(void);
	
	/* ==================== GETTERS ==================== */
	float GetLeftX(void);
	float GetLeftY(void);
	
	float GetRightX(void);
	float GetRightY(void);
	
	float GetDPadX(void);
	float GetDPadY(void);
	
	bool GetXButton(void);
	bool GetAButton(void);
	bool GetBButton(void);
	bool GetYButton(void);
	
	bool GetLeftBumper(void);
	bool GetRightBumper(void);
	
	bool GetLeftTrigger(void);
	bool GetRightTrigger(void);
	
	bool GetBackButton(void);
	bool GetStartButton(void);
	bool GetLeftStickButton(void);
	bool GetRightStickButton(void);
	
	/* ==================== SETTERS ==================== */
	void SetLeftX(float value);
	void SetLeftY(float value);
	
	void SetRightX(float value);
	void SetRightY(float value);
	
	void SetDPadX(float value);
	void SetDPadY(float value);
	
	void SetXButton(bool state);
	void SetAButton(bool state);
	void SetBButton(bool state);
	void SetYButton(bool state);
	
	void SetLeftBumper(bool state);
	void SetRightBumper(bool state);
	
	void SetLeftTrigger(bool state);
	void SetRightTrigger(bool state);
	
	void SetBackButton(bool state);
	void SetStartButton(bool state);
	void SetLeftStickButton(bool state);
	void SetRightStickButton(bool state);
	
private:
	float a_leftX;
	float a_leftY;
	
	float a_rightX;
	float a_rightY;
	
	float a_dpadX;
	float a_dpadY;
	
	bool a_xButton;
	bool a_aButton;
	bool a_bButton;
	bool a_yButton;
	
	bool a_leftBumper;
	bool a_rightBumper;
	
	bool a_leftTrigger;
	bool a_rightTrigger;
	
	bool a_backButton;
	bool a_startButton;
	bool a_leftStickButton;
	bool a_rightStickButton;
};

#endif

#include "BbF310.h"
#include "F310.h"
#include <math.h>

BbF310::BbF310(F310 *gamepad)
{
	ap_gamepad = gamepad;
	a_rightSensitivity = 0.5;
	a_leftSensitivity = 0.5;
	a_mode = kNormalGain;
}

BbF310::BbF310(F310 *gamepad, double rightSensitivity, double leftSensitivity)
{
	ap_gamepad = gamepad;
	if(rightSensitivity > 1)
	{
		a_rightSensitivity = 1.0;
	}
	else if(rightSensitivity < 0)
	{
		a_rightSensitivity = 0.0;
	}
	else
	{
		a_rightSensitivity = rightSensitivity;
	}
	if(leftSensitivity > 1)
	{
		a_leftSensitivity = 1.0;
	}
	else if(leftSensitivity < 0)
	{
		a_leftSensitivity = 0.0;
	}
	else
	{
		a_leftSensitivity = leftSensitivity;
	}
}

BbF310::~BbF310(void)
{
	delete ap_gamepad;
	ap_gamepad = NULL;
}

void BbF310::SetMode(ControlMode mode)
{
	a_mode = mode;
}

void BbF310::SetRightSensitivity(double sensitivity)
{
	if(sensitivity > 1)
	{
		a_rightSensitivity = 1.0;
	}
	else if(sensitivity < 0)
	{
		a_rightSensitivity = 0.0;
	}
	else
	{
		a_rightSensitivity = sensitivity;
	}
}

void BbF310::SetLeftSensitivity(double sensitivity)
{
	if(sensitivity > 1)
	{
		a_leftSensitivity = 1.0;
	}
	else if(sensitivity < 0)
	{
		a_leftSensitivity = 0.0;
	}
	else
	{
		a_leftSensitivity = sensitivity;
	}
}

double BbF310::GetRightSensitivity(void)
{
	return a_rightSensitivity;
}

double BbF310::GetLeftSensitivity(void)
{
	return a_leftSensitivity;
}

float BbF310::GetRightX(void)
{
	float result = 0.0;
	
	float temp = ap_gamepad->GetX(F310::kRightStick);
	result = a_rightSensitivity * pow(temp, 3) + (1 - a_rightSensitivity) * temp;
	
	if(a_mode == kLowGain)
	{
		result /= 2.0;
	}
	
	return result;
}

float BbF310::GetRightY(void)
{
	float result = 0.0;
	
	float temp = ap_gamepad->GetY(F310::kRightStick);
	result = a_rightSensitivity * pow(temp, 3) + (1 - a_rightSensitivity) * temp;
	
	if(a_mode == kLowGain)
	{
		result /= 2.0;
	}
	
	return result;
}

float BbF310::GetLeftX(void)
{
	float result = 0.0;
	
	float temp = ap_gamepad->GetX(F310::kLeftStick);
	result = a_leftSensitivity * pow(temp, 3) + (1 - a_leftSensitivity) * temp;
	
	if(a_mode == kLowGain)
	{
		result /= 2.0;
	}
	
	return result;
}

float BbF310::GetLeftY(void)
{
	float result = 0.0;
	
	float temp = ap_gamepad->GetY(F310::kLeftStick);
	result = a_leftSensitivity * pow(temp, 3) + (1 - a_leftSensitivity) * temp;
	
	if(a_mode == kLowGain)
	{
		result /= 2.0;
	}
	
	return result;
}

float BbF310::GetDPadX(void)
{
	return ap_gamepad->GetDPadX();
}

float BbF310::GetDPadY(void)
{
	return ap_gamepad->GetDPadY();
}

bool BbF310::GetXButton(void)
{
	return ap_gamepad->GetButton(F310::kXButton);
}

bool BbF310::GetAButton(void)
{
	return ap_gamepad->GetButton(F310::kAButton);
}

bool BbF310::GetBButton(void)
{
	return ap_gamepad->GetButton(F310::kBButton);
}

bool BbF310::GetYButton(void)
{
	return ap_gamepad->GetButton(F310::kYButton);
}

bool BbF310::GetRightBumper(void)
{
	return ap_gamepad->GetButton(F310::kRightBumper);
}

bool BbF310::GetLeftBumper(void)
{
	return ap_gamepad->GetButton(F310::kLeftBumper);
}

bool BbF310::GetRightTrigger(void)
{
	return ap_gamepad->GetButton(F310::kRightTrigger);
}

bool BbF310::GetLeftTrigger(void)
{
	return ap_gamepad->GetButton(F310::kLeftTrigger);
}

bool BbF310::GetBackButton(void)
{
	return ap_gamepad->GetButton(F310::kBackButton);
}

bool BbF310::GetStartButton(void)
{
	return ap_gamepad->GetButton(F310::kStartButton);
}

bool BbF310::GetRightStickButton(void)
{
	return ap_gamepad->GetButton(F310::kRightStickButton);
}

bool BbF310::GetLeftStickButton(void)
{
	return ap_gamepad->GetButton(F310::kLeftStickButton);
}

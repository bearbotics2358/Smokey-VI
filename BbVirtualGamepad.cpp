#include "BbVirtualGamepad.h"

BbVirtualGamepad::BbVirtualGamepad(void)
	: a_leftX(0.0),
	  a_leftY(0.0),
	  a_rightX(0.0),
	  a_rightY(0.0),
	  a_dpadX(0.0),
	  a_dpadY(0.0),
	  a_xButton(false),
	  a_aButton(false),
	  a_bButton(false),
	  a_yButton(false),
	  a_leftBumper(false),
	  a_rightBumper(false),
	  a_leftTrigger(false),
	  a_rightTrigger(false),
	  a_backButton(false),
	  a_startButton(false),
	  a_leftStickButton(false),
	  a_rightStickButton(false)
{
	
}

BbVirtualGamepad::~BbVirtualGamepad(void)
{
	
}

float BbVirtualGamepad::GetLeftX(void)
{
	return a_leftX;
}

float BbVirtualGamepad::GetLeftY(void)
{
	return a_leftY;
}

float BbVirtualGamepad::GetRightX(void)
{
	return a_rightX;
}

float BbVirtualGamepad::GetRightY(void)
{
	return a_rightY;
}

float BbVirtualGamepad::GetDPadX(void)
{
	return a_dpadX;
}

float BbVirtualGamepad::GetDPadY(void)
{
	return a_dpadY;
}

bool BbVirtualGamepad::GetXButton(void)
{
	return a_xButton;
}

bool BbVirtualGamepad::GetAButton(void)
{
	return a_aButton;
}

bool BbVirtualGamepad::GetBButton(void)
{
	return a_bButton;
}

bool BbVirtualGamepad::GetYButton(void)
{
	return a_yButton;
}

bool BbVirtualGamepad::GetLeftBumper(void)
{
	return a_leftBumper;
}

bool BbVirtualGamepad::GetRightBumper(void)
{
	return a_rightBumper;
}

bool BbVirtualGamepad::GetLeftTrigger(void)
{
	return a_leftTrigger;
}

bool BbVirtualGamepad::GetRightTrigger(void)
{
	return a_rightTrigger;
}

bool BbVirtualGamepad::GetBackButton(void)
{
	return a_backButton;
}

bool BbVirtualGamepad::GetStartButton(void)
{
	return a_startButton;
}

bool BbVirtualGamepad::GetLeftStickButton(void)
{
	return a_leftStickButton;
}

bool BbVirtualGamepad::GetRightStickButton(void)
{
	return a_rightStickButton;
}

void BbVirtualGamepad::SetLeftX(float value)
{
	a_leftX = value;
}

void BbVirtualGamepad::SetLeftY(float value)
{
	a_leftY = value;
}

void BbVirtualGamepad::SetRightX(float value)
{
	a_rightX = value;
}

void BbVirtualGamepad::SetRightY(float value)
{
	a_rightY = value;
}

void BbVirtualGamepad::SetDPadX(float value)
{
	a_dpadX = value;
}

void BbVirtualGamepad::SetDPadY(float value)
{
	a_dpadY = value;
}

void BbVirtualGamepad::SetXButton(bool state)
{
	a_xButton = state;
}

void BbVirtualGamepad::SetAButton(bool state)
{
	a_aButton = state;
}

void BbVirtualGamepad::SetBButton(bool state)
{
	a_bButton = state;
}

void BbVirtualGamepad::SetYButton(bool state)
{
	a_yButton = state;
}

void BbVirtualGamepad::SetLeftBumper(bool state)
{
	a_leftBumper = state;
}

void BbVirtualGamepad::SetRightBumper(bool state)
{
	a_rightBumper = state;
}

void BbVirtualGamepad::SetLeftTrigger(bool state)
{
	a_leftTrigger = state;
}

void BbVirtualGamepad::SetRightTrigger(bool state)
{
	a_rightTrigger = state;
}

void BbVirtualGamepad::SetBackButton(bool state)
{
	a_backButton = state;
}

void BbVirtualGamepad::SetStartButton(bool state)
{
	a_startButton = state;
}

void BbVirtualGamepad::SetLeftStickButton(bool state)
{
	a_leftStickButton = state;
}

void BbVirtualGamepad::SetRightStickButton(bool state)
{
	a_rightStickButton = state;
}

#pragma once
#include "PowerObject.h"

#define POWER_SIGN_WIDTH	14
#define POWER_SIGN_HEIGHT	7

class CPowerSign : public CPowerObject
{
public:
	CPowerSign();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};


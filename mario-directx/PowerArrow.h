#pragma once
#include "PowerObject.h"

#define POWER_ARROW_WIDTH	8
#define POWER_ARROW_HEIGHT	7

class CPowerArrow : public CPowerObject
{
public:
	CPowerArrow();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};


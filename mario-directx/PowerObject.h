#pragma once
#include "GameObject.h"

#define POWER_OBJECT_STATE_ON	0
#define POWER_OBJECT_STATE_OFF	1

#define POWER_OBJECT_ANI_OFF	0
#define POWER_OBJECT_ANI_ON		1

class CPowerObject : public CGameObject
{
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};


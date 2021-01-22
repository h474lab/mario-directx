#pragma once
#include "GameObject.h"

#define FIRE_FLOWER_STATE_AVAILABLE		0
#define FIRE_FLOWER_STATE_UNAVAILABLE	1

#define FIRE_FLOWER_FLYING_SPEED_Y	0.04f

#define FIRE_FLOWER_BBOX_WIDTH	16
#define FIRE_FLOWER_BBOX_HEIGHT	16

#define FIRE_FLOWER_ANI_AVAILABLE	0

class CFireFlower : public CGameObject
{
public:
	CFireFlower();

	virtual void SetState(int state);
	virtual void SetPosition(float x, float y);

	virtual void SetAppearingState() { SetState(FIRE_FLOWER_STATE_AVAILABLE); }
	virtual void SetDisappearingState() { SetState(FIRE_FLOWER_STATE_UNAVAILABLE); }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


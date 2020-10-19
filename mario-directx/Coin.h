#pragma once
#include "GameObject.h"

#define COIN_STATE_AVAILABLE	0
#define COIN_STATE_UNAVAILABLE	1

#define COIN_BBOX_WIDTH			16
#define COIN_BBOX_HEIGHT		16

class CCoin : public CGameObject
{
public:
	CCoin();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


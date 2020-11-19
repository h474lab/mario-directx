#pragma once
#include "GameObject.h"

#define COIN_STATE_AVAILABLE	0
#define COIN_STATE_UNAVAILABLE	1

#define COIN_BBOX_WIDTH			16
#define COIN_BBOX_HEIGHT		16

#define COIN_FLYING_SPEED_Y		0.4f

#define COIN_AFFECT_TYPE_GAINED	1

#define COIN_SCORE_GAINED	100
#define COIN_MONEY_GAINED	1

class CCoin : public CGameObject
{
public:
	CCoin();
	virtual void SetPosition(float x, float y);
	virtual void Affect(int type);

	virtual void SetDisappearingState();
	virtual void SetAppearingState();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


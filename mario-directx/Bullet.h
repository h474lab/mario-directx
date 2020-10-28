#pragma once
#include "GameObject.h"

#define BULLET_FLYING_SPEED_X		0.1f
#define BULLET_FLYING_SPEED_Y		0.1f

#define BULLET_BBOX_WIDTH	8
#define BULLET_BBOX_HEIGHT	8

#define BULLET_STATE_ON_HOLD	0
#define BULLET_STATE_FLY		1

#define BULLET_FLYING_DIRECTION_TOP_LEFT	0
#define BULLET_FLYING_DIRECTION_TOP_RIGHT	1
#define BULLET_FLYING_DIRECTION_BOT_LEFT	2
#define BULLET_FLYING_DIRECTION_BOT_RIGHT	3

class CBullet : public CGameObject
{
	int direction;
public:
	CBullet() { background = 0; SetState(BULLET_STATE_ON_HOLD); }

	void SetDirection(int direction);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


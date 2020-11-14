#pragma once
#include "GameObject.h"

#define BULLET_FLYING_SPEED_X		0.04f
#define BULLET_FLYING_SPEED_Y		0.04f

#define BULLET_FLYING_MID_SPEED_X	(float)sqrt(6)/50.0f
#define BULLET_FLYING_MID_SPEED_Y	(float)sqrt(2)/50.0f

#define BULLET_BBOX_WIDTH	8
#define BULLET_BBOX_HEIGHT	8

#define BULLET_STATE_ON_HOLD	0
#define BULLET_STATE_FLY		1

#define BULLET_FLYING_DIRECTION_TOP_LEFT		0
#define BULLET_FLYING_DIRECTION_MID_TOP_LEFT	1
#define BULLET_FLYING_DIRECTION_TOP_RIGHT		2
#define BULLET_FLYING_DIRECTION_MID_TOP_RIGHT	3
#define BULLET_FLYING_DIRECTION_BOT_LEFT		4
#define BULLET_FLYING_DIRECTION_MID_BOT_LEFT	5
#define BULLET_FLYING_DIRECTION_BOT_RIGHT		6
#define BULLET_FLYING_DIRECTION_MID_BOT_RIGHT	7

class CBullet : public CGameObject
{
	int direction;
public:
	CBullet() { background = 0; SetState(BULLET_STATE_ON_HOLD); }

	void SetDirection(int direction);

	float GetDistance(int direction, float xM, float yM);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


#pragma once
#include "GameObject.h"

#define FIREBALL_FLYING_SPEED_X	0.2f
#define FIREBALL_FLYING_SPEED_Y	0.3f;
#define FIREBALL_GRAVITY		0.002f

#define FIREBALL_STATE_ON_HOLD	0
#define FIREBALL_STATE_FLY		1

#define FIREBALL_DIRECTION_LEFT		0
#define FIREBALL_DIRECTION_RIGHT	1

#define FIREBALL_BBOX_WIDTH		8
#define FIREBALL_BBOX_HEIGHT	8

class CFireball : public CGameObject
{
	int direction;
public:
	CFireball() { background = 0; SetState(FIREBALL_STATE_ON_HOLD); }

	void SetDirection(int direction);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


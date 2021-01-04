#pragma once
#include "GameObject.h"

#define BOOMERANG_IDLE_SPEED_X	0.0f
#define BOOMERANG_IDLE_SPEED_Y	0.0f

#define BOOMERANG_FLY_SPEED_X	0.25f
#define BOOMERANG_FLY_SPEED_Y	0.07f

#define BOOMERANG_FLY_LIMIT_Y		8.0f
#define BOOMERANG_FLY_SPEED_DOWN_X	0.003f
#define BOOMERANG_FLY_SPEED_DOWN_Y	0.0012f

#define BOOMERANG_ANI_CLOCKWISE_ROTATION		0
#define BOOMERANG_ANI_COUNTERCLOCKWISE_ROTATION	1
#define BOOMERANG_ANI_IDLE_LEFT					2
#define BOOMERANG_ANI_IDLE_RIGHT				3

#define BOOMERANG_STATE_HIDE		0
#define BOOMERANG_STATE_IDLE		1
#define BOOMERANG_STATE_FLY			2

#define BOOMERANG_BBOX_WIDTH	16
#define BOOMERANG_BBOX_HEIGHT	16

#define BOOMERANG_DIRECTION_LEFT	0
#define BOOMERANG_DIRECTION_RIGHT	1

class CBoomerang : public CGameObject
{
	int direction;
	float limitY;
public:
	CBoomerang();

	void Throw(int dir);

	virtual void SetPosition(float x, float y);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


#pragma once
#include "GameObject.h"

#define BEETLE_FLYING_OUT_SPEED_X	0.05f
#define BEETLE_FLYING_OUT_SPEED_Y	0.1f

#define BEETLE_GRAVITY			0.007f;
#define BEETLE_DROP_BOUNCING	0.5f

#define BEETLE_STATE_WALKING_LEFT	0
#define BEETLE_STATE_WALKING_RIGHT	1
#define BEETLE_STATE_LYING			2
#define BEETLE_STATE_ROLLING_LEFT	3
#define BEETLE_STATE_ROLLING_RIGHT	4
#define BEETLE_STATE_FLYING_OUT		5
#define BEETLE_STATE_UNAVAILABLE	6
#define BEETLE_STATE_DROPPING		7

#define BEETLE_ANI_NONE				-1
#define BEETLE_ANI_WALKING_LEFT		0
#define BEETLE_ANI_WALKING_RIGHT	1
#define BEETLE_ANI_LYING			2
#define BEETLE_ANI_ROLLING			3
#define BEETLE_ANI_FLYING_OUT		4

#define BEETLE_WIDTH	15
#define BEETLE_HEIGHT	15

class CBeetle : public CGameObject
{
public:
	void KickBeetleOut(int direction);
	virtual void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


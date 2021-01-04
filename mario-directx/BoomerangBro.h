#pragma once
#include "GameObject.h"

#define BOOMERANG_BRO_ANI_WALKING_LEFT		0
#define BOOMERANG_BRO_ANI_WALKING_RIGHT		1
#define BOOMERANG_BRO_ANI_DYING_LEFT		2
#define BOOMERANG_BRO_ANI_DYING_RIGHT		3
#define BOOMERANG_BRO_ANI_THROWING_LEFT		4
#define BOOMERANG_BRO_ANI_THROWING_RIGHT	5

#define BOOMERANG_BRO_WALKING_SPEED_X	0.05f
#define BOOMERANG_BRO_WALKING_SPEED_Y	0.0f

#define BOOMERANG_BRO_JUMPING_SPEED_X	0.05f
#define BOOMERANG_BRO_JUMPING_SPEED_Y	0.05f

#define BOOMERANG_BRO_DYING_SPEED_X		0.0f
#define BOOMERANG_BRO_DYING_SPEED_Y		0.0f

#define BOOMERANG_BRO_THROWING_DELAY	3000
#define BOOMERANG_BRO_THROWING_TIME		500
#define BOOMERANG_BRO_GRAVITY			0.002f

#define BOOMERANG_BRO_WALKING_DISTANCE	32.0f
#define BOOMERANG_BRO_WALKING_TIMES		6

#define BOOMERANG_BRO_STATE_MOVING_FORWARD	0
#define BOOMERANG_BRO_STATE_MOVING_BACKWARD	1
#define BOOMERANG_BRO_STATE_JUMPING			2
#define BOOMERANG_BRO_STATE_DYING			3

#define BOOMERANG_BRO_BBOX_HEIGHT	23
#define BOOMERANG_BRO_BBOX_WIDTH	16

class CBoomerangBro : public CGameObject
{
	float leftBound, rightBound;
	float ix, iy; // initial position of Boomerang Bro
	int jumping;
	int walkingCount;
	CGameObject* followingObject;

	int throwing;
	DWORD throwing_start, throwing_delay_start;
public:
	CBoomerangBro();

	virtual void SetState(int state);
	virtual void SetPosition(float x, float y);
	
	void SetFollowingObject(CGameObject* object) { this->followingObject = object; }
	void ThrowBoomerang();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


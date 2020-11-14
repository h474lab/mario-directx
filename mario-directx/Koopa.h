#pragma once
#include "GameObject.h"

#define KOOPA_LEVEL_TROOPA		0
#define KOOPA_LEVEL_PARATROOPA	1

#define KOOPA_WALKING_SPEED			0.030f
#define KOOPA_ROLLING_SPEED			0.25f
#define KOOPA_GRAVITY				0.001f
#define KOOPA_FLYING_TIME			2000

#define KOOPA_JUMPING_SPEED_X		0.05f
#define KOOPA_JUMPING_SPEED_Y		0.3f

#define KOOPA_DEFLECTING_X			0.15f
#define KOOPA_DEFLECTING_Y			0.2f

#define KOOPA_FLYING_OUT_X			0.05f
#define KOOPA_FLYING_OUT_Y			0.1f

#define KOOPA_STATE_WALKING_LEFT			0
#define KOOPA_STATE_WALKING_RIGHT			1
#define KOOPA_STATE_LYING_UP				2
#define KOOPA_STATE_LYING_DOWN				3
#define KOOPA_STATE_ROLLING_UP_LEFT			4
#define KOOPA_STATE_ROLLING_UP_RIGHT		5
#define KOOPA_STATE_ROLLING_DOWN_LEFT		6
#define KOOPA_STATE_ROLLING_DOWN_RIGHT		7
#define KOOPA_STATE_JUMPING_RIGHT			8
#define KOOPA_STATE_JUMPING_LEFT			9
#define KOOPA_STATE_FLYING_OUT				10

#define KOOPA_ANI_WALKING_RIGHT			0
#define KOOPA_ANI_WALKING_LEFT			1
#define KOOPA_ANI_LYING_UP				2
#define KOOPA_ANI_ROLLING_UP			3
#define KOOPA_ANI_LYING_DOWN			4
#define KOOPA_ANI_ROLLING_DOWN			5
#define KOOPA_ANI_JUMPING_RIGHT			6
#define KOOPA_ANI_JUMPING_LEFT			7

#define KOOPA_MARGIN_HEIGHT		1
#define KOOPA_MARGIN_WIDTH		2

#define KOOPA_STANDING_WIDTH			16
#define KOOPA_STANDING_HEIGHT			27

#define KOOPA_LYING_WIDTH			18
#define KOOPA_LYING_HEIGHT			16

#define KOOPA_ROLLING_WIDTH			16
#define KOOPA_ROLLING_HEIGHT		16

#define KOOPA_JUMPING_WIDTH		16
#define KOOPA_JUMPING_HEIGHT	27

class CKoopa : public CGameObject
{
private:
	float leftEdge, rightEdge;

	int level;
	int jumping;
	
	int flying;
	DWORD flying_start;

	int isHolden;
public:
	CKoopa();

	void SetLevel(int level) { this->level = level; }
	void LevelDown();

	virtual void SetState(int state);
	void SetHolden(int holdenState) { isHolden = holdenState; background = isHolden; }

	void HitKoopa(int direction);
	void KickKoopaOut(int direction);

	void ChangeDirection();

	void StartFlying() { flying = 1; flying_start = (DWORD)GetTickCount64(); }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


#pragma once
#include "GameObject.h"
#include "Bullet.h"

#define FIRE_TRAP_STATE_POINT	0
#define FIRE_TRAP_STATE_FIRE	1

#define FIRE_TRAP_DIRECTION_BOTTOM_LEFT		0
#define FIRE_TRAP_DIRECTION_BOTTOM_RIGHT	1
#define FIRE_TRAP_DIRECTION_TOP_LEFT		2
#define FIRE_TRAP_DIRECTION_TOP_RIGHT		3

#define FIRE_TRAP_ANI_POINT_BOTTOM_LEFT		0
#define FIRE_TRAP_ANI_FIRE_BOTTOM_LEFT		1
#define FIRE_TRAP_ANI_POINT_BOTTOM_RIGHT	2
#define FIRE_TRAP_ANI_FIRE_BOTTOM_RIGHT		3
#define FIRE_TRAP_ANI_POINT_TOP_LEFT		4
#define FIRE_TRAP_ANI_FIRE_TOP_LEFT			5
#define FIRE_TRAP_ANI_POINT_TOP_RIGHT		6
#define FIRE_TRAP_ANI_FIRE_TOP_RIGHT		7

#define FIRE_TRAP_BBOX_WIDTH	16
#define FIRE_TRAP_BBOX_HEIGHT	33

#define FIRE_TRAP_FLYING_SPEED_Y		0.01f
#define FIRE_TRAP_DELAY_FLYING_TIME		3000

class CVenusFireTrap : public CGameObject
{
	int direction;
	CGameObject* followingObject;
	CBullet* bullet;
public:
	CVenusFireTrap() { background = 0; }

	virtual void SetPosition(float x, float y);
	void SetDirection(int direction) { this->direction = direction; }

	void Firing();

	void SetAppearingState(int state) { SetState(FIRE_TRAP_STATE_POINT); }
	void SetFollowingObject(CGameObject* followingObject) { this->followingObject = followingObject; }
	void SetBullet(CBullet* bullet) { this->bullet = bullet; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


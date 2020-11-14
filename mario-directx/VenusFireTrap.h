#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "FireTrap.h"

#define FIRE_TRAP_ANI_POINT_BOTTOM_LEFT		0
#define FIRE_TRAP_ANI_FIRE_BOTTOM_LEFT		1
#define FIRE_TRAP_ANI_POINT_BOTTOM_RIGHT	2
#define FIRE_TRAP_ANI_FIRE_BOTTOM_RIGHT		3
#define FIRE_TRAP_ANI_POINT_TOP_LEFT		4
#define FIRE_TRAP_ANI_FIRE_TOP_LEFT			5
#define FIRE_TRAP_ANI_POINT_TOP_RIGHT		6
#define FIRE_TRAP_ANI_FIRE_TOP_RIGHT		7

#define VENUS_FIRE_TRAP_BBOX_WIDTH	16
#define VENUS_FIRE_TRAP_BBOX_HEIGHT	33

#define FIRE_TRAP_FLYING_SPEED_Y		0.01f
#define FIRE_TRAP_DELAY_FLYING_TIME		3000

class CVenusFireTrap : public CFireTrap
{
public:
	CVenusFireTrap() { background = 0; }

	virtual void SetPosition(float x, float y);

	virtual void SetAppearingState() { SetState(TUBE_ENEMY_STATE_POINT); }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


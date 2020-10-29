#pragma once
#include "TubeEnemy.h"

#define FIRE_TRAP_ANI_POINT_BOTTOM_LEFT		0
#define FIRE_TRAP_ANI_FIRE_BOTTOM_LEFT		1
#define FIRE_TRAP_ANI_POINT_BOTTOM_RIGHT	2
#define FIRE_TRAP_ANI_FIRE_BOTTOM_RIGHT		3
#define FIRE_TRAP_ANI_POINT_TOP_LEFT		4
#define FIRE_TRAP_ANI_FIRE_TOP_LEFT			5
#define FIRE_TRAP_ANI_POINT_TOP_RIGHT		6
#define FIRE_TRAP_ANI_FIRE_TOP_RIGHT		7

class CFireTrap : public CTubeEnemy
{
public:
	virtual void SetPosition(float x, float y);

	virtual void SetAppearingState(int state) { SetState(TUBE_ENEMY_STATE_POINT); }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) { CTubeEnemy::Update(dt, coObjects); }
	virtual void Render();
};


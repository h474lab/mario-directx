#pragma once
#include "GameObject.h"
#include "Mario.h"

#define MAP_MARIO_MOVING_SPEED_X	0.5f
#define MAP_MARIO_MOVING_SPEED_Y	0.5f

#define MAP_MARIO_STATE_MOVING	0
#define MAP_MARIO_STATE_IDLING	1

#define MAP_MARIO_MOVING_DIRECTION_LEFT		0
#define MAP_MARIO_MOVING_DIRECTION_RIGHT	1
#define MAP_MARIO_MOVING_DIRECTION_UP		2
#define MAP_MARIO_MOVING_DIRECTION_DOWN		3

#define MAP_MARIO_ANI_SMALL_MARIO	0
#define MAP_MARIO_ANI_BIG_MARIO		1
#define MAP_MARIO_ANI_FIRE_MARIO	2
#define MAP_MARIO_ANI_TAIL_MARIO	3

#define MAP_MARIO_ANI_SET	9820

class CMapMario : public CGameObject
{
	int level;
	int movingDirection;
	float destination_x, destination_y;
public:
	CMapMario();

	void SetDestination(float x, float y);
	void SetLevel(int level) { this->level = level; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


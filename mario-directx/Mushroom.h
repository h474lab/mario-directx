#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Utils.h"
#include "Brick.h"
#include "Tube.h"

#define MUSHROOM_GRAVITY		0.001f
#define MUSHROOM_FLYING_SPEED_Y	0.025f
#define MUSHROOM_MOVING_SPEED_X	0.05f

#define MUSHROOM_LEVEL_SUPER	0
#define MUSHROOM_LEVEL_1UP		1

#define MUSHROOM_BBOX_WIDTH		16
#define MUSHROOM_BBOX_HEIGHT	16

#define MUSHROOM_ANI_SUPER		0
#define MUSHROOM_ANI_1UP		1

#define MUSHROOM_STATE_IDLE			0
#define MUSHROOM_STATE_MOVING_LEFT	1
#define MUSHROOM_STATE_MOVING_RIGHT	2
#define MUSHROOM_STATE_UNAVAILABLE	3

class CMushroom : public CGameObject
{
	int level;
	CGameObject* container;
public:
	CMushroom(int level);

	void SetLevel(int level) { this->level = level; }
	void SetState(int state);

	void Gain(CMario* player);

	void SetContainer(CGameObject* container) { this->container = container; }

	virtual void SetPosition(float x, float y);

	virtual void UpdateFlying(DWORD dt);
	virtual void SetMovingDirection(int movDirection);
	virtual void SetAppearingState() { SetState(MUSHROOM_STATE_IDLE); }
	virtual void SetDisappearingState() { SetState(MUSHROOM_STATE_UNAVAILABLE); }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


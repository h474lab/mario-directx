#pragma once
#include "GameObject.h"

#define FRAGMENT_STATE_HIDE		0
#define FRAGMENT_STATE_FLY_HIGH	1
#define FRAGMENT_STATE_FLY_LOW	2
#define FRAGMENT_STATE_OUT		3

#define FRAGMENT_BBOX_WIDTH		8
#define FRAGMENT_BBOX_HEIGHT	8

#define FRAGMENT_POSITION_TOP_LEFT	0
#define FRAGMENT_POSITION_TOP_RIGHT	1
#define FRAGMENT_POSITION_BOT_LEFT	2
#define FRAGMENT_POSITION_BOT_RIGHT	3

#define FRAGMENT_TOP_SPEED_X	0.1f
#define FRAGMENT_TOP_SPEED_Y	0.2f
#define FRAGMENT_BOT_SPEED_X	0.05f
#define FRAGMENT_BOT_SPEED_Y	0.1f

#define FRAGMENT_GRAVITY		0.004f
#define FRAGMENT_AVAILABLE_TIME	500

class CBrickFragment : public CGameObject
{
	int pos;

	DWORD available_start;
public:
	CBrickFragment();
	void SetPos(int pos) { this->pos = pos; }

	void Hit();

	virtual void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


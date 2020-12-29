#pragma once
#include "GameObject.h"

#define FLOATING_BLOCK_STATE_IDLE	0
#define FLOATING_BLOCK_STATE_FLOAT	1
#define FLOATING_BLOCK_STATE_DROP	2

#define FLOATING_BLOCK_ANI_LEFT		0
#define FLOATING_BLOCK_ANI_MID		1
#define FLOATING_BLOCK_ANI_RIGHT	2

#define FLOAT_BLOCK_BBOX_HEIGHT		16
#define FLOAT_BLOCK_BBOX_WIDTH		48

#define FLOAT_BLOCK_LEFT_X	0.0f
#define FLOAT_BLOCK_MID_X	16.0f
#define FLOAT_BLOCK_RIGHT_X	32.0f

#define FLOAT_BLOCK_FLOATING_SPEED_X	-0.03f
#define FLOAT_BLOCK_FLOATING_SPEED_Y	0.0f;
#define FLOAT_BLOCK_DROPPING_SPEED_X	0.0f;
#define FLOAT_BLOCK_DROPPING_SPEED_Y	0.05f

class CFloatingBlock : public CGameObject
{
public:
	CFloatingBlock();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


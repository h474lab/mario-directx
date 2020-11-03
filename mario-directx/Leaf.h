#pragma once
#include "GameObject.h"

#define EDGES_DISTANCE_X		48

#define LEAF_DROPPING_SPEED_X	0.04f
#define LEAF_GRAVITY			0.02f

#define LEAF_FLYING_Y			32
#define LEAF_FLYING_SPEED_Y		0.08f

#define LEAF_STATE_UNAVAILABLE	0
#define LEAF_STATE_DROP_LEFT	1
#define LEAF_STATE_DROP_RIGHT	2

#define LEAF_ANI_RIGHT	0
#define LEAF_ANI_LEFT	1

#define LEAF_BBOX_WIDTH		16
#define LEAF_BBOX_HEIGHT	12

class CLeaf : public CGameObject
{
	float leftEdge, rightEdge;
public:
	CLeaf();

	virtual void SetAppearingState() { SetState(LEAF_STATE_DROP_RIGHT); }
	virtual void SetPosition(float x, float y);
	virtual void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


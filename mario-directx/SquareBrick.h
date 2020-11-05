#pragma once
#include "GameObject.h"

#define SQUARE_BRICK_STATE_AVAILABLE	0
#define SQUARE_BRICK_STATE_UNAVAILABLE	1

#define SQUARE_BRICK_BBOX_WIDTH		16
#define SQUARE_BRICK_BBOX_HEIGHT	16

class CSquareBrick : public CGameObject
{
public:
	CSquareBrick() { background = 0; SetState(SQUARE_BRICK_STATE_AVAILABLE); }

	void Destroy();

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


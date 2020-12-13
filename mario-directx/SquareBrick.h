#pragma once
#include "GameObject.h"
#include "BrickFragment.h"

#define SQUARE_BRICK_STATE_AVAILABLE	0
#define SQUARE_BRICK_STATE_UNAVAILABLE	1

#define SQUARE_BRICK_BBOX_WIDTH		16
#define SQUARE_BRICK_BBOX_HEIGHT	16

class CSquareBrick : public CGameObject
{
	CBrickFragment *fragments[4];

	LPANIMATION_SET fragmentAnimationSet;
public:
	CSquareBrick();

	void Destroy();

	void SetFragmentAnimationSet(LPANIMATION_SET ani_set) { fragmentAnimationSet = ani_set; }

	CSquareBrick* Duplicate();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_ANI_TOPLEFT	0
#define BRICK_ANI_BOTLEFT	1
#define BRICK_ANI_TOPMID	2
#define BRICK_ANI_BOTMID	3
#define BRICK_ANI_TOPRIGHT	4
#define BRICK_ANI_BOTRIGHT	5

#define BRICK_POSITION_TOPLEFT	0
#define BRICK_POSITION_BOTLEFT	1
#define BRICK_POSITION_TOPMID	2
#define BRICK_POSITION_BOTMID	3
#define BRICK_POSITION_TOPRIGHT	4
#define BRICK_POSITION_BOTRIGHT	5

class CGroundBricks : public CGameObject
{
private:
	int position;
public:
	CGroundBricks(int position) { background = 0; this->position = position; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


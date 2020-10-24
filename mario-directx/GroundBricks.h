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

class CGroundBricks : public CGameObject
{
private:
	int numRows, numColumns;
public:
	CGroundBricks(int numRows, int numColumns) { background = 0; this->numRows = numRows; this->numColumns = numColumns; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


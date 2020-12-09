#pragma once
#include "GameObject.h"

#define COLORED_BLOCK_TYPE_TOP_LEFT		0
#define COLORED_BLOCK_TYPE_TOP_MID		1
#define COLORED_BLOCK_TYPE_TOP_RIGHT	2
#define COLORED_BLOCK_TYPE_MID_LEFT		3
#define COLORED_BLOCK_TYPE_MID_MID		4
#define COLORED_BLOCK_TYPE_MID_RIGHT	5
#define COLORED_BLOCK_TYPE_BOT_LEFT		6
#define COLORED_BLOCK_TYPE_BOT_MID		7
#define COLORED_BLOCK_TYPE_BOT_RIGHT	8

#define COLORED_BLOCK_ANI_TOP_LEFT	0
#define COLORED_BLOCK_ANI_TOP_MID	1
#define COLORED_BLOCK_ANI_TOP_RIGHT	2
#define COLORED_BLOCK_ANI_MID_LEFT	3
#define COLORED_BLOCK_ANI_MID_MID	4
#define COLORED_BLOCK_ANI_MID_RIGHT	5
#define COLORED_BLOCK_ANI_BOT_LEFT	6
#define COLORED_BLOCK_ANI_BOT_MID	7
#define COLORED_BLOCK_ANI_BOT_RIGHT	8

#define BRICK_SHADOW_TOP			9
#define BRICK_SHADOW_MID			10
#define BRICK_SHADOW_LEFT			11
#define BRICK_SHADOW_RIGHT			12

#define COLORED_BLOCK_CELL_WIDTH	16
#define COLORED_BLOCK_CELL_HEIGHT	16

#define BRICK_SHADOW_WIDTH			8
#define BRICK_SHADOW_HEIGHT			8

#define COLORED_CELL_LEFT_EDGE	-1
#define COLORED_CELL_RIGHT_EDGE	1

class CColoredBlock : public CGameObject
{
	int type;
public:
	CColoredBlock(int type);
	int IsTop();
	int IsEdge();

	virtual void Render();
	void RenderShadow();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
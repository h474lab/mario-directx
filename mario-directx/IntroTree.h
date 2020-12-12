#pragma once
#include "GameObject.h"

#define TREE_STATE_AVAILABLE	0
#define TREE_STATE_UNAVAILABLE	1

#define TREE_TYPE_SHORT	0
#define TREE_TYPE_HIGH	1

#define TREE_ANI_SHORT	0
#define TREE_ANI_HIGH	1

class CIntroTree : public CGameObject
{
	int type;
public:
	CIntroTree(int type);

	virtual void GetBoundingBox(float& left, float& top, float& bottom, float& right) { }
	virtual void Render();
};


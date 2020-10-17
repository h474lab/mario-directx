#pragma once
#include "GameObject.h"

#define QUESTIONBRICK_BBOX_WIDTH	16
#define QUESTIONBRICK_BBOX_HEIGHT	16

class CQuestionBrick : public CGameObject
{
public:
	CQuestionBrick() { background = 0; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


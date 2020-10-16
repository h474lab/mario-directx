#pragma once
#include "GameObject.h"

#define BACKGROUND_WIDTH	16
#define BACKGROUND_HEIGHT	16

class CBackground : public CGameObject
{
public:
	CBackground() { background = 1; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
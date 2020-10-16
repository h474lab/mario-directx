#pragma once
#include "GameObject.h"

#define TUBE_CELL_WIDTH		16
#define TUBE_CELL_HEIGHT	16

class CTube : public CGameObject
{
public:
	CTube() { background = 0; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


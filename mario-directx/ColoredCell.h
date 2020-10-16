#pragma once
#include "GameObject.h"

#define CELL_WIDTH		16
#define CELL_HEIGHT		16

class CColoredCell : public CGameObject
{
public:
	CColoredCell() { background = 0; }
	void SetPosition(int x, int y) { this->x = x; this->y = y; }
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
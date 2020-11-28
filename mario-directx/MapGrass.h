#pragma once
#include "GameObject.h"

#define MAP_GRASS_WIDTH		16
#define MAP_GRASS_HEIGHT	16


class CMapGrass : public CGameObject
{
	int numRows, numColumns;
public:
	CMapGrass(int numRows, int numColumns);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};


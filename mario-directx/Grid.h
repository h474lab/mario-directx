#pragma once
#include "GameObject.h"

#define MAX_GRID_COLUMNS	10
#define MAX_GRID_ROWS		10

class CGrid
{
private:
	CGameObject* unit[MAX_GRID_COLUMNS][MAX_GRID_ROWS];

	int numRows, numColumns;
	float start_x, start_y;
	float end_x, end_y;

	void InsertToGrid(CGameObject* object, int row, int column);
	void RemoveFromGrid(CGameObject* object, int row, int column);
public:
	CGrid();
	void AddObject(CGameObject* object);
};


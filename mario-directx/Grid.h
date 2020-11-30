#pragma once
#include "GameObject.h"

#define MAX_GRID_COLUMNS	100
#define MAX_GRID_ROWS		100

class CGrid
{
private:
	LPGAMEOBJECT unit[MAX_GRID_COLUMNS][MAX_GRID_ROWS];

	int numRows, numColumns;
	float start_x, start_y;
	float end_x, end_y;

	void InsertToGrid(LPGAMEOBJECT object, int row, int column);
	void RemoveFromGrid(LPGAMEOBJECT object, int row, int column);
public:
	CGrid();
	void AddObject(LPGAMEOBJECT object);
};

typedef CGrid* LPGRID;

class CGrids
{
	unordered_map<int, LPGRID> grids;
	static CGrids* __instance;
public:
	static CGrids* GetInstance();

	void Add(int id, LPGRID grid);
	LPGRID Get(int id);
};
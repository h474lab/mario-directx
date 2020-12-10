#pragma once
#include "GameObject.h"
#include <stdlib.h>

#define MAX_GRID_COLUMNS	100
#define MAX_GRID_ROWS		100

class CGrid
{
private:
	LPGAMEOBJECT cells[MAX_GRID_COLUMNS][MAX_GRID_ROWS];

	int numRows, numColumns;
	float start_x, start_y;
	float end_x, end_y;

	float cellWidth, cellHeight;

	void InsertToGrid(LPGAMEOBJECT object, int row, int column);
	void RemoveFromGrid(LPGAMEOBJECT object, int row, int column);
public:
	CGrid(float start_x, float start_y, float end_x, float end_y, int numRows, int numColumns);
	void AddObject(LPGAMEOBJECT object);
	void UpdateObject(CGameObject* object);
	vector<LPGAMEOBJECT> LoadCellsWithinCamera();
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
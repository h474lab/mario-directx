#pragma once
#include "GameObject.h"
#include <stdlib.h>

#define MAX_GRID_COLUMNS	100
#define MAX_GRID_ROWS		100

class CGrid
{
private:
	LPGAMEOBJECT cells[MAX_GRID_COLUMNS][MAX_GRID_ROWS];

	// number of rows and columns in the grid
	int numRows, numColumns;
	
	// the starting and ending position of grid
	float start_x, start_y;
	float end_x, end_y;

	// each cell in the grid has its size
	float cellWidth, cellHeight;

	// insert new object to grid
	void InsertToGrid(LPGAMEOBJECT object, int row, int column);
	// delete object from grid
	void RemoveFromGrid(LPGAMEOBJECT object, int row, int column);
public:
	CGrid(float start_x, float start_y, float end_x, float end_y, int numRows, int numColumns);
	void AddObject(LPGAMEOBJECT object);
	void UpdateObject(CGameObject* object);	// re-set object's position in the grid
	void ReplaceObject(CGameObject* object_1, CGameObject* object_2);	// replace object_1 in the grid by object_2
	void ClearCells();	// set all cells in the grid to NULL value
	vector<LPGAMEOBJECT> LoadCellsWithinCamera();	// get all cells appearing inside the camera
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
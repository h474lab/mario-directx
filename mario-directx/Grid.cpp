#include "Grid.h"
#include "Camera.h"
#include "Game.h"

void CGrid::InsertToGrid(LPGAMEOBJECT object, int row, int column)
{
	if (!unit[row][column])
	{
		object->SetPreviousObject(NULL);
		object->SetNextObject(NULL);
		unit[row][column] = object;
	}
	else if (object != unit[row][column])
	{
		object->SetPreviousObject(NULL);
		object->SetNextObject(unit[row][column]);
		unit[row][column] = object;
	}
}

void CGrid::RemoveFromGrid(LPGAMEOBJECT object, int row, int column)
{
	CGameObject* currentObject = unit[row][column];
	while (currentObject)
	{
		if (currentObject == object)
		{
			// if removing object is the first object in the list -> set the next object as the first object
			if (currentObject == unit[row][column]) unit[row][column] = currentObject->GetNextObject();

			// change next and previous object's next and previous object
			currentObject->GetPreviousObject()->SetNextObject(currentObject->GetNextObject());
			currentObject->GetNextObject()->SetPreviousObject(currentObject->GetPreviousObject());

			// re-set current object's previous and next object to NULL
			currentObject->SetPreviousObject(NULL);
			currentObject->SetNextObject(NULL);
		}
		currentObject = currentObject->GetNextObject();
	}
}

CGrid::CGrid(float start_x, float start_y, float end_x, float end_y, int numRows, int numColumns)
{
	this->start_x = start_x;
	this->start_y = start_y;
	this->end_x = end_x;
	this->end_y = end_y;

	this->numRows = numRows;
	this->numColumns = numColumns;

	for (int i = 0; i < MAX_GRID_ROWS; i++)
		for (int j = 0; j < MAX_GRID_COLUMNS; j++)
			unit[i][j] = NULL;
}

void CGrid::AddObject(LPGAMEOBJECT object)
{
	float obj_x, obj_y;
	object->GetPosition(obj_x, obj_y);

	// if the object is not in the grid area -> return
	if (obj_x > end_x || obj_x < start_x || obj_y > end_y || obj_y < start_y) return;

	// find grid width and height
	float gridHeight = end_y - start_y;
	float gridWidth = end_x - start_x;

	// calculate the height and width of each cell
	float cellHeight = gridHeight / (float)numRows;
	float cellWidth = gridWidth / (float)numColumns;

	// calculate row and column of this object
	int row = (int)((obj_y - start_y) / cellHeight);
	int column = (int)((obj_x - start_x) / cellWidth);

	InsertToGrid(object, row, column);
}

vector<LPGAMEOBJECT> CGrid::LoadCellsWithinCamera()
{
	vector<LPGAMEOBJECT> result;
	result.clear();

	float cam_x, cam_y;
	CCamera::GetInstance()->GetPosition(cam_x, cam_y);

	int screenWidth, screenHeight;
	screenWidth = CGame::GetInstance()->GetScreenWidth();
	screenHeight = CGame::GetInstance()->GetScreenHeight();

	// find grid width and height
	float gridHeight = end_y - start_y;
	float gridWidth = end_x - start_x;

	// calculate the height and width of each cell
	float cellHeight = gridHeight / (float)numRows;
	float cellWidth = gridWidth / (float)numColumns;

	int cell_start_x = (int)(cam_x / cellWidth);
	int cell_start_y = (int)(cam_y / cellHeight);
	int cell_end_x = (int)((cam_x + screenWidth) / cellWidth + 1);
	int cell_end_y = (int)((cam_y + screenHeight) / cellHeight + 1);

	for (int i = cell_start_x; i <= cell_end_x; i++)
		for (int j = cell_start_y; j <= cell_end_y; j++)
				result.push_back(unit[j][i]);

	return result;
}

CGrids* CGrids::__instance = NULL;

CGrids* CGrids::GetInstance()
{
	if (__instance == NULL) __instance = new CGrids();
	return __instance;
}

void CGrids::Add(int id, LPGRID grid)
{
	grids.insert(std::make_pair(id, grid));
}

LPGRID CGrids::Get(int id)
{
	return grids.at(id);
}

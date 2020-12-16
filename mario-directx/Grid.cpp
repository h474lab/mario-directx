#include "Grid.h"
#include "Camera.h"
#include "Game.h"

void CGrid::InsertToGrid(LPGAMEOBJECT object, int row, int column)
{
	// when current object is the first one in the cell
	if (!cells[row][column])
	{
		object->SetPreviousObject(NULL);
		object->SetNextObject(NULL);
		cells[row][column] = object;
	}
	// add it into the list at the first position
	else
	{
		cells[row][column]->SetPreviousObject(object);
		object->SetPreviousObject(NULL);
		object->SetNextObject(cells[row][column]);
		cells[row][column] = object;
	}
}

void CGrid::RemoveFromGrid(LPGAMEOBJECT object, int row, int column)
{
	CGameObject* currentObject = cells[row][column];
	while (currentObject)
	{
		if (currentObject == object)
		{
			// if removing object is the first object in the list -> set the next object as the first object
			if (currentObject == cells[row][column]) cells[row][column] = currentObject->GetNextObject();

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

	// find grid width and height
	float gridHeight = end_y - start_y;
	float gridWidth = end_x - start_x;

	// calculate the height and width of each cell
	cellHeight = gridHeight / (float)numRows;
	cellWidth = gridWidth / (float)numColumns;

	ClearCells();
}

void CGrid::AddObject(LPGAMEOBJECT object)
{
	float obj_x, obj_y;
	object->GetPosition(obj_x, obj_y);

	// if the object is not in the grid area -> return
	if (obj_x > end_x || obj_x < start_x || obj_y > end_y || obj_y < start_y) return;

	// calculate row and column of this object
	int row = (int)((obj_y - start_y) / cellHeight);
	int column = (int)((obj_x - start_x) / cellWidth);

	object->SetGridPosition(row, column);
	InsertToGrid(object, row, column);
}

void CGrid::UpdateObject(CGameObject* object)
{
	// get last position in grid
	int oldGridRow = -1, oldGridColumn = -1;
	object->GetGridPosition(oldGridRow, oldGridColumn);

	// get current position in the scene
	float obj_x, obj_y;
	object->GetPosition(obj_x, obj_y);

	// get expected row/column in grid
	int expectedRow = (int)((obj_y - start_y) / cellHeight);
	int expectedColumn = (int)((obj_x - start_x) / cellWidth);

	// should not continue change object's grid cell
	if (oldGridRow == expectedRow && oldGridColumn == expectedColumn) return;

	if (dynamic_cast<CKoopa*>(object) && (object->GetState() == KOOPA_STATE_ROLLING_DOWN_LEFT || object->GetState() == KOOPA_STATE_ROLLING_DOWN_RIGHT))
		DebugOut(L"\nFrom [%d, %d] to [%d, %d]", oldGridRow, oldGridColumn, expectedRow, expectedColumn);

	// remove object from last cell
	// if object is the first one in cell
	if (object->GetPreviousObject() == NULL)
	{
		cells[oldGridRow][oldGridColumn] = object->GetNextObject();
		if (object->GetNextObject()) object->GetNextObject()->SetPreviousObject(NULL);
	}
	// if object is in the middle of linked list
	else
	{
		if (object->GetPreviousObject()) object->GetPreviousObject()->SetNextObject(object->GetNextObject());
		if (object->GetNextObject()) object->GetNextObject()->SetPreviousObject(object->GetPreviousObject());
	}

	// add object to the new cell
	AddObject(object);
}

// replace object_1 by object_2 in the grid
void CGrid::ReplaceObject(CGameObject* object_1, CGameObject* object_2)
{
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numColumns; j++)
		{
			CGameObject* currentObject = cells[i][j];
			while (currentObject)
			{
				// [gotcha!!] found the object to be replaced
				if (currentObject == object_1)
				{
					// set new object (object_2) nearby objects
					object_2->SetPreviousObject(currentObject->GetPreviousObject());
					object_2->SetNextObject(currentObject->GetNextObject());

					// clear current object from the list
					if (currentObject->GetPreviousObject() == NULL)
						cells[i][j] = object_2;
					else
						currentObject->GetPreviousObject()->SetNextObject(object_2);

					if (currentObject->GetNextObject()) currentObject->GetNextObject()->SetPreviousObject(object_2);

					// after completing replacing -> done
					return;
				}
				// on the other hand, continue getting the next object in the list
				currentObject = currentObject->GetNextObject();
			}
		}
}

void CGrid::ClearCells()
{
	for (int i = 0; i < MAX_GRID_ROWS; i++)
		for (int j = 0; j < MAX_GRID_COLUMNS; j++)
			cells[i][j] = NULL;
}

vector<LPGAMEOBJECT> CGrid::LoadCellsWithinCamera()
{
	/*
		The camera edges is:
			width [cam_x, cam_x + screenWidth]
			height [cam_y, cam_y + screenHeight]
	*/

	vector<LPGAMEOBJECT> result;
	result.clear();

	float cam_x, cam_y;
	CCamera::GetInstance()->GetPosition(cam_x, cam_y);

	int screenWidth, screenHeight;
	screenWidth = CGame::GetInstance()->GetScreenWidth();
	screenHeight = CGame::GetInstance()->GetScreenHeight();

	int cell_start_x = (int)(cam_x / cellWidth);
	int cell_start_y = (int)(cam_y / cellHeight);
	int cell_end_x = (int)((cam_x + screenWidth) / cellWidth);
	int cell_end_y = (int)((cam_y + screenHeight) / cellHeight);

	for (int i = cell_start_x; i <= cell_end_x; i++)
		for (int j = cell_start_y; j <= cell_end_y; j++)
				result.push_back(cells[j][i]);

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

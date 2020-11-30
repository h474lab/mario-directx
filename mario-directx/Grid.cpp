#include "Grid.h"

void CGrid::InsertToGrid(CGameObject* object, int row, int column)
{
	if (!unit[row][column])
	{
		object->SetPreviousObject(NULL);
		object->SetNextObject(NULL);
	}
	else
	{
		object->SetPreviousObject(NULL);
		object->SetNextObject(unit[row][column]);
		unit[row][column] = object;
	}
}

void CGrid::RemoveFromGrid(CGameObject* object, int row, int column)
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

CGrid::CGrid()
{
	for (int i = 0; i < MAX_GRID_COLUMNS; i++)
		for (int j = 0; j < MAX_GRID_ROWS; j++)
			unit[i][j] = NULL;
}

void CGrid::AddObject(CGameObject* object)
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
	int row = (obj_y - start_y) / cellHeight;
	int column = (obj_x - start_x) / cellWidth;

	InsertToGrid(object, row, column);
}

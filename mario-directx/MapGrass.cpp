#include "MapGrass.h"

CMapGrass::CMapGrass(int numRows, int numColumns)
{
	this->numRows = numRows;
	this->numColumns = numColumns;
}

void CMapGrass::Render()
{
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numColumns; j++)
			animation_set->at(0)->Render(x + j * MAP_GRASS_WIDTH, y + i * MAP_GRASS_HEIGHT);
}

#include "ColoredBlock.h"

void CColoredBlock::addCell(CColoredCell cell, int r, int c)
{
	cells[r][c] = new CColoredCell();

	float cL, cT, cR, cB;
	cells[r][c]->GetBoundingBox(cL, cT, cR, cB);
	float width = cR - cL;
	float height = cB - cT;

	cells[r][c]->SetPosition(this->x + c * width, this->y + r * height);
}

void CColoredBlock::Render()
{
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numColumns; j++)
			cells[i][j]->Render();
}

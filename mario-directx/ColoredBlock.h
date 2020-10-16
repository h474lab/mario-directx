#pragma once
#include "ColoredCell.h"

class CColoredBlock
{
	int x, y;
	int numRows, numColumns;
	CColoredCell ***cells;
public:
	CColoredBlock(int rows, int columns) { numRows = rows; numColumns = columns; }
	void addCell(CColoredCell cell, int r, int c);
	void Render();
};
#pragma once
#include "GameObject.h"

#define TUBE_CELL_WIDTH		16
#define TUBE_CELL_HEIGHT	16

#define TUBE_ANI_UPPER_LID_LEFT		0
#define TUBE_ANI_UPPER_LID_RIGHT	1
#define TUBE_ANI_LEFT_EDGE			2
#define TUBE_ANI_RIGHT_EDGE			3
#define TUBE_ANI_LOWER_LID_LEFT		4
#define TUBE_ANI_LOWER_LID_RIGHT	5

class CTube : public CGameObject
{
	int numRows;
	int hasLid;		// hasLid = 0 - no lid, 1 - upper lid, 2 - lower lid
public:
	CTube(int numRows, int hasLid);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


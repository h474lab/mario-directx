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

#define TUBE_OBJECT_DELAYING_TIME	2000

class CTube : public CGameObject
{
	int numRows;
	int hasLid;		// hasLid = 0 - no lid, 1 - upper lid, 2 - lower lid

	CGameObject* object;
	DWORD objectDelay_start;
	int objLastState;
public:
	CTube(int numRows, int hasLid);

	void StartDelayingObject() { objectDelay_start = (DWORD)GetTickCount64(); }

	virtual void SetPosition(float x, float y);

	void SetObject(CGameObject* obj) { object = obj; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


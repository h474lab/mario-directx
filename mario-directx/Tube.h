#pragma once
#include "GameObject.h"

#define TUBE_CELL_WIDTH		16
#define TUBE_CELL_HEIGHT	16

#define TUBE_TYPE_NO_LID	0
#define TUBE_TYPE_UPPER_LID	1
#define TUBE_TYPE_LOWER_LID	2

#define TUBE_ZONE_NO_DOOR	-1

#define TUBE_ANI_UPPER_LID_LEFT		0
#define TUBE_ANI_UPPER_LID_RIGHT	1
#define TUBE_ANI_LEFT_EDGE			2
#define TUBE_ANI_RIGHT_EDGE			3
#define TUBE_ANI_LOWER_LID_LEFT		4
#define TUBE_ANI_LOWER_LID_RIGHT	5

#define TUBE_MAX_COLUMN	2

#define TUBE_OBJECT_DELAYING_TIME	2000

class CTube : public CGameObject
{
	int numRows;
	int lidType;
	int doorToZone;

	CGameObject* object;
	DWORD objectDelay_start;
	int objLastState;
public:
	CTube(int numRows, int lidType, int zoneID);

	void StartDelayingObject() { objectDelay_start = (DWORD)GetTickCount64(); }

	virtual void SetPosition(float x, float y);
	void SetObject(CGameObject* obj) { object = obj; }

	int GetZoneToSwitch() { return doorToZone; }
	int GetLidType() { return lidType; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


#pragma once
#include "GameObject.h"

#define CURTAIN_SIZE_LARGE_HEIGHT		15
#define CURTAIN_SIZE_COLLAPSED_HEIGHT	13

#define CURTAIN_TYPE_LARGE		0
#define CURTAIN_TYPE_COLLAPSED	1

#define CURTAIN_ANI_MID		0
#define CURTAIN_ANI_END		1
#define CURTAIN_ANI_HEADING	2

#define CURTAIN_STATE_IDLE			0
#define CURTAIN_STATE_PULLING_UP	1

#define CURTAIN_PULLING_SPEED_Y		0.5f

class CCurtain : public CGameObject
{
	int numRows;
	int type;
public:
	CCurtain(int numberOfRows, int type);

	void SetType(int curtainType) { type = curtainType; }
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


#pragma once
#include "TubeEnemy.h"

#define PIRANHA_PLANT_BBOX_WIDTH	16
#define PIRANHA_PLANT_BBOX_HEIGHT	24

#define PIRANHA_PLANT_SPEED_Y		0.01f
#define PIRANHA_PLANT_DELAY_TIME	3000

class CPiranhaPlant : public CTubeEnemy
{
public:
	CPiranhaPlant();
	virtual void SetPosition(float x, float y);

	virtual void SetAppearingState(int state) { SetState(TUBE_ENEMY_STATE_IDLE); }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


#include "PiranhaPlant.h"

void CPiranhaPlant::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	minFlyingY = y - PIRANHA_PLANT_BBOX_HEIGHT;
	maxFlyingY = y + 1;
	flyingSpeedY = PIRANHA_PLANT_SPEED_Y;
	delayAfterMovingUp = 1;
	delay_time = PIRANHA_PLANT_DELAY_TIME;

	followingObject = NULL;

	state = TUBE_ENEMY_STATE_IDLE;
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TUBE_ENEMY_STATE_DIE)
	{
		background = 1;
		return;
	}
	left = x;
	top = y;
	right = x + PIRANHA_PLANT_BBOX_WIDTH;
	bottom = y + PIRANHA_PLANT_BBOX_HEIGHT;
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CTubeEnemy::Update(dt, coObjects);
}

void CPiranhaPlant::Render()
{
	if (state == TUBE_ENEMY_STATE_DIE) return;

	animation_set->at(0)->Render(x, y);
}

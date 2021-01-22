#include "FireFlower.h"

CFireFlower::CFireFlower()
{
	SetState(FIRE_FLOWER_STATE_UNAVAILABLE);
}

void CFireFlower::SetState(int state)
{
	if (state == FIRE_FLOWER_STATE_AVAILABLE)
		background = 0;
	else background = 1;

	CGameObject::SetState(state);
}

void CFireFlower::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	minFlyingY = y - FIRE_FLOWER_BBOX_HEIGHT;
	maxFlyingY = y - FIRE_FLOWER_BBOX_HEIGHT;
	flyingSpeedY = FIRE_FLOWER_FLYING_SPEED_Y;
	delayAfterMovingUp = 0;
}

void CFireFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FIRE_FLOWER_STATE_AVAILABLE)
	{
		left = x;
		top = y;
		right = left + FIRE_FLOWER_BBOX_WIDTH;
		bottom = top + FIRE_FLOWER_BBOX_HEIGHT;
	}
}

void CFireFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (flyingDirection != FLYING_DIRECTION_NOMOVE)
	{
		UpdateFlying(dt);
		return;
	}
}

void CFireFlower::Render()
{
	if (state == FIRE_FLOWER_STATE_UNAVAILABLE) return;
	animation_set->at(FIRE_FLOWER_ANI_AVAILABLE)->Render(x, y);
}

#include "ShortFireTrap.h"

void CShortFireTrap::SetPosition(float x, float y)
{
	CFireTrap::SetPosition(x, y);

	minFlyingY = y - FIRE_TRAP_BBOX_HEIGHT;
	maxFlyingY = y + 1;
	flyingSpeedY = FIRE_TRAP_FLYING_SPEED_Y;
	delayAfterMovingUp = 1;
	delay_time = FIRE_TRAP_DELAY_FLYING_TIME;
}

void CShortFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIRE_TRAP_BBOX_WIDTH;
	bottom = y + FIRE_TRAP_BBOX_HEIGHT;
}

void CShortFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CFireTrap::Update(dt, coObjects);
}

void CShortFireTrap::Render()
{
	CFireTrap::Render();
}

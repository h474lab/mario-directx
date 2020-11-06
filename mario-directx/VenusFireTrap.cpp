#include "VenusFireTrap.h"
#include "Utils.h"

void CVenusFireTrap::SetPosition(float x, float y)
{
	CFireTrap::SetPosition(x, y);

	minFlyingY = y - FIRE_TRAP_BBOX_HEIGHT;
	maxFlyingY = y + 1;
	flyingSpeedY = FIRE_TRAP_FLYING_SPEED_Y;
	delayAfterMovingUp = 1;
	delay_time = FIRE_TRAP_DELAY_FLYING_TIME;
}

void CVenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TUBE_ENEMY_STATE_DIE || state == TUBE_ENEMY_STATE_UNAVAILABLE)
	{
		background = 1;
		return;
	}
	left = x;
	top = y;
	right = x + FIRE_TRAP_BBOX_WIDTH;
	bottom = y + FIRE_TRAP_BBOX_HEIGHT;
}

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CFireTrap::Update(dt, coObjects);
	//DebugOut(L"\nState: %d", state);
}

void CVenusFireTrap::Render()
{
	CFireTrap::Render();
}

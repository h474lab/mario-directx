#include "SwitchBlock.h"

CSwitchBlock::CSwitchBlock()
{
	SetState(SWITCH_BLOCK_STATE_UNAVAILABLE);
}

void CSwitchBlock::Switch()
{
	SetState(SWITCH_BLOCK_STATE_PRESSED);
}

void CSwitchBlock::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	minFlyingY = y - SWITCH_BLOCK_HEIGHT;
	maxFlyingY = y - SWITCH_BLOCK_HEIGHT;
	flyingSpeedY = SWITCH_BLOCK_FLYING_SPEED_Y;
	delayAfterMovingUp = 0;
}

void CSwitchBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SWITCH_BLOCK_STATE_UNPRESSED:
		background = 0;
		break;
	case SWITCH_BLOCK_STATE_PRESSED:
		background = 1;
		break;
	case SWITCH_BLOCK_STATE_UNAVAILABLE:
		background = 1;
		break;
	}
}

void CSwitchBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == SWITCH_BLOCK_STATE_UNPRESSED)
	{
		left = x;
		top = y;
		right = x + SWITCH_BLOCK_WIDTH;
		bottom = y + SWITCH_BLOCK_HEIGHT;
	}
}

void CSwitchBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (flyingDirection != FLYING_DIRECTION_NOMOVE)
	{
		UpdateFlying(dt);
		return;
	}
}

void CSwitchBlock::Render()
{
	if (state == SWITCH_BLOCK_STATE_UNAVAILABLE) return;

	if (state == SWITCH_BLOCK_STATE_UNPRESSED)
		animation_set->at(SWITCH_BLOCK_ANI_UNPRESSED)->Render(x, y);
	else
		animation_set->at(SWITCH_BLOCK_ANI_PRESSED)->Render(x, y);
}

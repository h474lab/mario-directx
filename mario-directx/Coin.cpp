#include "Coin.h"
#include "Utils.h"

CCoin::CCoin()
{
	background = 0;
	SetState(COIN_STATE_AVAILABLE);

	flyingSpeedY = COIN_FLYING_SPEED_Y;
	delayAfterMovingUp = 0;
	disappear = 1;
}

void CCoin::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	minFlyingY = y - 4 * COIN_BBOX_HEIGHT;
	maxFlyingY = y - 2 * COIN_BBOX_HEIGHT;
}

void CCoin::SetDisappearingState()
{
	SetState(COIN_STATE_UNAVAILABLE);
}

void CCoin::SetAppearingState()
{
	SetState(COIN_STATE_AVAILABLE);
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (state == COIN_STATE_UNAVAILABLE) background = 1;
	UpdateFlying(dt);
}

void CCoin::Render()
{
	if (state == COIN_STATE_AVAILABLE)
		animation_set->at(0)->Render(x, y);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

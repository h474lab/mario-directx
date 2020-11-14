#include "BrickFragment.h"

void CBrickFragment::Hit()
{
	if (pos == FRAGMENT_POSITION_BOT_LEFT || pos == FRAGMENT_POSITION_BOT_RIGHT)
		SetState(FRAGMENT_STATE_FLY_LOW);
	else
		SetState(FRAGMENT_STATE_FLY_HIGH);
	available_start = (DWORD)GetTickCount64();
}

void CBrickFragment::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case FRAGMENT_STATE_FLY_LOW:
		if (pos == FRAGMENT_POSITION_BOT_LEFT)
			vx = -FRAGMENT_BOT_SPEED_X;
		else
			vx = FRAGMENT_BOT_SPEED_X;
		vy = -FRAGMENT_BOT_SPEED_Y;
		break;
	case FRAGMENT_STATE_FLY_HIGH:
		if (pos == FRAGMENT_POSITION_TOP_LEFT)
			vx = -FRAGMENT_TOP_SPEED_X;
		else
			vx = FRAGMENT_TOP_SPEED_X;
		vy = -FRAGMENT_TOP_SPEED_Y;
		break;
	}
}

void CBrickFragment::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == FRAGMENT_STATE_HIDE || state == FRAGMENT_STATE_OUT) return;

	// check if exeeded fragment available time
	if (GetTickCount64() - available_start > FRAGMENT_AVAILABLE_TIME)
	{
		SetState(FRAGMENT_STATE_OUT);
		return;
	}

	vy += FRAGMENT_GRAVITY;
	CGameObject::Update(dt);

	x += dx;
	y += dy;
}

void CBrickFragment::Render()
{
	if (state != FRAGMENT_STATE_HIDE && state != FRAGMENT_STATE_OUT)
		animation_set->at(0)->Render(x, y);
}

void CBrickFragment::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FRAGMENT_BBOX_WIDTH;
	b = y + FRAGMENT_BBOX_HEIGHT;
}

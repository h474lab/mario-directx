#include "Beetle.h"

void CBeetle::KickBeetleOut(int direction)
{
	SetState(BEETLE_STATE_FLYING_OUT);
	if (direction)
		vx = BEETLE_FLYING_OUT_SPEED_X;
	else
		vx = -BEETLE_FLYING_OUT_SPEED_X;
	vy -= BEETLE_FLYING_OUT_SPEED_Y;
}

void CBeetle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BEETLE_STATE_UNAVAILABLE:
		vx = vy = 0.0f;
		break;
	case BEETLE_STATE_FLYING_OUT:
		background = 1;
		break;
	case BEETLE_STATE_DROPPING:
		background = 0;
		break;
	}
}

void CBeetle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BEETLE_WIDTH;
	bottom = top + BEETLE_HEIGHT;
}

void CBeetle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BEETLE_STATE_UNAVAILABLE) return;
	
	float lastVx = vx, lastVy = vy;

	vy += BEETLE_GRAVITY;
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny;
		float rdx, rdy;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for each (LPCOLLISIONEVENT event in coEventsResult)
		{
			if (event->ny < 0 && state == BEETLE_STATE_DROPPING) vy = -lastVy * BEETLE_DROP_BOUNCING;
		}
	}
}

void CBeetle::Render()
{
	int ani = BEETLE_ANI_NONE;
	if (state == BEETLE_STATE_DROPPING || state == BEETLE_STATE_LYING)
		ani = BEETLE_ANI_LYING;
	else if (state == BEETLE_STATE_ROLLING_LEFT || state == BEETLE_STATE_ROLLING_RIGHT)
		ani = BEETLE_ANI_ROLLING;
	else if (state == BEETLE_STATE_WALKING_LEFT)
		ani = BEETLE_ANI_WALKING_LEFT;
	else if (state == BEETLE_STATE_WALKING_RIGHT)
		ani = BEETLE_ANI_WALKING_RIGHT;

	if (ani != BEETLE_ANI_NONE) animation_set->at(ani)->Render(x, y);
}

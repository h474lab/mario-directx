#include "Mushroom.h"
#include "Utils.h"
#include "Brick.h"
#include "Tube.h"
#include "Mario.h"

CMushroom::CMushroom(int level)
{
	background = 0;
	SetLevel(level);
	SetState(MUSHROOM_STATE_IDLE);
}

void CMushroom::SetState(int state)
{
	background = 0;
	switch (state)
	{
	case MUSHROOM_STATE_IDLE:
		vx = 0.0f;
		break;
	case MUSHROOM_STATE_MOVING_LEFT:
		vx = -MUSHROOM_MOVING_SPEED_X;
		nx = -1;
		break;
	case MUSHROOM_STATE_MOVING_RIGHT:
		vx = MUSHROOM_MOVING_SPEED_X;
		nx = 1;
		break;
	case MUSHROOM_STATE_UNAVAILABLE:
		vx = 0.0f;
		background = 1;
		break;
	}
	this->state = state;
}

void CMushroom::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);

	minFlyingY = y - MUSHROOM_BBOX_HEIGHT - 1;
	maxFlyingY = y - MUSHROOM_BBOX_HEIGHT - 1;
	flyingSpeedY = MUSHROOM_FLYING_SPEED_Y;
	delayAfterMovingUp = 0;
	disappear = 0;
}

void CMushroom::UpdateFlying(DWORD dt)
{
	//DebugOut(L"\nContainer flying direction: %d", container->GetFlyingDirection());
	if (container->GetFlyingDirection() == FLYING_DIRECTION_NOMOVE && flyingDirection != FLYING_DIRECTION_NOMOVE)
	{
		CGameObject::UpdateFlying(dt);
	}
}

void CMushroom::SetMovingDirection(int movDirection)
{
	if (movDirection == 1)
		SetState(MUSHROOM_STATE_MOVING_RIGHT);
	else
		SetState(MUSHROOM_STATE_MOVING_LEFT);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MUSHROOM_BBOX_WIDTH;
	bottom = y + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"\nDisappear: %d", disappear);
	DebugOut(L"\nPosition: %f, %f", x, y);
	DebugOut(L"\nFlying state: %d", flyingDirection);
	UpdateFlying(dt);

	//DebugOut(L"\nFlying Speed: %f", flyingSpeedY);

	if (state == MUSHROOM_STATE_UNAVAILABLE || flyingDirection != 0) return;

	vy += MUSHROOM_GRAVITY * dt;

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

		for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			
			if (dynamic_cast<CTube*>(e->obj) && e->nx != 0)
			{
				if (state == MUSHROOM_STATE_MOVING_LEFT)
					SetState(MUSHROOM_STATE_MOVING_RIGHT);
				else if (state == MUSHROOM_STATE_MOVING_RIGHT)
					SetState(MUSHROOM_STATE_MOVING_LEFT);
			}
			if (dynamic_cast<CMario*>(e->obj))
			{
				CMario* mario = dynamic_cast<CMario*>(e->obj);

				SetState(MUSHROOM_STATE_UNAVAILABLE);
				mario->LevelUp();
			}
			else
			{
				if (e->nx != 0)
				{
					SetState(state);
				}
			}
		}

		CGameObject::Update(dt, coObjects);
		x += dx;
		y += dy;

	}
}

void CMushroom::Render()
{
	if (state == MUSHROOM_STATE_UNAVAILABLE) return;
	
	if (level == MUSHROOM_LEVEL_1UP)
		animation_set->at(MUSHROOM_ANI_1UP)->Render(x, y);
	else
		animation_set->at(MUSHROOM_ANI_SUPER)->Render(x, y);
}

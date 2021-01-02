#include "BoomerangBro.h"

CBoomerangBro::CBoomerangBro()
{
	background = 0;
	walkingCount = 0;
	jumping = 0;
	followingObject = NULL;
	renderScore = RENDER_SCORE_BOOMERANG_BRO;

	SetState(BOOMERANG_BRO_STATE_MOVING_FORWARD);
}

void CBoomerangBro::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	// set left and right bound to Boomerang Bro so that he could move inside this area
	leftBound = x;
	rightBound = leftBound + BOOMERANG_BRO_WALKING_DISTANCE;
}

void CBoomerangBro::SetState(int state)
{
	switch (state)
	{
	case BOOMERANG_BRO_STATE_MOVING_FORWARD:
		background = 0;
		if (nx > 0)
		{
			vx = BOOMERANG_BRO_WALKING_SPEED_X;
			vy = BOOMERANG_BRO_WALKING_SPEED_Y;
		}
		else
		{
			vx = -BOOMERANG_BRO_WALKING_SPEED_X;
			vy = BOOMERANG_BRO_WALKING_SPEED_Y;
		}
		break;
	case BOOMERANG_BRO_STATE_MOVING_BACKWARD:
		background = 0;
		if (nx > 0)
		{
			vx = -BOOMERANG_BRO_WALKING_SPEED_X;
			vy = BOOMERANG_BRO_WALKING_SPEED_Y;
		}
		else
		{
			vx = BOOMERANG_BRO_WALKING_SPEED_X;
			vy = BOOMERANG_BRO_WALKING_SPEED_Y;
		}
		break;
	case BOOMERANG_BRO_STATE_JUMPING:
		background = 0;
		if (nx > 0)
		{
			vx = -BOOMERANG_BRO_WALKING_SPEED_X;
			vy = -BOOMERANG_BRO_WALKING_SPEED_Y;
		}
		else
		{
			vx = BOOMERANG_BRO_WALKING_SPEED_X;
			vy = -BOOMERANG_BRO_WALKING_SPEED_Y;
		}
		break;
	case BOOMERANG_BRO_STATE_DYING:
		background = 1;
		vx = BOOMERANG_BRO_DYING_SPEED_X;
		vy = BOOMERANG_BRO_DYING_SPEED_Y;
		break;
	}

	CGameObject::SetState(state);
}

void CBoomerangBro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BOOMERANG_BRO_BBOX_WIDTH;
	bottom = y + BOOMERANG_BRO_BBOX_HEIGHT;
}

void CBoomerangBro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)
{
	// calculate Boomerang Bro gravity
	vy += BOOMERANG_BRO_GRAVITY;
	// update Boomerang Bro position
	CGameObject::Update(dt);

	// exit collision calculation when Boomerang Bro has been dead
	if (state == BOOMERANG_BRO_STATE_DYING) return;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	jumping = 1;

	// update Boomerang Bro position if there are no collisions
	if (coEvents.size() == 0 || state == BOOMERANG_BRO_STATE_DYING)
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
			if (event->dy < 0)
				jumping = 0;
		}
	}

	if (state == BOOMERANG_BRO_STATE_JUMPING && !jumping)
		SetState(BOOMERANG_BRO_STATE_MOVING_FORWARD);
	else if (state == BOOMERANG_BRO_STATE_MOVING_FORWARD && x >= rightBound)
	{
		x = rightBound;
		SetState(BOOMERANG_BRO_STATE_MOVING_BACKWARD);
		// start jumping when Boomerang Bro has reached his walking limit
		if (walkingCount == BOOMERANG_BRO_WALKING_TIMES)
		{
			// reset walking count parameter
			walkingCount = 0;
			// start jumping
			SetState(BOOMERANG_BRO_STATE_JUMPING);
		}
	}
	else if (state == BOOMERANG_BRO_STATE_MOVING_FORWARD && x <= leftBound)
	{
		x = leftBound;
		SetState(BOOMERANG_BRO_STATE_MOVING_FORWARD);
		walkingCount++;
	}
}

void CBoomerangBro::Render()
{
	if (nx > 0)
	{
		if (state == BOOMERANG_BRO_STATE_DYING)
			animation_set->at(BOOMERANG_BRO_ANI_DYING_RIGHT)->Render(x, y);
		else
			animation_set->at(BOOMERANG_BRO_ANI_WALKING_RIGHT)->Render(x, y);
	}
	else if (nx < 0)
	{
		if (state == BOOMERANG_BRO_STATE_DYING)
			animation_set->at(BOOMERANG_BRO_ANI_DYING_LEFT)->Render(x, y);
		else
			animation_set->at(BOOMERANG_BRO_ANI_WALKING_LEFT)->Render(x, y);
	}
}
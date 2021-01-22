#include "BoomerangBro.h"

CBoomerangBro::CBoomerangBro()
{
	background = 0;
	walkingCount = 0;
	jumping = 0;
	currentBoomerang = 0;
	nx = 0;
	followingObject = NULL;
	renderScore = RENDER_SCORE_BOOMERANG_BRO;

	SetState(BOOMERANG_BRO_STATE_MOVING_FORWARD);
}

void CBoomerangBro::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	// set left and right bound to Boomerang Bro so that he could move inside this area
	ix = x;
	iy = y;
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
			vx = -BOOMERANG_BRO_JUMPING_SPEED_X;
			vy = -BOOMERANG_BRO_JUMPING_SPEED_Y;
		}
		else
		{
			vx = BOOMERANG_BRO_JUMPING_SPEED_X;
			vy = -BOOMERANG_BRO_JUMPING_SPEED_Y;
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

void CBoomerangBro::ThrowBoomerang()
{
	throwing = 1;
	throwing_start = (DWORD)GetTickCount64();
	throwing_delay_start = (DWORD)GetTickCount64();

	// throw boomerang at current position if possible
	if (boomerangs.size() > 0)
	{
		if (++currentBoomerang == boomerangs.size())
			currentBoomerang = 0;

		boomerangs[currentBoomerang]->SetPosition(x, y - 4);
	}
}

void CBoomerangBro::InsertBoomerang(CBoomerang *boomerang)
{
	boomerangs.push_back(boomerang);
}

void CBoomerangBro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BOOMERANG_BRO_BBOX_WIDTH;
	bottom = y + BOOMERANG_BRO_BBOX_HEIGHT;
}

void CBoomerangBro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// get Mario's position
	float fx, fy;
	followingObject->GetPosition(fx, fy);
	// set Boomerang Bro direction based on Mario's position
	if (fx > x)
	{
		if (this->nx != 1.0f)
		{
			this->nx = 1;
			SetPosition(x, y);
			SetState(BOOMERANG_BRO_STATE_MOVING_FORWARD);
		}

		this->nx = 1;
		leftBound = ix;
		rightBound = ix + BOOMERANG_BRO_WALKING_DISTANCE;
	}
	else
	{
		if (this->nx != -1.0f)
		{
			this->nx = -1;
			SetPosition(x, y);
			SetState(BOOMERANG_BRO_STATE_MOVING_FORWARD);
		}

		this->nx = -1;
		leftBound = ix - BOOMERANG_BRO_WALKING_DISTANCE;
		rightBound = ix;
	}

	// calculate Boomerang Bro gravity
	vy += BOOMERANG_BRO_GRAVITY;
	// update Boomerang Bro position
	CGameObject::Update(dt);

	// exit collision calculation when Boomerang Bro has been dead
	if (state == BOOMERANG_BRO_STATE_DYING)
	{
		x += dx;
		y += dy;
		return;
	}

	if ((DWORD)GetTickCount64() - throwing_delay_start > BOOMERANG_BRO_THROWING_DELAY)
		ThrowBoomerang();
	if ((DWORD)GetTickCount64() - throwing_start > BOOMERANG_BRO_THROWING_TIME)
	{
		int throwingDirection;
		if (nx > 0)
			throwingDirection = BOOMERANG_DIRECTION_RIGHT;
		else
			throwingDirection = BOOMERANG_DIRECTION_LEFT;
		boomerangs[currentBoomerang]->Throw(throwingDirection);

		throwing = 0;
	}
	else
	{
		boomerangs[currentBoomerang]->SetPosition(x, y - 4);
	}
	
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

		if (ny != 0) vy = 0;

		for each (LPCOLLISIONEVENT event in coEventsResult)
		{
			if (event->ny < 0)
				jumping = 0;

			if (CBoomerang* boomerang = dynamic_cast<CBoomerang*>(event->obj))
			{
				// destroy boomerang when it goes back to BoomerangBro
				boomerang->SetState(BOOMERANG_STATE_HIDE);
			}
		}

		if (state == BOOMERANG_BRO_STATE_JUMPING && !jumping)
			SetState(BOOMERANG_BRO_STATE_MOVING_FORWARD);
		else if (state == BOOMERANG_BRO_STATE_MOVING_FORWARD)
		{
			if ((this->nx > 0 && x >= rightBound) || (this->nx < 0 && x <= leftBound))
			{
				if (this->nx > 0) x = rightBound;
				else x = leftBound;
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
		}
		else if (state == BOOMERANG_BRO_STATE_MOVING_BACKWARD)
		{
			if ((this->nx > 0 && x <= leftBound) || (this->nx < 0 && x >= rightBound))
			{
				if (this->nx > 0) x = leftBound;
				else x = rightBound;

				SetState(BOOMERANG_BRO_STATE_MOVING_FORWARD);
				walkingCount++;
			}
		}

		CGameObject::Update(dt);
		x += dx;
		y += dy;
	}
}

void CBoomerangBro::Render()
{
	if (nx > 0)
	{
		if (state == BOOMERANG_BRO_STATE_DYING)
			animation_set->at(BOOMERANG_BRO_ANI_DYING_RIGHT)->Render(x, y);
		else if (throwing)
			animation_set->at(BOOMERANG_BRO_ANI_THROWING_RIGHT)->Render(x, y);
		else
			animation_set->at(BOOMERANG_BRO_ANI_WALKING_RIGHT)->Render(x, y);
	}
	else if (nx < 0)
	{
		if (state == BOOMERANG_BRO_STATE_DYING)
			animation_set->at(BOOMERANG_BRO_ANI_DYING_LEFT)->Render(x, y);
		else if (throwing)
			animation_set->at(BOOMERANG_BRO_ANI_THROWING_LEFT)->Render(x, y);
		else
			animation_set->at(BOOMERANG_BRO_ANI_WALKING_LEFT)->Render(x, y);
	}
}
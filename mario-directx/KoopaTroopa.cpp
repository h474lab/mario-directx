#include "KoopaTroopa.h"
#include "Mario.h"
#include "Brick.h"
#include "ColoredBlock.h"
#include "Goomba.h"

CKoopaTroopa::CKoopaTroopa(float leftEdge, float rightEdge)
{
	this->leftEdge = leftEdge;
	this->rightEdge = rightEdge;

	background = 0;
	SetState(KOOPATROOPA_STATE_WALKING_LEFT);
	//SetState(KOOPATROOPA_STATE_LYING_DOWN);
}

void CKoopaTroopa::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case KOOPATROOPA_STATE_WALKING_LEFT:
		vx = -KOOPATROOPA_WALKING_SPEED;
		nx = -1;
		break;
	case KOOPATROOPA_STATE_WALKING_RIGHT:
		vx = KOOPATROOPA_WALKING_SPEED;
		nx = 1;
		break;
	case KOOPATROOPA_STATE_LYING_DOWN:
		vx = 0.0f;
		break;
	case KOOPATROOPA_STATE_LYING_UP:
		vx = 0.0f;
		break;
	case KOOPATROOPA_STATE_ROLLING_UP_LEFT:
		vx = -KOOPATROOPA_ROLLING_SPEED;
		nx = -1;
		break;
	case KOOPATROOPA_STATE_ROLLING_DOWN_LEFT:
		vx = -KOOPATROOPA_ROLLING_SPEED;
		nx = -1;
		break;
	case KOOPATROOPA_STATE_ROLLING_UP_RIGHT:
		vx = KOOPATROOPA_ROLLING_SPEED;
		nx = 1;
		break;
	case KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT:
		vx = KOOPATROOPA_ROLLING_SPEED;
		nx = 1;
		break;
	}
}

void CKoopaTroopa::HitKoopa(int direction)
{
	SetState(KOOPATROOPA_STATE_LYING_UP);

	if (-direction > 0)
		vx = KOOPATROOPA_DEFLECTING_X;
	else
		vx = -KOOPATROOPA_DEFLECTING_X;
	vy = -KOOPATROOPA_DEFLECTING_Y;

	StartFlying();
}

void CKoopaTroopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"\nvx, vy: %f, %f", vx, vy);

	if (isHolden)
	{
		return;
	}

	if (flying == 1)
	{
		if (GetTickCount64() - flying_start > KOOPATROOPA_FLYING_TIME || vy == 0.0f)
		{
			flying = 0;
			vx = 0.0f;
		}
	}

	vy += KOOPATROOPA_GRAVITY * dt;

	CGameObject::Update(dt, coObjects);

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
			
			if (e->ny < 0 && (dynamic_cast<CColoredBlock*>(e->obj)))
			{
				float l, t, r, b;
				e->obj->GetBoundingBox(l, t, r, b);

				leftEdge = l;
				rightEdge = r;
			}
			else if (e->nx != 0)
			{
				if (dynamic_cast<CGoomba*>(e->obj))
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

					if (state == KOOPATROOPA_STATE_ROLLING_DOWN_LEFT || state == KOOPATROOPA_STATE_ROLLING_UP_LEFT ||
						state == KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT || state == KOOPATROOPA_STATE_ROLLING_UP_RIGHT)
					{
						goomba->HitGoomba(nx);
					}
					else if (state == KOOPATROOPA_STATE_WALKING_RIGHT)
						SetState(KOOPATROOPA_STATE_WALKING_RIGHT);
					else if (state == KOOPATROOPA_STATE_WALKING_LEFT)
						SetState(KOOPATROOPA_STATE_WALKING_LEFT);
				}
				if (dynamic_cast<CMario*>(e->obj))
				{
					SetState(state);
				}
				else
				{
					if (state == KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT)
						SetState(KOOPATROOPA_STATE_ROLLING_DOWN_LEFT);
					else if (state == KOOPATROOPA_STATE_ROLLING_DOWN_LEFT)
						SetState(KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT);
					else if (state == KOOPATROOPA_STATE_ROLLING_UP_RIGHT)
						SetState(KOOPATROOPA_STATE_ROLLING_UP_LEFT);
					else if (state == KOOPATROOPA_STATE_ROLLING_UP_LEFT)
						SetState(KOOPATROOPA_STATE_ROLLING_UP_RIGHT);
				}
			}
		}

		CGameObject::Update(dt, coObjects);

		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		float width = r - l;

		if (state == KOOPATROOPA_STATE_WALKING_LEFT || state == KOOPATROOPA_STATE_WALKING_RIGHT)
		{
			if (x < leftEdge) SetState(KOOPATROOPA_STATE_WALKING_RIGHT);
			else if (x + width > rightEdge) SetState(KOOPATROOPA_STATE_WALKING_LEFT);
		}
		x += dx;
		y += dy;

		//DebugOut(L"\ndx, dy = %f, %f", dx, dy);
	}
}

void CKoopaTroopa::Render()
{
	int ani = -1;

	switch (state)
	{
	case KOOPATROOPA_STATE_WALKING_LEFT:
		ani = KOOPATROOPA_ANI_WALKING_LEFT;
		break;
	case KOOPATROOPA_STATE_WALKING_RIGHT:
		ani = KOOPATROOPA_ANI_WALKING_RIGHT;
		break;
	case KOOPATROOPA_STATE_LYING_UP:
		ani = KOOPATROOPA_ANI_LYING_UP;
		break;
	case KOOPATROOPA_STATE_LYING_DOWN:
		ani = KOOPATROOPA_ANI_LYING_DOWN;
		break;
	case KOOPATROOPA_STATE_ROLLING_UP_LEFT:
		ani = KOOPATROOPA_ANI_ROLLING_UP;
		break;
	case KOOPATROOPA_STATE_ROLLING_UP_RIGHT:
		ani = KOOPATROOPA_ANI_ROLLING_UP;
		break;
	case KOOPATROOPA_STATE_ROLLING_DOWN_LEFT:
		ani = KOOPATROOPA_ANI_ROLLING_DOWN;
		break;
	case KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT:
		ani = KOOPATROOPA_ANI_ROLLING_DOWN;
		break;
	}
	animation_set->at(ani)->Render(x, y);
}

void CKoopaTroopa::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;

	if (state == KOOPATROOPA_STATE_WALKING_LEFT || state == KOOPATROOPA_STATE_WALKING_RIGHT)
	{
		r = l + KOOPATROOPA_STANDING_WIDTH;
		b = t + KOOPATROOPA_STANDING_HEIGHT;
	}
	else if (state == KOOPATROOPA_STATE_LYING_UP || state == KOOPATROOPA_STATE_LYING_DOWN)
	{
		r = l + KOOPATROOPA_LYING_WIDTH;
		b = t + KOOPATROOPA_LYING_HEIGHT;
	}
	else
	{
		r = l + KOOPATROOPA_ROLLING_WIDTH;
		b = t + KOOPATROOPA_ROLLING_HEIGHT;
	}
}

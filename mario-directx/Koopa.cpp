#include "Koopa.h"
#include "Mario.h"
#include "Brick.h"
#include "ColoredBlock.h"
#include "Goomba.h"
#include "GroundBricks.h"
#include "Tube.h"
#include "QuestionBrick.h"
#include "SquareBrick.h"

CKoopa::CKoopa()
{
	background = 0;
	SetState(KOOPA_STATE_WALKING_LEFT);
	//SetState(KOOPA_STATE_LYING_DOWN);
}

void CKoopa::LevelDown()
{
	if (level == KOOPA_LEVEL_PARATROOPA)
	{
		SetLevel(KOOPA_LEVEL_TROOPA);
		if (nx > 0)
			SetState(KOOPA_STATE_WALKING_RIGHT);
		else
			SetState(KOOPA_STATE_WALKING_LEFT);
	}
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case KOOPA_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		nx = -1;
		break;
	case KOOPA_STATE_WALKING_RIGHT:
		vx = KOOPA_WALKING_SPEED;
		nx = 1;
		break;
	case KOOPA_STATE_LYING_DOWN:
		vx = 0.0f;
		break;
	case KOOPA_STATE_LYING_UP:
		vx = 0.0f;
		break;
	case KOOPA_STATE_ROLLING_UP_LEFT:
		vx = -KOOPA_ROLLING_SPEED;
		nx = -1;
		break;
	case KOOPA_STATE_ROLLING_DOWN_LEFT:
		vx = -KOOPA_ROLLING_SPEED;
		nx = -1;
		break;
	case KOOPA_STATE_ROLLING_UP_RIGHT:
		vx = KOOPA_ROLLING_SPEED;
		nx = 1;
		break;
	case KOOPA_STATE_ROLLING_DOWN_RIGHT:
		vx = KOOPA_ROLLING_SPEED;
		nx = 1;
		break;
	case KOOPA_STATE_JUMPING_LEFT:
		vx = -KOOPA_JUMPING_SPEED_X;
		vy = -KOOPA_JUMPING_SPEED_Y;
		nx = -1;
		break;
	case KOOPA_STATE_JUMPING_RIGHT:
		vx = KOOPA_JUMPING_SPEED_X;
		vy = -KOOPA_JUMPING_SPEED_Y;
		nx = 1;
		break;
	}
}

void CKoopa::HitKoopa(int direction)
{
	SetState(KOOPA_STATE_LYING_UP);

	if (-direction > 0)
		vx = KOOPA_DEFLECTING_X;
	else
		vx = -KOOPA_DEFLECTING_X;
	vy = -KOOPA_DEFLECTING_Y;

	StartFlying();
}

void CKoopa::KickKoopaOut(int direction)
{
	SetState(KOOPA_STATE_FLYING_OUT);

	if (-direction > 0)
		vx = KOOPA_FLYING_OUT_X;
	else
		vx = -KOOPA_FLYING_OUT_X;
	vy = -KOOPA_FLYING_OUT_Y;

	StartFlying();
}

void CKoopa::ChangeDirection()
{
	switch (state)
	{
	case KOOPA_STATE_ROLLING_DOWN_RIGHT:
		SetState(KOOPA_STATE_ROLLING_DOWN_LEFT);
		break;
	case KOOPA_STATE_ROLLING_DOWN_LEFT:
		SetState(KOOPA_STATE_ROLLING_DOWN_RIGHT);
		break;
	case KOOPA_STATE_ROLLING_UP_RIGHT:
		SetState(KOOPA_STATE_ROLLING_UP_LEFT);
		break;
	case KOOPA_STATE_ROLLING_UP_LEFT:
		SetState(KOOPA_STATE_ROLLING_UP_RIGHT);
		break;
	case KOOPA_STATE_WALKING_RIGHT:
		SetState(KOOPA_STATE_WALKING_LEFT);
		break;
	case KOOPA_STATE_WALKING_LEFT:
		SetState(KOOPA_STATE_WALKING_RIGHT);
		break;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isHolden) return;

	if (level == KOOPA_LEVEL_PARATROOPA && !jumping)
	{
		if (nx > 0)
			SetState(KOOPA_STATE_JUMPING_RIGHT);
		else
			SetState(KOOPA_STATE_JUMPING_LEFT);
	}

	if (flying == 1)
	{
		if (GetTickCount64() - flying_start > KOOPA_FLYING_TIME || vy == 0.0f)
		{
			flying = 0;
			vx = 0.0f;
		}
	}

	vy += KOOPA_GRAVITY * dt;

	CGameObject::Update(dt, coObjects);

	if (state == KOOPA_STATE_FLYING_OUT)
	{
		x += dx;
		y += dy;
		background = 1;
		return;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		jumping = 1;
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

		jumping = 1;
		for (unsigned int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (e->ny < 0) jumping = 0;

			if (e->ny < 0 && (dynamic_cast<CColoredBlock*>(e->obj) || dynamic_cast<CSquareBrick*>(e->obj)))
			{
				float l, t, r, b;
				e->obj->GetBoundingBox(l, t, r, b);

				leftEdge = l - 7;
				rightEdge = r + 7;
			}
			else if (e->nx != 0)
			{
				if (dynamic_cast<CGoomba*>(e->obj))
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

					if (state == KOOPA_STATE_ROLLING_DOWN_LEFT || state == KOOPA_STATE_ROLLING_UP_LEFT ||
						state == KOOPA_STATE_ROLLING_DOWN_RIGHT || state == KOOPA_STATE_ROLLING_UP_RIGHT)
					{
						goomba->HitGoomba(nx);
						SetState(state);
					}
					else if (state == KOOPA_STATE_WALKING_RIGHT)
						SetState(state);
					else if (state == KOOPA_STATE_WALKING_LEFT)
						SetState(state);
				}
				else if (dynamic_cast<CMario*>(e->obj))
				{
					SetState(state);
				}
				else if (dynamic_cast<CGroundBricks*>(e->obj) || dynamic_cast<CTube*>(e->obj))
				{
					ChangeDirection();
				}
				else if (dynamic_cast<CQuestionBrick*>(e->obj))
				{
					CQuestionBrick* questionbrick = dynamic_cast<CQuestionBrick*>(e->obj);
					if (state == KOOPA_STATE_ROLLING_DOWN_LEFT || state == KOOPA_STATE_ROLLING_UP_LEFT ||
						state == KOOPA_STATE_ROLLING_DOWN_RIGHT || state == KOOPA_STATE_ROLLING_UP_RIGHT)
						questionbrick->HitQuestionBrick(this->nx);
					ChangeDirection();
				}
				else if (dynamic_cast<CSquareBrick*>(e->obj))
				{
					CSquareBrick* squareBrick = dynamic_cast<CSquareBrick*>(e->obj);
					if (state == KOOPA_STATE_ROLLING_DOWN_LEFT || state == KOOPA_STATE_ROLLING_UP_LEFT ||
						state == KOOPA_STATE_ROLLING_DOWN_RIGHT || state == KOOPA_STATE_ROLLING_UP_RIGHT)
						squareBrick->Destroy();
					ChangeDirection();
				}
				else SetState(state);
			}
		}

		CGameObject::Update(dt, coObjects);

		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		float width = r - l;

		if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT)
		{
			if (x < leftEdge) SetState(KOOPA_STATE_WALKING_RIGHT);
			else if (x + width > rightEdge) SetState(KOOPA_STATE_WALKING_LEFT);
		}
		x += dx;
		y += dy;

		int dir = CanBeHitByTail();
		if (dir) HitKoopa(dir);
	}
}

void CKoopa::Render()
{
	int ani = -1;

	switch (state)
	{
	case KOOPA_STATE_WALKING_LEFT:
		ani = KOOPA_ANI_WALKING_LEFT;
		break;
	case KOOPA_STATE_WALKING_RIGHT:
		ani = KOOPA_ANI_WALKING_RIGHT;
		break;
	case KOOPA_STATE_LYING_UP:
		ani = KOOPA_ANI_LYING_UP;
		break;
	case KOOPA_STATE_LYING_DOWN:
		ani = KOOPA_ANI_LYING_DOWN;
		break;
	case KOOPA_STATE_ROLLING_UP_LEFT:
		ani = KOOPA_ANI_ROLLING_UP;
		break;
	case KOOPA_STATE_ROLLING_UP_RIGHT:
		ani = KOOPA_ANI_ROLLING_UP;
		break;
	case KOOPA_STATE_ROLLING_DOWN_LEFT:
		ani = KOOPA_ANI_ROLLING_DOWN;
		break;
	case KOOPA_STATE_ROLLING_DOWN_RIGHT:
		ani = KOOPA_ANI_ROLLING_DOWN;
		break;
	case KOOPA_STATE_JUMPING_LEFT:
		ani = KOOPA_ANI_JUMPING_LEFT;
		break;
	case KOOPA_STATE_JUMPING_RIGHT:
		ani = KOOPA_ANI_JUMPING_RIGHT;
		break;
	case KOOPA_STATE_FLYING_OUT:
		ani = KOOPA_ANI_LYING_UP;
		break;
	}
	animation_set->at(ani)->Render(x, y);
}

void CKoopa::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x + 5;
	t = y + 2;

	if (state == KOOPA_STATE_JUMPING_LEFT || state == KOOPA_STATE_JUMPING_RIGHT)
	{
		r = l + KOOPA_JUMPING_WIDTH;
		b = t + KOOPA_JUMPING_HEIGHT - 2;
	}
	else if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT)
	{
		r = l + KOOPA_STANDING_WIDTH;
		b = t + KOOPA_STANDING_HEIGHT - 2;
	}
	else if (state == KOOPA_STATE_LYING_UP || state == KOOPA_STATE_LYING_DOWN)
	{
		r = l + KOOPA_LYING_WIDTH - 5;
		b = t + KOOPA_LYING_HEIGHT - 2;
	}
	else
	{
		r = l + KOOPA_ROLLING_WIDTH - 5;
		b = t + KOOPA_ROLLING_HEIGHT - 2;
	}
}

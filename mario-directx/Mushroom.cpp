#include "Mushroom.h"
#include "SquareBrick.h"
#include "QuestionBrick.h"

CMushroom::CMushroom(int level)
{
	background = 0;
	SetLevel(level);
	SetState(MUSHROOM_STATE_IDLE);

	renderScore = RENDER_SCORE_MUSHROOM;
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

void CMushroom::Gain(CMario* player)
{
	SetState(MUSHROOM_STATE_UNAVAILABLE);
	switch (level)
	{
	case MUSHROOM_LEVEL_1UP:
		player->AddScore(MARIO_SCORE_1UP, this);
		break;
	case MUSHROOM_LEVEL_SUPER:
		player->LevelUp();
		player->AddScore(MARIO_SCORE_1000, this);
		break;
	}
}

void CMushroom::HitMushroom(int direction)
{
	if (-direction > 0)
		vx = MUSHROOM_DEFLECTING_X;
	else
		vx = -MUSHROOM_DEFLECTING_X;
	vy = -MUSHROOM_DEFLECTING_Y;
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
	if (!container) return;
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
	if (state == MUSHROOM_STATE_UNAVAILABLE && flyingDirection == FLYING_DIRECTION_NOMOVE) return;

	UpdateFlying(dt);
	if (state == MUSHROOM_STATE_UNAVAILABLE || flyingDirection != FLYING_DIRECTION_NOMOVE) return;

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

		for (unsigned int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			// Change Mushroom moving direction when collides with objects
			if ((dynamic_cast<CTube*>(e->obj) || dynamic_cast<CBrick*>(e->obj) ||
				dynamic_cast<CSquareBrick*>(e->obj)) && e->nx != 0)
			{
				if (state == MUSHROOM_STATE_MOVING_LEFT)
					SetState(MUSHROOM_STATE_MOVING_RIGHT);
				else if (state == MUSHROOM_STATE_MOVING_RIGHT)
					SetState(MUSHROOM_STATE_MOVING_LEFT);
			}
			if (CMario *mario = dynamic_cast<CMario*>(e->obj))
			{
				SetState(MUSHROOM_STATE_UNAVAILABLE);
				Gain(mario);
				return;
			}
			else if (CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj))
			{
				if (questionBrick->GetFlyingDirection() == FLYING_DIRECTION_UP)
				{
					float ql, qt, qr, qb;
					questionBrick->GetBoundingBox(ql, qt, qr, qb);

					float l, t, r, b;
					GetBoundingBox(l, t, r, b);

					HitMushroom((ql < l) ? 1 : -1);
				}
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

	// If swapAABB does not work, trigger this!!
	if (state != MUSHROOM_STATE_UNAVAILABLE)
	{
		CGame* game = CGame::GetInstance();
		if (game->CheckPlayerOverlap(this))
		{
			SetState(MUSHROOM_STATE_UNAVAILABLE);
			Gain(game->GetPlayer());
		}
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

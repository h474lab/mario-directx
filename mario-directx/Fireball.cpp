#include "Fireball.h"
#include "Utils.h"
#include "Goomba.h"
#include "TubeEnemy.h"
#include "Koopa.h"
#include "VenusFireTrap.h"
#include "ShortFireTrap.h"
#include "PiranhaPlant.h"
#include "GroundBricks.h"
#include "ColoredBlock.h"
#include "SquareBrick.h"
#include "Game.h"
#include "BoomerangBro.h"

CFireball::CFireball()
{
	background = 0;
	SetState(FIREBALL_STATE_ON_HOLD);
	renderScore = RENDER_SCORE_FIREBALL;
}

void CFireball::SetDirection(int direction)
{
	if (direction == FIREBALL_DIRECTION_LEFT)
	{
		nx = -1;
		vx = -FIREBALL_FLYING_SPEED_X;
	}
	else
	{
		nx = 1;
		vx = FIREBALL_FLYING_SPEED_X;
	}

	this->direction = direction;
}

void CFireball::SetState(int state)
{
	switch (state)
	{
	case FIREBALL_STATE_ON_HOLD:
		background = 1;
		if (this->state != FIREBALL_STATE_ON_HOLD)
		{
			destroyed_x = x;
			destroyed_y = y;
			on_hold_start = (DWORD)GetTickCount64();
		}
		break;
	case FIREBALL_STATE_FLY:
		background = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CFireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIREBALL_BBOX_WIDTH;
	bottom = y + FIREBALL_BBOX_HEIGHT;
}

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == FIREBALL_STATE_ON_HOLD) return;

	if (!CGame::GetInstance()->CheckInCameraState(this))
		SetState(FIREBALL_STATE_ON_HOLD);

	vy += FIREBALL_GRAVITY * dt;
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		vector<LPCOLLISIONEVENT> coEventsResult;
		float min_tx, min_ty;
		float nx, ny;
		float rdx, rdy;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (unsigned int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT event = coEventsResult.at(i);

			if (event->ny < 0)
			{
				if (direction == FIREBALL_DIRECTION_LEFT)
					vx = -FIREBALL_FLYING_SPEED_X;
				else
					vx = FIREBALL_FLYING_SPEED_X;

				vy = -FIREBALL_FLYING_SPEED_Y;
			}

			if (dynamic_cast<CGoomba*>(event->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(event->obj);

				if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_AND_FLY)
				{
					SetState(FIREBALL_STATE_ON_HOLD);
					goomba->HitGoomba(nx);
				}
			}
			else if (dynamic_cast<CVenusFireTrap*>(event->obj))
			{
				CVenusFireTrap* firetrap = dynamic_cast<CVenusFireTrap*>(event->obj);

				SetState(FIREBALL_STATE_ON_HOLD);
				firetrap->SetState(TUBE_ENEMY_STATE_DIE);
			}
			else if (dynamic_cast<CShortFireTrap*>(event->obj))
			{
				CShortFireTrap* firetrap = dynamic_cast<CShortFireTrap*>(event->obj);

				SetState(FIREBALL_STATE_ON_HOLD);
				firetrap->SetState(TUBE_ENEMY_STATE_DIE);
			}
			else if (dynamic_cast<CPiranhaPlant*>(event->obj))
			{
				CPiranhaPlant* firetrap = dynamic_cast<CPiranhaPlant*>(event->obj);

				SetState(FIREBALL_STATE_ON_HOLD);
				firetrap->SetState(TUBE_ENEMY_STATE_DIE);
			}
			else if (dynamic_cast<CKoopa*>(event->obj))
			{
				CKoopa* koopa = dynamic_cast<CKoopa*>(event->obj);

				SetState(FIREBALL_STATE_ON_HOLD);
				koopa->KickKoopaOut(-this->nx);
			}
			else if (!dynamic_cast<CGroundBricks*>(event->obj) &&
				!dynamic_cast<CColoredBlock*>(event->obj) &&
				!dynamic_cast<CSquareBrick*>(event->obj))
			{
				if (nx != 0)
					SetState(FIREBALL_STATE_ON_HOLD);
			}
			else if (CBoomerangBro* boomerangBro = dynamic_cast<CBoomerangBro*>(event->obj))
			{
				boomerangBro->SetState(BOOMERANG_BRO_STATE_DYING);
			}
		}

		CGameObject::Update(dt);

		x += dx;
		y += dy;
	}
}

void CFireball::Render()
{
	if (state != FIREBALL_STATE_ON_HOLD)
		animation_set->at(FIREBALL_ANI_FLYING)->Render(x, y);
	else
	{
		if ((DWORD)GetTickCount64() - on_hold_start < FIREBALL_AFTER_DESTROY_RENDER_TIME)
			animation_set->at(FIREBALL_ANI_DESTROYED)->Render(destroyed_x, destroyed_y);
	}
}

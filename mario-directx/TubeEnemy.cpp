#include "TubeEnemy.h"
#include "Mario.h"

void CTubeEnemy::Firing()
{
	this->SetState(TUBE_ENEMY_STATE_FIRE);

	bullet->SetState(BULLET_STATE_FLY);
	bullet->SetPosition(this->x + 5, this->y);

	switch (direction)
	{
	case TUBE_ENEMY_DIRECTION_BOTTOM_LEFT:
		bullet->SetDirection(BULLET_FLYING_DIRECTION_BOT_LEFT);
		break;
	case TUBE_ENEMY_DIRECTION_BOTTOM_RIGHT:
		bullet->SetDirection(BULLET_FLYING_DIRECTION_BOT_RIGHT);
		break;
	case TUBE_ENEMY_DIRECTION_TOP_LEFT:
		bullet->SetDirection(BULLET_FLYING_DIRECTION_TOP_LEFT);
		break;
	case TUBE_ENEMY_DIRECTION_TOP_RIGHT:
		bullet->SetDirection(BULLET_FLYING_DIRECTION_TOP_RIGHT);
		break;
	}
}

void CTubeEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == TUBE_ENEMY_STATE_DIE) return;

	UpdateFlying(dt);

	CGameObject::Update(dt);

	x += dx;
	y += dy;

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();

	CGameObject::CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() > 0)
	{
		float min_tx, min_ty;
		float nx, ny;
		float rdx, rdy;

		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT event = coEventsResult.at(i);

			if (dynamic_cast<CMario*>(event->obj))
			{
				CMario* mario = dynamic_cast<CMario*>(event->obj);

				if (!mario->GetUntouchable())
					mario->LevelDown();
			}
		}
	}

	if (followingObject)
	{
		float fX, fY;
		followingObject->GetPosition(fX, fY);

		if (fX > x)
		{
			if (fY > y)
				SetDirection(TUBE_ENEMY_DIRECTION_BOTTOM_RIGHT);
			else
				SetDirection(TUBE_ENEMY_DIRECTION_TOP_RIGHT);
		}
		else
		{
			if (fY > y)
				SetDirection(TUBE_ENEMY_DIRECTION_BOTTOM_LEFT);
			else
				SetDirection(TUBE_ENEMY_DIRECTION_TOP_LEFT);
		}
	}
}

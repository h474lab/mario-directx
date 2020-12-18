#include "Goomba.h"
#include "Mario.h"
#include "Background.h"
#include "Brick.h"
#include "GroundBricks.h"
CGoomba::CGoomba()
{
	background = 0;
	jumpCount = 0;
	level = GOOMBA_LEVEL_PARA_GOOMBA;
	state = GOOMBA_STATE_DIE;
	SetState(GOOMBA_STATE_WALKING_LEFT);
	renderScore = RENDER_SCORE_GOOMBA;
}

void CGoomba::ChangeDirection()
{
	switch (state)
	{
	case GOOMBA_STATE_WALKING_LEFT:
		SetState(GOOMBA_STATE_WALKING_RIGHT);
		break;
	case GOOMBA_STATE_WALKING_RIGHT:
		SetState(GOOMBA_STATE_WALKING_LEFT);
		break;
	case GOOMBA_STATE_JUMPING_LOW_LEFT:
		SetState(GOOMBA_STATE_JUMPING_LOW_RIGHT);
		break;
	case GOOMBA_STATE_JUMPING_LOW_RIGHT:
		SetState(GOOMBA_STATE_JUMPING_LOW_LEFT);
		break;
	case GOOMBA_STATE_JUMPING_HIGH_LEFT:
		SetState(GOOMBA_STATE_JUMPING_HIGH_RIGHT);
		break;
	case GOOMBA_STATE_JUMPING_HIGH_RIGHT:
		SetState(GOOMBA_STATE_JUMPING_HIGH_LEFT);
		break;
	}
}

void CGoomba::HitGoomba(float direction)
{
	if (state == GOOMBA_STATE_DIE || state == GOOMBA_STATE_DIE_AND_FLY)
		return;
	nx = (int)direction;
	SetState(GOOMBA_STATE_DIE_AND_FLY);
}

void CGoomba::LevelDown()
{
	if (level == GOOMBA_LEVEL_PARA_GOOMBA)
	{
		SetLevel(GOOMBA_LEVEL_GOOMBA);
		if (nx < 0)
			SetState(GOOMBA_STATE_WALKING_LEFT);
		else
			SetState(GOOMBA_STATE_WALKING_RIGHT);
	}
	else
	{
		SetState(GOOMBA_STATE_DIE);
	}
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	
	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;

	if (level == GOOMBA_LEVEL_GOOMBA)
	{
		right = x + GOOMBA_BBOX_WIDTH;
		bottom = y + GOOMBA_BBOX_HEIGHT;
	}
	else if (level == GOOMBA_LEVEL_PARA_GOOMBA)
	{
		right = x + PARA_GOOMBA_BBOX_WIDTH;
		bottom = y + PARA_GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == GOOMBA_STATE_DISAPPEARED) return;

	float lastVx, lastVy;
	GetSpeed(lastVx, lastVy);

	if (level == GOOMBA_LEVEL_PARA_GOOMBA)
	{
		if (state == GOOMBA_STATE_WALKING_LEFT || state == GOOMBA_STATE_WALKING_RIGHT)
		{
			float fX, fY;
			if (followingObject)
			{
				followingObject->GetPosition(fX, fY);

				if (x < fX)
					SetState(GOOMBA_STATE_WALKING_RIGHT);
				else
					SetState(GOOMBA_STATE_WALKING_LEFT);
			}
			
			if (GetTickCount64() - walking_start > GOOMBA_WALKING_TIME)
			{
				jumpCount = 0;
				if (nx < 0)
					SetState(GOOMBA_STATE_JUMPING_LOW_LEFT);
				else
					SetState(GOOMBA_STATE_JUMPING_LOW_RIGHT);
			}
		}
		else if (state == GOOMBA_STATE_JUMPING_LOW_LEFT || state == GOOMBA_STATE_JUMPING_LOW_RIGHT)
		{
			if (!jumping)
			{
				SetState(state);
				jumpCount++;
			}
			if (jumpCount == GOOMBA_MAXIMUM_LOW_JUMP)
			{
				jumpCount = 0;
				if (nx < 0)
					SetState(GOOMBA_STATE_JUMPING_HIGH_LEFT);
				else
					SetState(GOOMBA_STATE_JUMPING_HIGH_RIGHT);
			}
		}
		else if (state == GOOMBA_STATE_JUMPING_HIGH_LEFT || state == GOOMBA_STATE_JUMPING_HIGH_RIGHT)
		{
			if (!jumping)
			{
				if (nx < 0)
					SetState(GOOMBA_STATE_WALKING_LEFT);
				else
					SetState(GOOMBA_STATE_WALKING_RIGHT);
			}
		}
	}

	vy += GOOMBA_GRAVITY * dt;

	CGameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	if (state != GOOMBA_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	else return;

	if (coEvents.size() == 0 || state == GOOMBA_STATE_DIE_AND_FLY)
	{
		jumping = 1;
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		
		jumping = 1;
		int changeDirection = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult.at(i);

			if (e->ny < 0) jumping = 0;

			if (dynamic_cast<CMario*>(e->obj))
			{
				if (e->nx != 0 || e->ny < 0)
				{
					CMario* mario = dynamic_cast<CMario*>(e->obj);
					if (!mario->GetUntouchable()) mario->LevelDown();
				}
			}
			else if (dynamic_cast<CKoopa*>(e->obj))
			{
				CKoopa *koopa = dynamic_cast<CKoopa*>(e->obj);
				int koopaState = koopa->GetState();

				if (koopaState == KOOPA_STATE_ROLLING_DOWN_LEFT || koopaState == KOOPA_STATE_ROLLING_DOWN_RIGHT ||
					koopaState == KOOPA_STATE_ROLLING_UP_LEFT || koopaState == KOOPA_STATE_ROLLING_UP_RIGHT)
					HitGoomba(e->nx);
			}
			else if (dynamic_cast<CGroundBricks*>(e->obj))
			{
				float brick_x, brick_y;
				e->obj->GetPosition(brick_x, brick_y);

				if (this->y + GOOMBA_BBOX_HEIGHT > brick_y && !jumping)
					changeDirection = 1;
				else if (jumping) changeDirection = 1;
			}
			else if (e->nx != 0)
			{
				followingObject = NULL;
				changeDirection = 1;
			}
		}

		if (changeDirection)
			ChangeDirection();
		else SetState(state);

		CGameObject::Update(dt, coObjects);
		x += dx;
		y += dy;
	}

}

void CGoomba::Render()
{
	if (state == GOOMBA_STATE_DISAPPEARED) return;

	int ani = -1;
	if (level == GOOMBA_LEVEL_GOOMBA)
	{
		ani = GOOMBA_ANI_WALKING;
		if (state == GOOMBA_STATE_DIE) {
			ani = GOOMBA_ANI_DIE;
			if (GetTickCount64() - corpse_start > GOOMBA_CORPSE_STAYING_TIME)
			{
				SetState(GOOMBA_STATE_DISAPPEARED);
			}
		}
		else if (state == GOOMBA_STATE_DIE_AND_FLY) ani = GOOMBA_ANI_DIE_AND_FLY;
	}
	else if (level == GOOMBA_LEVEL_PARA_GOOMBA)
	{
		ani = GOOMBA_ANI_WALKING_WITH_WINGS;
		if (state == GOOMBA_STATE_JUMPING_LOW_LEFT || state == GOOMBA_STATE_JUMPING_LOW_RIGHT) ani = GOOMBA_ANI_JUMPING_LOW;
		else if (state == GOOMBA_STATE_JUMPING_HIGH_LEFT || state == GOOMBA_STATE_JUMPING_HIGH_RIGHT) ani = GOOMBA_ANI_JUMPING_HIGH;
		else if (state == GOOMBA_STATE_DIE_AND_FLY) ani = GOOMBA_ANI_DIE_AND_FLY;
	}

	animation_set->at(ani)->Render(x,y);

	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	int lastState = this->state;

	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_IDLE:
			vx = 0;
			break;
		case GOOMBA_STATE_DIE:
			y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			StartDying();
			background = 1;
			break;
		case GOOMBA_STATE_DIE_AND_FLY:
			if (nx > 0)
				vx = GOOMBA_DEFLECT_SPEED_X;
			else
				vx = -GOOMBA_DEFLECT_SPEED_X;
			vy = -GOOMBA_DEFLECT_SPEED_Y;
			background = 1;
			break;
		case GOOMBA_STATE_WALKING_LEFT:
			nx = -1;
			vx = -GOOMBA_WALKING_SPEED;
			if (level == GOOMBA_LEVEL_PARA_GOOMBA && lastState != GOOMBA_STATE_WALKING_LEFT && lastState != GOOMBA_STATE_WALKING_RIGHT) StartWalking();
			break;
		case GOOMBA_STATE_WALKING_RIGHT:
			nx = 1;
			vx = GOOMBA_WALKING_SPEED;
			if (level == GOOMBA_LEVEL_PARA_GOOMBA && lastState != GOOMBA_STATE_WALKING_LEFT && lastState != GOOMBA_STATE_WALKING_RIGHT) StartWalking();
			break;
		case GOOMBA_STATE_JUMPING_LOW_LEFT:
			nx = -1;
			vx = -GOOMBA_LOW_JUMP_SPEED_X;
			vy = -GOOMBA_LOW_JUMP_SPEED_Y;
			break;
		case GOOMBA_STATE_JUMPING_LOW_RIGHT:
			nx = 1;
			vx = GOOMBA_LOW_JUMP_SPEED_X;
			vy = -GOOMBA_LOW_JUMP_SPEED_Y;
			break;
		case GOOMBA_STATE_JUMPING_HIGH_LEFT:
			nx = -1;
			vx = -GOOMBA_HIGH_JUMP_SPEED_X;
			vy = -GOOMBA_HIGH_JUMP_SPEED_Y;
			break;
		case GOOMBA_STATE_JUMPING_HIGH_RIGHT:
			nx = 1;
			vx = GOOMBA_HIGH_JUMP_SPEED_X;
			vy = -GOOMBA_HIGH_JUMP_SPEED_Y;
			break;
	}
}

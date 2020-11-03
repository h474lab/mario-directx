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
	SetState(GOOMBA_STATE_WALKING_LEFT);
}

void CGoomba::HitGoomba(float direction)
{
	nx = -direction;
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
	float lastX, lastY;
	GetPosition(lastX, lastY);

	if (level == GOOMBA_LEVEL_PARA_GOOMBA)
	{
		if (state == GOOMBA_STATE_WALKING_LEFT || state == GOOMBA_STATE_WALKING_RIGHT)
		{
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
			if (jumpCount > GOOMBA_MAXIMUM_LOW_JUMP)
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

	//DebugOut(L"\nState: %d", state);

	vy += GOOMBA_GRAVITY * dt;

	CGameObject::Update(dt, coObjects);

	//DebugOut(L"\n%f %f", vx, vy);

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
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			//DebugOut(L"\nsize: %d", coEventsResult.size());

			LPCOLLISIONEVENT e = coEventsResult.at(i);

			if (e->ny < 0) jumping = 0;

			if (dynamic_cast<CMario*>(e->obj) || dynamic_cast<CGoomba*>(e->obj))
			{
				if (e->nx != 0)
				{
					SetState(state);
				}
			}
			else if (!dynamic_cast<CBrick*>(e->obj) && e->nx != 0)
			{
				if (state == GOOMBA_STATE_WALKING_LEFT)
					SetState(GOOMBA_STATE_WALKING_RIGHT);
				else if (state == GOOMBA_STATE_WALKING_RIGHT)
					SetState(GOOMBA_STATE_WALKING_LEFT);
			}
		}

		CGameObject::Update(dt, coObjects);
		x += dx;
		y += dy;
	}

}

void CGoomba::Render()
{
	if (isBackground()) return;

	int ani = -1;
	if (level == GOOMBA_LEVEL_GOOMBA)
	{
		ani = GOOMBA_ANI_WALKING;
		if (state == GOOMBA_STATE_DIE) {
			ani = GOOMBA_ANI_DIE;
			if (GetTickCount64() - corpse_start > GOOMBA_CORPSE_STAYING_TIME)
			{
				background = 1;
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
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			StartDying();
			break;
		case GOOMBA_STATE_DIE_AND_FLY:
			if (nx > 0)
				vx = GOOMBA_DEFLECT_SPEED_X;
			else
				vx = -GOOMBA_DEFLECT_SPEED_X;
			vy = -GOOMBA_DEFLECT_SPEED_Y;
			break;
		case GOOMBA_STATE_WALKING_LEFT:
			nx = -1;
			vx = -GOOMBA_WALKING_SPEED;
			if (level == GOOMBA_LEVEL_PARA_GOOMBA) StartWalking();
			break;
		case GOOMBA_STATE_WALKING_RIGHT:
			nx = 1;
			vx = GOOMBA_WALKING_SPEED;
			if (level == GOOMBA_LEVEL_PARA_GOOMBA) StartWalking();
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

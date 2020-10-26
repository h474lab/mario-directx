#include "Goomba.h"
#include "Mario.h"
#include "Background.h"
#include "Brick.h"
CGoomba::CGoomba()
{
	background = 0;
	SetState(GOOMBA_STATE_WALKING_LEFT);
}

void CGoomba::HitGoomba(float direction)
{
	nx = -direction;
	SetState(GOOMBA_STATE_DIE_AND_FLY);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else 	
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	float lastX, lastY;
	GetPosition(lastX, lastY);

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
		

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			//DebugOut(L"\nsize: %d", coEventsResult.size());

			LPCOLLISIONEVENT e = coEventsResult.at(i);

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
	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
		if (GetTickCount64() - corpse_start > GOOMBA_CORPSE_STAYING_TIME)
		{
			background = 1;
		}
	}
	else if (state == GOOMBA_STATE_DIE_AND_FLY) ani = GOOMBA_ANI_DIE_AND_FLY;

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
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_WALKING_RIGHT:
			vx = GOOMBA_WALKING_SPEED;
			break;
	}
}

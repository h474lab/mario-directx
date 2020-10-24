#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
#include "ColoredBlock.h"
#include "Coin.h"
#include "KoopaTroopa.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	turning = 0;
	kicking = 0;

	holdenKoopa = NULL;

	state = MARIO_STATE_IDLE;
	SetState(MARIO_STATE_IDLE);

	jumping = 0;
	background = 0;

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//DebugOut(L"\n%d", untouchable);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;


	float lastX = x, lastY = y;
	float lastVx = vx, lastVy = vy;

	// Calculate dx, dy 
	CGameObject::Update(dt);

	//DebugOut(L"\ndx, dy= %f %f", dx, dy);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (GetTickCount64() - kicking_start > MARIO_KICKING_TIME)
	{
		kicking = 0;
		kicking_start = 0;
	}

	if (GetTickCount64() - turning_start > MARIO_TURNING_DELAY)
	{
		turning = 0;
		turning_start = 0;
	}

	if (GetTickCount64() - spinning_start > MARIO_SPINNING_TIME)
	{
		spinning = 0;
		spinning_start = 0;
	}

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
		background = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		jumping = 1;
		x += dx; 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0; 
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 
		
		// block every object first!
		x += min_tx*dx + nx*0.4f;
		y += min_ty*dy + ny*0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//DebugOut(L"\nMario Velocity: %f %f", nx, ny);

		//
		// Collision logic with other objects
		//
		jumping = 1;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->ny < 0) jumping = 0;

			if (dynamic_cast<CCoin*>(e->obj))
			{
   				//DebugOut(L"\nCOIN GAINED");
				CCoin* coin = dynamic_cast<CCoin*>(e->obj);

				if (coin->GetState() == COIN_STATE_AVAILABLE)
					coin->SetState(COIN_STATE_UNAVAILABLE);

				x = lastX + dx;
				y = lastY + dy;

				vx = lastVx;
				vy = lastVy;
			}
			else if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				DebugOut(L"\n%d", untouchable);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_AND_FLY)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (spinning)
					{
						goomba->HitGoomba(nx);
					}
					else if (untouchable == 0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							LevelDown();
						}
					}
					/*else
					{
						x = lastX + dx;
						y = lastY + dy;

						vx = lastVx;
						vy = lastVy;
					}*/
				}
			}
			else if (dynamic_cast<CKoopaTroopa*>(e->obj))
			{
				CKoopaTroopa* koopa = dynamic_cast<CKoopaTroopa*>(e->obj);
				int koopaState = koopa->GetState();

				if (e->ny < 0)
				{
					if (koopaState == KOOPATROOPA_STATE_WALKING_LEFT || koopaState == KOOPATROOPA_STATE_WALKING_RIGHT)
						koopa->SetState(KOOPATROOPA_STATE_LYING_DOWN);
					else if (koopaState == KOOPATROOPA_STATE_ROLLING_DOWN_LEFT || koopaState == KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT)
						koopa->SetState(KOOPATROOPA_STATE_LYING_DOWN);
					// to-do: sliding to the left/right before kicking koopa to other direction
					else if (koopaState == KOOPATROOPA_STATE_LYING_DOWN)
					{
						kicking = 1;
						nx = 1;
						koopa->SetState(KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT);
						continue;
					}
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				else if (e->nx < 0)
				{
					if (spinning)
					{
						koopa->SetState(KOOPATROOPA_STATE_LYING_UP);
					}
					else if ((koopaState == KOOPATROOPA_STATE_LYING_UP || koopaState == KOOPATROOPA_STATE_LYING_DOWN) && state == MARIO_STATE_RUNNING_RIGHT)
					{
						setHoldenKoopa(koopa);
					}
					else if (koopaState == KOOPATROOPA_STATE_LYING_DOWN)
					{
						kicking = 1;
						koopa->SetState(KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT);
					}
					else if (koopaState == KOOPATROOPA_STATE_LYING_UP)
					{
						kicking = 1;
						koopa->SetState(KOOPATROOPA_STATE_ROLLING_UP_RIGHT);
					}
					else
					{
						if (!untouchable) LevelDown();
					}
				}
				else if (e->nx > 0)
				{
					if (spinning)
					{
						koopa->SetState(KOOPATROOPA_STATE_LYING_UP);
					}
					if ((koopaState == KOOPATROOPA_STATE_LYING_UP || koopaState == KOOPATROOPA_STATE_LYING_DOWN) && state == MARIO_STATE_RUNNING_LEFT)
					{
						setHoldenKoopa(koopa);
					}
					else if (koopaState == KOOPATROOPA_STATE_LYING_DOWN)
					{
						kicking = 1;
						koopa->SetState(KOOPATROOPA_STATE_ROLLING_DOWN_LEFT);
					}
					else if (koopaState == KOOPATROOPA_STATE_LYING_UP)
					{
						kicking = 1;
						koopa->SetState(KOOPATROOPA_STATE_ROLLING_UP_LEFT);
					}
					else
					{
						if (!untouchable) LevelDown();
					}
				}
			}
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
				return;
			}
		}
	}

	if (holdenKoopa != NULL)
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);

		if (nx > 0)
			holdenKoopa->SetPosition(r - 5, b - KOOPATROOPA_LYING_HEIGHT - 1);
		else
			holdenKoopa->SetPosition(l + 5 - KOOPATROOPA_LYING_WIDTH, b - KOOPATROOPA_LYING_HEIGHT - 1);
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = -1;

	if (spinning)
	{
		if (nx > 0)
			ani = MARIO_ANI_SPINNING_RIGHT;
		else
			ani = MARIO_ANI_SPINNING_LEFT;
	}
	else if (turning == 1 && !holdenKoopa)
	{
		switch (level)
		{
		case MARIO_LEVEL_FIRE:
			ani = MARIO_ANI_FIRE_TURNING_LEFT;
			break;
		case MARIO_LEVEL_TAIL:
			ani = MARIO_ANI_TAIL_TURNING_LEFT;
			break;
		case MARIO_LEVEL_BIG:
			ani = MARIO_ANI_BIG_TURNING_LEFT;
			break;
		case MARIO_LEVEL_SMALL:
			ani = MARIO_ANI_SMALL_TURNING_LEFT;
			break;
		}
	}
	else if (turning == 2 && !holdenKoopa)
	{
		switch (level)
		{
		case MARIO_LEVEL_FIRE:
			ani = MARIO_ANI_FIRE_TURNING_RIGHT;
			break;
		case MARIO_LEVEL_TAIL:
			ani = MARIO_ANI_TAIL_TURNING_RIGHT;
			break;
		case MARIO_LEVEL_BIG:
			ani = MARIO_ANI_BIG_TURNING_RIGHT;
			break;
		case MARIO_LEVEL_SMALL:
			ani = MARIO_ANI_SMALL_TURNING_RIGHT;
			break;
		}
	}
	else if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else if (level == MARIO_LEVEL_FIRE)
	{
		if (vx == 0)
		{
			if (nx > 0)
			{
				if (jumping)
					ani = MARIO_ANI_FIRE_JUMPING_RIGHT;
				else if (kicking)
					ani = MARIO_ANI_FIRE_KICKING_RIGHT;
				else if (holdenKoopa)
					ani = MARIO_ANI_FIRE_HOLD_KOOPA_IDLE_RIGHT;
				else
					ani = MARIO_ANI_FIRE_IDLE_RIGHT;
			}
			else
			{
				if (jumping)
					ani = MARIO_ANI_FIRE_JUMPING_LEFT;
				else if (kicking)
					ani = MARIO_ANI_FIRE_KICKING_LEFT;
				else if (holdenKoopa)
					ani = MARIO_ANI_FIRE_HOLD_KOOPA_IDLE_LEFT;
				else
					ani = MARIO_ANI_FIRE_IDLE_LEFT;
			}
		}
		else if (vx > 0)
		{
			if (jumping)
				ani = MARIO_ANI_FIRE_JUMPING_RIGHT;
			else if (kicking)
				ani = MARIO_ANI_FIRE_KICKING_RIGHT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_FIRE_HOLD_KOOPA_WALKING_RIGHT;
				else
					ani = MARIO_ANI_FIRE_WALKING_RIGHT;
			}
			else
			{
				if (holdenKoopa)
					ani = MARIO_ANI_FIRE_HOLD_KOOPA_RUNNING_RIGHT;
				else
					ani = MARIO_ANI_FIRE_RUNNING_RIGHT;
			}
		}
		else
		{
			if (jumping)
				ani = MARIO_ANI_FIRE_JUMPING_LEFT;
			else if (kicking)
				ani = MARIO_ANI_FIRE_KICKING_LEFT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_FIRE_HOLD_KOOPA_WALKING_LEFT;
				else
					ani = MARIO_ANI_FIRE_WALKING_LEFT;
			}
			else
			{
				if (holdenKoopa)
					ani = MARIO_ANI_FIRE_HOLD_KOOPA_RUNNING_LEFT;
				else
					ani = MARIO_ANI_FIRE_RUNNING_LEFT;
			}
		}
	}
	else if (level == MARIO_LEVEL_TAIL)
	{
		if (vx == 0)
		{
			if (nx > 0)
			{
				if (jumping)
					ani = MARIO_ANI_TAIL_JUMPING_RIGHT;
				else if (kicking)
					ani = MARIO_ANI_TAIL_KICKING_RIGHT;
				else if (holdenKoopa)
					ani = MARIO_ANI_TAIL_HOLD_KOOPA_IDLE_RIGHT;
				else
					ani = MARIO_ANI_TAIL_IDLE_RIGHT;
			}
			else
			{
				if (jumping)
					ani = MARIO_ANI_TAIL_JUMPING_LEFT;
				else if (kicking)
					ani = MARIO_ANI_TAIL_KICKING_LEFT;
				else if (holdenKoopa)
					ani = MARIO_ANI_TAIL_HOLD_KOOPA_IDLE_LEFT;
				else
					ani = MARIO_ANI_TAIL_IDLE_LEFT;
			}
		}
		else if (vx > 0)
		{
			if (jumping)
				ani = MARIO_ANI_TAIL_JUMPING_RIGHT;
			else if (kicking)
				ani = MARIO_ANI_TAIL_KICKING_RIGHT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_TAIL_HOLD_KOOPA_WALKING_RIGHT;
				else
					ani = MARIO_ANI_TAIL_WALKING_RIGHT;
			}
			else
			{
				if (holdenKoopa)
					ani = MARIO_ANI_TAIL_HOLD_KOOPA_RUNNING_RIGHT;
				else
					ani = MARIO_ANI_TAIL_RUNNING_RIGHT;
			}
		}
		else
		{
			if (jumping)
				ani = MARIO_ANI_TAIL_JUMPING_LEFT;
			else if (kicking)
				ani = MARIO_ANI_TAIL_KICKING_LEFT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_TAIL_HOLD_KOOPA_WALKING_LEFT;
				else
					ani = MARIO_ANI_TAIL_WALKING_LEFT;
			}
			else
			{
				if (holdenKoopa)
					ani = MARIO_ANI_TAIL_HOLD_KOOPA_RUNNING_LEFT;
				else
					ani = MARIO_ANI_TAIL_RUNNING_LEFT;
			}
		}
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		if (vx == 0)
		{
			if (nx > 0)
			{
				if (jumping)
					ani = MARIO_ANI_BIG_JUMPING_RIGHT;
				else if (kicking)
					ani = MARIO_ANI_BIG_KICKING_RIGHT;
				else if (holdenKoopa)
					ani = MARIO_ANI_BIG_HOLD_KOOPA_IDLE_RIGHT;
				else
					ani = MARIO_ANI_BIG_IDLE_RIGHT;
			}
			else
			{
				if (jumping)
					ani = MARIO_ANI_BIG_JUMPING_LEFT;
				else if (kicking)
					ani = MARIO_ANI_BIG_KICKING_LEFT;
				else if (holdenKoopa)
					ani = MARIO_ANI_BIG_HOLD_KOOPA_IDLE_LEFT;
				else
					ani = MARIO_ANI_BIG_IDLE_LEFT;
			}
		}
		else if (vx > 0)
		{
			if (jumping)
				ani = MARIO_ANI_BIG_JUMPING_RIGHT;
			else if (kicking)
				ani = MARIO_ANI_BIG_KICKING_RIGHT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_BIG_HOLD_KOOPA_WALKING_RIGHT;
				else
					ani = MARIO_ANI_BIG_WALKING_RIGHT;
			}
			else
			{
				if (holdenKoopa)
					ani = MARIO_ANI_BIG_HOLD_KOOPA_RUNNING_RIGHT;
				else
					ani = MARIO_ANI_BIG_RUNNING_RIGHT;
			}
		}
		else
		{
			if (jumping)
				ani = MARIO_ANI_BIG_JUMPING_LEFT;
			else if (kicking)
				ani = MARIO_ANI_BIG_KICKING_LEFT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_BIG_HOLD_KOOPA_WALKING_LEFT;
				else
					ani = MARIO_ANI_BIG_WALKING_LEFT;
			}
			else
			{
				if (holdenKoopa)
					ani = MARIO_ANI_BIG_HOLD_KOOPA_RUNNING_LEFT;
				else
					ani = MARIO_ANI_BIG_RUNNING_LEFT;
			}
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (vx == 0)
		{
			if (nx > 0)
			{
				if (jumping)
					ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
				else if (kicking)
					ani = MARIO_ANI_SMALL_KICKING_RIGHT;
				else if (holdenKoopa)
					ani = MARIO_ANI_SMALL_HOLD_KOOPA_IDLE_RIGHT;
				else
					ani = MARIO_ANI_SMALL_IDLE_RIGHT;
			}
			else
			{
				if (jumping)
					ani = MARIO_ANI_SMALL_JUMPING_LEFT;
				else if (kicking)
					ani = MARIO_ANI_SMALL_KICKING_LEFT;
				else if (holdenKoopa)
					ani = MARIO_ANI_SMALL_HOLD_KOOPA_IDLE_LEFT;
				else
					ani = MARIO_ANI_SMALL_IDLE_LEFT;
			}
		}
		else if (vx > 0)
		{
			if (jumping)
				ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
			else if (kicking)
				ani = MARIO_ANI_SMALL_KICKING_RIGHT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_SMALL_HOLD_KOOPA_WALKING_RIGHT;
				else
					ani = MARIO_ANI_SMALL_WALKING_RIGHT;
			}
			else
			{
				if (holdenKoopa)
					ani = MARIO_ANI_SMALL_HOLD_KOOPA_RUNNING_RIGHT;
				else
					ani = MARIO_ANI_SMALL_RUNNING_RIGHT;
			}
		}
		else
		{
			if (jumping)
				ani = MARIO_ANI_SMALL_JUMPING_LEFT;
			else if (kicking)
				ani = MARIO_ANI_SMALL_KICKING_LEFT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_SMALL_HOLD_KOOPA_WALKING_LEFT;
				else
					ani = MARIO_ANI_SMALL_WALKING_LEFT;
			}
			else
			{
				if (holdenKoopa)
					ani = MARIO_ANI_SMALL_HOLD_KOOPA_RUNNING_LEFT;
				else
					ani = MARIO_ANI_SMALL_RUNNING_LEFT;
			}
		}
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	//RenderBoundingBox();
}

void CMario::releaseKoopa()
{
	holdenKoopa->SetHolden(0);
	
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	holdenKoopa->SetPosition(r + 0.01f, b - KOOPATROOPA_LYING_HEIGHT);

	holdenKoopa = NULL;
}

void CMario::LevelDown()
{
	if (level == MARIO_LEVEL_TAIL)
	{
		level = MARIO_LEVEL_BIG;
		StartUntouchable();
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		level = MARIO_LEVEL_SMALL;
		StartUntouchable();
	}
	else {
		DebugOut(L"\nDIE");
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::SetState(int state)
{
	lastState = GetState();

	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		if (lastState != MARIO_STATE_WALKING_LEFT && lastState != MARIO_STATE_RUNNING_LEFT)
		{
			if (holdenKoopa) releaseKoopa();
			vx = MARIO_WALKING_SPEED;
			nx = 1;
		}
		else StartTurning(2);
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (lastState != MARIO_STATE_WALKING_RIGHT && lastState != MARIO_STATE_RUNNING_RIGHT)
		{
			if (holdenKoopa) releaseKoopa();
			vx = -MARIO_WALKING_SPEED;
			nx = -1;
		}
		else StartTurning(1);
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		if (lastState != MARIO_STATE_WALKING_LEFT && lastState != MARIO_STATE_RUNNING_LEFT)
		{
			vx = MARIO_RUNNING_SPEED;
			nx = 1;
		}
		else StartTurning(2);
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (lastState != MARIO_STATE_WALKING_RIGHT && lastState != MARIO_STATE_RUNNING_RIGHT)
		{
			vx = -MARIO_RUNNING_SPEED;
			nx = -1;
		}
		else StartTurning(1);
		break;
	case MARIO_STATE_JUMPING:
		vy = -MARIO_JUMP_SPEED_Y;
		break; 
	case MARIO_STATE_IDLE:
		if (holdenKoopa) releaseKoopa();
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		if (holdenKoopa) releaseKoopa();
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::SetLevel(int l)
{
	if (level == MARIO_LEVEL_SMALL)
	{
		SetPosition(x, y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT));
	}
	level = l;
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level == MARIO_LEVEL_FIRE)
	{
		right = x + MARIO_FIRE_BBOX_WIDTH;
		bottom = y + MARIO_FIRE_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_TAIL)
	{
		right = x + MARIO_TAIL_BBOX_WIDTH;
		bottom = y + MARIO_TAIL_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::StartSpinning()
{
	if (spinning != 1 && level == MARIO_LEVEL_TAIL)
	{
		spinning = 1;
		spinning_start = GetTickCount64();
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}


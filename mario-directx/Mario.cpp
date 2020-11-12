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
#include "Koopa.h"
#include "QuestionBrick.h"
#include "Mushroom.h"
#include "Bullet.h"
#include "TubeEnemy.h"
#include "Leaf.h"
#include "Tube.h"
#include "SquareBrick.h"

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

	running = 0;
	lastRunning = 0;

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//DebugOut(L"\n%d", untouchable);
	//DebugOut(L"\nFlying start: %llu", GetTickCount64() - flyJump_start);

	float _lastVy = vy;

	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	if (jumping) running = 0;

	if (fly == 0)
	{
		if (flyJump && _lastVy >= 0.0f)
		{
			if (!jumping) flyJump = 0;
			vy -= MARIO_FLY_JUMP_SPEED_Y * dt;
		}
	}
	else if (fly == 1)
	{
		if (flyJump)
		{
			if (!jumping)
			{
				flyJump = 0;
				fly = 0;
			}
			vy = -MARIO_FLY_SPEED_Y * dt;
		}
	}
	else
	{
		if (!jumping)
		{
			flyJump = 0;
			fly = 0;
		}
	}

	float lastX = x, lastY = y;
	float lastVx = vx, lastVy = vy;

	if (!lastRunning && running)
		StartRunning();

	DWORD runningTime = GetTickCount64() - running_start;

	if (running)
	{
		if (runningTime > MARIO_RUNNING_TIME)
		{
			if (nx > 0)
				SetState(MARIO_STATE_RUNNING_FAST_RIGHT);
			else
				SetState(MARIO_STATE_RUNNING_FAST_LEFT);
		}
		powerLevel = (int)(((float)runningTime / MARIO_RUNNING_TIME) * 6.0f);
	}

	// Calculate dx, dy 
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (throwing && GetTickCount64() - throwing_start > MARIO_THROW_TIME)
	{
		throwing = 0;
		throwing_start = 0;
		ThrowFireball();
	}

	if (GetTickCount64() - jumpingUp_start > MARIO_JUMP_UP_TIME)
	{
		jumpingUp = 0;
		jumpingUp_start = 0;
	}

	if (fly == 0)
	{
		if (GetTickCount64() - flyJump_start > MARIO_FLY_JUMP_TIME)
		{
			flyJump = 0;
			flyJump_start = 0;
		}
	}
	else if (fly == 1)
	{
		if (GetTickCount64() - flyJump_start > MARIO_FLY_TIME)
		{
			jumpingUp = 0;
			jumpingUp_start = 0;
			fly = -1;
		}
	}
	
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

	if (spinning == 1)
	{
		spinningTime = GetTickCount64();
		DWORD spinning_time = spinningTime - spinning_start;
		int body_spinning = MARIO_TAIL_SPINNING_WIDTH - MARIO_TAIL_SPINNING_LENGTH;
		int body_facing = MARIO_TAIL_FACING_SCREEN_WIDTH;

		if (spinning_time > MARIO_SPINNING_TIME)
		{
			spinning = 0;
			spinning_start = 0;
			if (nx > 0)
				x += MARIO_TAIL_SPINNING_LENGTH - MARIO_TAIL_NORMAL_LENGTH;
			//DebugOut(L"\nx = %f", x);
		}
		// phase 5
		else if (spinning_time >= MARIO_SPINNING_TIME * 4.0f / 5.0f - MARIO_SPINNING_PHASE_ERROR)
		{
			if (spinningPhase == 4)
			{
				if (nx > 0)
				{
					x -= MARIO_TAIL_SPINNING_LENGTH;
					SetTail(x, x + MARIO_TAIL_SPINNING_LENGTH);
				}
				else
				{
					x -= body_spinning - body_facing;
					SetTail(x + MARIO_TAIL_SPINNING_WIDTH - MARIO_TAIL_SPINNING_LENGTH, x + MARIO_TAIL_SPINNING_WIDTH);
				}
				spinningPhase++;
				hittableTail = 0;
			}
		}
		// phase 4
		else if (spinning_time >= MARIO_SPINNING_TIME * 3.0f / 5.0f - MARIO_SPINNING_PHASE_ERROR)
		{
			if (spinningPhase == 3)
			{
				if (nx < 0)
				{
					x += MARIO_TAIL_SPINNING_LENGTH + body_spinning - body_facing;
				}
				spinningPhase++;
				hittableTail = 0;
			}
		}
		// phase 3
		else if (spinning_time >= MARIO_SPINNING_TIME * 2.0f / 5.0f - MARIO_SPINNING_PHASE_ERROR)
		{
			if (spinningPhase == 2)
			{
				hittableTail = 1;
				if (nx < 0)
				{
					x -= (body_spinning - body_facing + MARIO_TAIL_SPINNING_LENGTH);
					SetTail(x, x + MARIO_TAIL_SPINNING_LENGTH);
				}
				else SetTail(x + MARIO_TAIL_SPINNING_WIDTH - MARIO_TAIL_SPINNING_LENGTH, x + MARIO_TAIL_SPINNING_WIDTH);
				spinningPhase++;
			}
		}
		// phase 2
		else if (spinning_time >= MARIO_SPINNING_TIME / 5.0f - MARIO_SPINNING_PHASE_ERROR)
		{
			if (spinningPhase == 1)
			{
				if (nx > 0)
				{
					x += MARIO_TAIL_SPINNING_LENGTH;
				}
				else
				{
					x += body_spinning - body_facing;
				}

				spinningPhase++;
				hittableTail = 0;
			}
		}
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

		//DebugOut(L"\nMario Velocity: %f %f", vx, vy);

		//
		// Collision logic with other objects
		//
		jumping = 1;
		int acquiredQuestionBrick = 0;
		int keepMoving = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			float obj_x, obj_y;
			e->obj->GetPosition(obj_x, obj_y);

			float obj_l, obj_t, obj_r, obj_b;
			e->obj->GetBoundingBox(obj_l, obj_t, obj_r, obj_b);
			
			float obj_w = obj_r - obj_l;
			float obj_h = obj_b - obj_t;

			int canBeHitBySpinning = (e->nx != 0 && spinning && obj_y <= y + MARIO_TAIL_HEAD_TO_TAIL &&
				obj_y + obj_h >= y + MARIO_TAIL_HEAD_TO_TAIL + MARIO_TAIL_TAIL_WIDTH) ? 1 : 0;

			if (e->ny < 0) jumping = 0;
			if (e->ny > 0)
			{
				jumpingUp = 0;
				jumpingUp_start = 0;
			}

			if (dynamic_cast<CCoin*>(e->obj))
			{
				CCoin* coin = dynamic_cast<CCoin*>(e->obj);

				if (coin->GetState() == COIN_STATE_AVAILABLE)
					coin->SetState(COIN_STATE_UNAVAILABLE);

				keepMoving = 1;
			}
			else if (dynamic_cast<CGoomba *>(e->obj))
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_AND_FLY)
					{
						goomba->LevelDown();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (canBeHitBySpinning)
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
				}
			}
			else if (dynamic_cast<CKoopa*>(e->obj))
			{
				CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
				int koopaState = koopa->GetState();

				if (e->ny < 0)
				{
					if (koopaState == KOOPA_STATE_JUMPING_LEFT || koopaState == KOOPA_STATE_JUMPING_RIGHT)
						koopa->LevelDown();
					else if (koopaState == KOOPA_STATE_WALKING_LEFT || koopaState == KOOPA_STATE_WALKING_RIGHT)
						koopa->SetState(KOOPA_STATE_LYING_DOWN);
					else if (koopaState == KOOPA_STATE_ROLLING_DOWN_LEFT || koopaState == KOOPA_STATE_ROLLING_DOWN_RIGHT)
						koopa->SetState(KOOPA_STATE_LYING_DOWN);
					else if (koopaState == KOOPA_STATE_LYING_DOWN || koopaState == KOOPA_STATE_LYING_UP)
					{
						float left, top, right, bottom;
						GetBoundingBox(left, top, right, bottom);

						keepMoving = 1;

						float koopa_x, koopa_y;
						koopa->GetPosition(koopa_x, koopa_y);

						if (koopa_x > x)
						{
							nx = 1;
							kicking = 1;
							if (koopaState == KOOPA_STATE_LYING_DOWN)
								koopa->SetState(KOOPA_STATE_ROLLING_DOWN_RIGHT);
							else
								koopa->SetState(KOOPA_STATE_ROLLING_UP_RIGHT);
						}
						else
						{
							nx = -1;
							kicking = 1;
							if (koopaState == KOOPA_STATE_LYING_DOWN)
								koopa->SetState(KOOPA_STATE_ROLLING_DOWN_LEFT);
							else
								koopa->SetState(KOOPA_STATE_ROLLING_UP_LEFT);
						}
						continue;
					}
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				else if (e->nx != 0)
				{
					if (canBeHitBySpinning)
					{
						koopa->HitKoopa(nx);
					}
					else if ((koopaState == KOOPA_STATE_LYING_UP || koopaState == KOOPA_STATE_LYING_DOWN) &&
						(state == MARIO_STATE_RUNNING_RIGHT || state == MARIO_STATE_RUNNING_LEFT ||
							state == MARIO_STATE_RUNNING_FAST_RIGHT || state == MARIO_STATE_RUNNING_FAST_LEFT))
					{
						setHoldenKoopa(koopa);
					}
					else if (koopaState == KOOPA_STATE_LYING_DOWN)
					{
						kicking = 1;
						if (e->nx < 0)
							koopa->SetState(KOOPA_STATE_ROLLING_DOWN_RIGHT);
						else
							koopa->SetState(KOOPA_STATE_ROLLING_DOWN_LEFT);
					}
					else if (koopaState == KOOPA_STATE_LYING_UP)
					{
						kicking = 1;
						if (e->nx < 0)
							koopa->SetState(KOOPA_STATE_ROLLING_UP_RIGHT);
						else
							koopa->SetState(KOOPA_STATE_ROLLING_UP_LEFT);
					}
					else
					{
						if (!untouchable) LevelDown();

						keepMoving = 1;
					}
				}
			}
			else if (dynamic_cast<CQuestionBrick*>(e->obj) && !acquiredQuestionBrick)
			{
				float l, t, b, r;
				GetBoundingBox(l, t, r, b);

				float width = r - l, height = b - t;

				CQuestionBrick* brick = dynamic_cast<CQuestionBrick*>(e->obj);
				int result = 0;
				if (e->ny > 0)
				{
					if ((x <= obj_x && x + width - obj_x >= width / 2.5f) || (x >= obj_x && obj_x + width - x >= width / 2.5f))
						brick->HitQuestionBrick((this->x > obj_x) ? 1 : -1);

					continue;
				}
				if (canBeHitBySpinning)
				{
					result = brick->HitQuestionBrick(this->nx);
				}

				if (result) acquiredQuestionBrick = 1;
			}
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
				return;
			}
			else if (dynamic_cast<CBullet*>(e->obj))
			{
				if (!untouchable)
					this->LevelDown();

				keepMoving = 1;
			}
			else if (dynamic_cast<CMushroom*>(e->obj))
			{
				CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
				mushroom->Gain(this);

				keepMoving = 1;
			}
			else if (dynamic_cast<CTubeEnemy*>(e->obj))
			{
				if (!untouchable)
					this->LevelDown();

				keepMoving = 1;
			}
			else if (dynamic_cast<CLeaf*>(e->obj))
			{
				CLeaf *leaf = dynamic_cast<CLeaf*>(e->obj);
				this->LevelUp();
				leaf->SetState(LEAF_STATE_UNAVAILABLE);

				keepMoving = 1;
			}
			else if (dynamic_cast<CTube*>(e->obj))
			{
				CTube* tube = dynamic_cast<CTube*>(e->obj);
				tube->StartDelayingObject();
			}
			else if (dynamic_cast<CSquareBrick*>(e->obj))
			{
				CSquareBrick* squareBrick = dynamic_cast<CSquareBrick*>(e->obj);
				
				if (canBeHitBySpinning || e->ny > 0)
					squareBrick->Destroy();
			}
		}

		if (keepMoving)
		{
			x = lastX + dx;
			vx = lastVx;

			if (jumping || lastVy < 0)
			{
				y = lastY + dy;
				vy = lastVy;
			}
		}
	}

	if (holdenKoopa != NULL)
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);

		if (nx > 0)
			holdenKoopa->SetPosition(r - 5, b - KOOPA_LYING_HEIGHT - 1);
		else
			holdenKoopa->SetPosition(l + 5 - KOOPA_LYING_WIDTH, b - KOOPA_LYING_HEIGHT - 1);
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
		animation_set->at(ani)->Render(x, y);
		return;
	}
	else if (sitting)
	{
		if (nx > 0)
		{
			switch (level)
			{
			case MARIO_LEVEL_FIRE:
				ani = MARIO_ANI_FIRE_SITTING_RIGHT;
				break;
			case MARIO_LEVEL_TAIL:
				ani = MARIO_ANI_TAIL_SITTING_RIGHT;
				break;
			case MARIO_LEVEL_BIG:
				ani = MARIO_ANI_BIG_SITTING_RIGHT;
				break;
			default:
				ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				break;
			}
		}
		else
		{
			switch (level)
			{
			case MARIO_LEVEL_FIRE:
				ani = MARIO_ANI_FIRE_SITTING_LEFT;
				break;
			case MARIO_LEVEL_TAIL:
				ani = MARIO_ANI_TAIL_SITTING_LEFT;
				break;
			case MARIO_LEVEL_BIG:
				ani = MARIO_ANI_BIG_SITTING_LEFT;
				break;
			default:
				ani = MARIO_ANI_SMALL_IDLE_LEFT;
				break;
			}
		}
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
		if (throwing)
		{
			if (nx > 0)
				ani = MARIO_ANI_FIRE_RIGHT;
			else
				ani = MARIO_ANI_FIRE_LEFT;
		}
		else if (vx == 0)
		{
			if (nx > 0)
			{
				if (jumping)
				{
					if (!holdenKoopa)
						ani = MARIO_ANI_FIRE_JUMPING_RIGHT;
					else
						ani = MARIO_ANI_FIRE_HOLD_KOOPA_JUMPING_RIGHT;
				}
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
				{
					if (!holdenKoopa)
						ani = MARIO_ANI_FIRE_JUMPING_LEFT;
					else
						ani = MARIO_ANI_FIRE_HOLD_KOOPA_JUMPING_LEFT;
				}
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
			{
				if (!holdenKoopa)
					ani = MARIO_ANI_FIRE_JUMPING_RIGHT;
				else
					ani = MARIO_ANI_FIRE_HOLD_KOOPA_JUMPING_RIGHT;
			}
			else if (kicking)
				ani = MARIO_ANI_FIRE_KICKING_RIGHT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_FIRE_HOLD_KOOPA_WALKING_RIGHT;
				else
					ani = MARIO_ANI_FIRE_WALKING_RIGHT;
			}
			else if (vx * nx == MARIO_RUNNING_FAST_SPEED)
			{
				ani = MARIO_ANI_FIRE_RUNNING_FASTER_RIGHT;
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
			{
				if (!holdenKoopa)
					ani = MARIO_ANI_FIRE_JUMPING_LEFT;
				else
					ani = MARIO_ANI_FIRE_HOLD_KOOPA_JUMPING_LEFT;
			}
			else if (kicking)
				ani = MARIO_ANI_FIRE_KICKING_LEFT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_FIRE_HOLD_KOOPA_WALKING_LEFT;
				else
					ani = MARIO_ANI_FIRE_WALKING_LEFT;
			}
			else if (vx * nx == MARIO_RUNNING_FAST_SPEED)
			{
				ani = MARIO_ANI_BIG_RUNNING_FASTER_LEFT;
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
				{
					if (holdenKoopa)
					{
						ani = MARIO_ANI_TAIL_HOLD_KOOPA_JUMPING_RIGHT;
					}
					else if (vy < 0)
					{
						if (fly == 1)
							ani = MARIO_ANI_TAIL_FLY_RIGHT;
						else
							ani = MARIO_ANI_TAIL_JUMPING_RIGHT;
					}
					else
					{
						if (fly != 0)
							ani = MARIO_ANI_TAIL_FLY_DROP_RIGHT;
						else if (flyJump)
							ani = MARIO_ANI_TAIL_FLY_JUMP_RIGHT;
						else
							ani = MARIO_ANI_TAIL_FLY_JUMP_DROP_RIGHT;
					}
				}
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
				{
					if (holdenKoopa)
					{
						ani = MARIO_ANI_TAIL_HOLD_KOOPA_JUMPING_LEFT;
					}
					else if (vy < 0)
					{
						if (fly == 1)
							ani = MARIO_ANI_TAIL_FLY_LEFT;
						else
							ani = MARIO_ANI_TAIL_JUMPING_LEFT;
					}
					else
					{
						if (fly != 0)
							ani = MARIO_ANI_TAIL_FLY_DROP_LEFT;
						else if (flyJump)
							ani = MARIO_ANI_TAIL_FLY_JUMP_LEFT;
						else
							ani = MARIO_ANI_TAIL_FLY_JUMP_DROP_LEFT;
					}
				}
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
			{
				if (holdenKoopa)
				{
					ani = MARIO_ANI_TAIL_HOLD_KOOPA_JUMPING_RIGHT;
				}
				else if (vy < 0)
				{
					if (fly == 1)
						ani = MARIO_ANI_TAIL_FLY_RIGHT;
					else
						ani = MARIO_ANI_TAIL_JUMPING_RIGHT;
				}
				else
				{
					if (fly != 0)
						ani = MARIO_ANI_TAIL_FLY_DROP_RIGHT;
					else if (flyJump)
						ani = MARIO_ANI_TAIL_FLY_JUMP_RIGHT;
					else
						ani = MARIO_ANI_TAIL_FLY_JUMP_DROP_RIGHT;
				}
			}
			else if (kicking)
				ani = MARIO_ANI_TAIL_KICKING_RIGHT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_TAIL_HOLD_KOOPA_WALKING_RIGHT;
				else
					ani = MARIO_ANI_TAIL_WALKING_RIGHT;
			}
			else if (vx * nx == MARIO_RUNNING_FAST_SPEED)
			{
				ani = MARIO_ANI_TAIL_RUNNING_FASTER_RIGHT;
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
			{
				if (holdenKoopa)
				{
					ani = MARIO_ANI_TAIL_HOLD_KOOPA_JUMPING_LEFT;
				}
				else if (vy < 0)
				{
					if (fly == 1)
						ani = MARIO_ANI_TAIL_FLY_LEFT;
					else
						ani = MARIO_ANI_TAIL_JUMPING_LEFT;
				}
				else
				{
					if (fly != 0)
						ani = MARIO_ANI_TAIL_FLY_DROP_LEFT;
					else if (flyJump)
						ani = MARIO_ANI_TAIL_FLY_JUMP_LEFT;
					else
						ani = MARIO_ANI_TAIL_FLY_JUMP_DROP_LEFT;
				}
			}
			else if (kicking)
				ani = MARIO_ANI_TAIL_KICKING_LEFT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_TAIL_HOLD_KOOPA_WALKING_LEFT;
				else
					ani = MARIO_ANI_TAIL_WALKING_LEFT;
			}
			else if (vx * nx == MARIO_RUNNING_FAST_SPEED)
			{
				ani = MARIO_ANI_TAIL_RUNNING_FASTER_LEFT;
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
				{
					if (!holdenKoopa)
						ani = MARIO_ANI_BIG_JUMPING_RIGHT;
					else
						ani = MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_RIGHT;
				}
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
				{
					if (!holdenKoopa)
						ani = MARIO_ANI_BIG_JUMPING_LEFT;
					else
						ani = MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_LEFT;
				}
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
			{
				if (!holdenKoopa)
					ani = MARIO_ANI_BIG_JUMPING_RIGHT;
				else
					ani = MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_RIGHT;
			}
			else if (kicking)
				ani = MARIO_ANI_BIG_KICKING_RIGHT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_BIG_HOLD_KOOPA_WALKING_RIGHT;
				else
					ani = MARIO_ANI_BIG_WALKING_RIGHT;
			}
			else if (vx * nx == MARIO_RUNNING_FAST_SPEED)
			{
				ani = MARIO_ANI_BIG_RUNNING_FASTER_RIGHT;
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
			{
				if (!holdenKoopa)
					ani = MARIO_ANI_BIG_JUMPING_LEFT;
				else
					ani = MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_LEFT;
			}
			else if (kicking)
				ani = MARIO_ANI_BIG_KICKING_LEFT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_BIG_HOLD_KOOPA_WALKING_LEFT;
				else
					ani = MARIO_ANI_BIG_WALKING_LEFT;
			}
			else if (vx * nx == MARIO_RUNNING_FAST_SPEED)
			{
				ani = MARIO_ANI_BIG_RUNNING_FASTER_LEFT;
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
				{
					if (!holdenKoopa)
						ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
					else
						ani = MARIO_ANI_SMALL_HOLD_KOOPA_JUMPING_RIGHT;
				}
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
				{
					if (!holdenKoopa)
						ani = MARIO_ANI_SMALL_JUMPING_LEFT;
					else
						ani = MARIO_ANI_SMALL_HOLD_KOOPA_JUMPING_LEFT;
				}
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
			{
				if (!holdenKoopa)
					ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
				else
					ani = MARIO_ANI_SMALL_HOLD_KOOPA_JUMPING_RIGHT;
			}
			else if (kicking)
				ani = MARIO_ANI_SMALL_KICKING_RIGHT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_SMALL_HOLD_KOOPA_WALKING_RIGHT;
				else
					ani = MARIO_ANI_SMALL_WALKING_RIGHT;
			}
			else if (vx * nx == MARIO_RUNNING_FAST_SPEED)
			{
				ani = MARIO_ANI_SMALL_RUNNING_FASTER_RIGHT;
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
			{
				if (!holdenKoopa)
					ani = MARIO_ANI_SMALL_JUMPING_LEFT;
				else
					ani = MARIO_ANI_SMALL_HOLD_KOOPA_JUMPING_LEFT;
			}
			else if (kicking)
				ani = MARIO_ANI_SMALL_KICKING_LEFT;
			else if (vx * nx == MARIO_WALKING_SPEED)
			{
				if (holdenKoopa)
					ani = MARIO_ANI_SMALL_HOLD_KOOPA_WALKING_LEFT;
				else
					ani = MARIO_ANI_SMALL_WALKING_LEFT;
			}
			else if (vx * nx == MARIO_RUNNING_FAST_SPEED)
			{
				ani = MARIO_ANI_SMALL_RUNNING_FASTER_LEFT;
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

void CMario::SetSittingState(int state)
{
	int lastSittingState = sitting;

	if (GetState() == MARIO_STATE_DIE)
	{
		sitting = 0;
		return;
	}

	if ((GetState() == MARIO_STATE_IDLE || jumping == 1) && level != MARIO_LEVEL_SMALL)
		sitting = state;
	else
		sitting = 0;

	if (!lastSittingState && sitting)
	{
		switch (level)
		{
		case MARIO_LEVEL_FIRE:
			y += MARIO_FIRE_BBOX_HEIGHT - MARIO_FIRE_SITTING_BBOX_HEIGHT;
			break;
		case MARIO_LEVEL_TAIL:
			y += MARIO_TAIL_BBOX_HEIGHT - MARIO_TAIL_SITTING_BBOX_HEIGHT;
			break;
		case MARIO_LEVEL_BIG:
			y += MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_SITTING_BBOX_HEIGHT;
			break;
		}
	}
	else if (lastSittingState && !sitting)
	{
		switch (level)
		{
		case MARIO_LEVEL_FIRE:
			y -= MARIO_FIRE_BBOX_HEIGHT - MARIO_FIRE_SITTING_BBOX_HEIGHT;
			break;
		case MARIO_LEVEL_TAIL:
			y -= MARIO_TAIL_BBOX_HEIGHT - MARIO_TAIL_SITTING_BBOX_HEIGHT;
			break;
		case MARIO_LEVEL_BIG:
			y -= MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_SITTING_BBOX_HEIGHT;
			break;
		}
	}
}

void CMario::SetJumpingUp(int jumpingUp)
{
	this->jumpingUp = jumpingUp;
	if (jumpingUp)
		jumpingUp_start = GetTickCount64();
}

void CMario::FlyJump()
{
	if (level == MARIO_LEVEL_TAIL && jumping)
	{
		flyJump_start = GetTickCount64();
		flyJump = 1;
	}
}

void CMario::SetThrowing()
{
	if (level != MARIO_LEVEL_FIRE) return;
	throwing = 1;
	throwing_start = GetTickCount64();
}

void CMario::ThrowFireball()
{
	if (level != MARIO_LEVEL_FIRE) return;
	
	currentFireball = -1;
	for (int i = 0; i < fireballs.size(); i++)
		if (fireballs[i]->GetState() == FIREBALL_STATE_ON_HOLD)
		{
			currentFireball = i;
			break;
		}

	if (currentFireball == -1) return;

	fireballs.at(currentFireball)->SetState(FIREBALL_STATE_ON_HOLD);
	if (nx > 0)
	{
		fireballs.at(currentFireball)->SetPosition(x + MARIO_FIRE_BBOX_WIDTH, y + MARIO_FIRE_BBOX_HEIGHT * 0.3f);
		fireballs.at(currentFireball)->SetDirection(FIREBALL_DIRECTION_RIGHT);
	}
	else
	{
		fireballs.at(currentFireball)->SetPosition(x - FIREBALL_BBOX_WIDTH, y + MARIO_FIRE_BBOX_HEIGHT * 0.3f);
		fireballs.at(currentFireball)->SetDirection(FIREBALL_DIRECTION_LEFT);
	}

	fireballs.at(currentFireball)->SetState(FIREBALL_STATE_FLY);
}

void CMario::releaseKoopa()
{
	holdenKoopa->SetHolden(0);
	
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	StartKicking();

	if (nx > 0)
	{
		holdenKoopa->SetPosition(r + 0.0001f, b - KOOPA_LYING_HEIGHT);
		if (holdenKoopa->GetState() == KOOPA_STATE_LYING_DOWN)
			holdenKoopa->SetState(KOOPA_STATE_ROLLING_DOWN_RIGHT);
		else
			holdenKoopa->SetState(KOOPA_STATE_ROLLING_UP_RIGHT);
	}
	else
	{
		holdenKoopa->SetPosition(l - KOOPA_LYING_WIDTH - 0.0001f, b - KOOPA_LYING_HEIGHT);
		if (holdenKoopa->GetState() == KOOPA_STATE_LYING_DOWN)
			holdenKoopa->SetState(KOOPA_STATE_ROLLING_DOWN_LEFT);
		else
			holdenKoopa->SetState(KOOPA_STATE_ROLLING_UP_LEFT);
	}

	holdenKoopa = NULL;
}

void CMario::LevelUp()
{
	if (level == MARIO_LEVEL_SMALL)
	{
		SetLevel(MARIO_LEVEL_BIG);
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		SetLevel(MARIO_LEVEL_TAIL);
	}
}

void CMario::LevelDown()
{

	if (level == MARIO_LEVEL_FIRE)
	{
		SetLevel(MARIO_LEVEL_BIG);
		StartUntouchable();
	}
	else if (level == MARIO_LEVEL_TAIL)
	{
		SetLevel(MARIO_LEVEL_BIG);
		StartUntouchable();
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		SetLevel(level = MARIO_LEVEL_SMALL);
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
	lastRunning = running;
	int last_nx = nx;

	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		if ((lastState != MARIO_STATE_WALKING_LEFT && lastState != MARIO_STATE_RUNNING_LEFT && lastState != MARIO_STATE_RUNNING_FAST_LEFT) || jumping)
		{
			running = 0;
			if (holdenKoopa) releaseKoopa();
			vx = MARIO_WALKING_SPEED;
			nx = 1;
		}
		else StartTurning(2);
		break;
	case MARIO_STATE_WALKING_LEFT:
		if ((lastState != MARIO_STATE_WALKING_RIGHT && lastState != MARIO_STATE_RUNNING_RIGHT && lastState != MARIO_STATE_RUNNING_FAST_RIGHT) || jumping)
		{
			running = 0;
			if (holdenKoopa) releaseKoopa();
			vx = -MARIO_WALKING_SPEED;
			nx = -1;
		}
		else StartTurning(1);
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		if ((lastState != MARIO_STATE_WALKING_LEFT && lastState != MARIO_STATE_RUNNING_LEFT && lastState != MARIO_STATE_RUNNING_FAST_LEFT) || jumping)
		{
			running = 1;
			vx = MARIO_RUNNING_SPEED;
			nx = 1;
		}
		else StartTurning(2);
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if ((lastState != MARIO_STATE_WALKING_RIGHT && lastState != MARIO_STATE_RUNNING_RIGHT && lastState != MARIO_STATE_RUNNING_FAST_RIGHT) || jumping)
		{
			running = 1;
			vx = -MARIO_RUNNING_SPEED;
			nx = -1;
		}
		else StartTurning(1);
		break;
	case MARIO_STATE_RUNNING_FAST_RIGHT:
		running = 1;
		vx = MARIO_RUNNING_FAST_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_FAST_LEFT:
		running = 1;
		vx = -MARIO_RUNNING_FAST_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMPING:
		running = 0;
		vy = -MARIO_JUMP_SPEED_Y;
		if ((lastState == MARIO_STATE_RUNNING_FAST_LEFT || lastState == MARIO_STATE_RUNNING_FAST_RIGHT) && !jumping)
		{
			jumping = 1;
			FlyJump();
			fly = 1;
		}
		break; 
	case MARIO_STATE_IDLE:
		running = 0;
		if (holdenKoopa) releaseKoopa();
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		running = 0;
		if (holdenKoopa) releaseKoopa();
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}

	if (jumping && vx != 0)
	{
		if (nx > 0)
			vx = MARIO_JUMP_SPEED_X;
		else
			vx = -MARIO_JUMP_SPEED_X;
	}

	if (last_nx != nx)
	{
		int leftMargin = 0, rightMargin = 0;

		GetMargins(leftMargin, rightMargin);

		if (last_nx > nx)
		{
			x = x + leftMargin - rightMargin;
		}
		else
		{
			x = x - leftMargin + rightMargin;
		}
	}
}

void CMario::SetLevel(int l)
{
	int lastLevel = level;

	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	float width = right - left, height = bottom - top;

	int leftMargin, rightMargin;
	GetMargins(leftMargin, rightMargin);

	level = l;

	int lv[] = { MARIO_LEVEL_SMALL, MARIO_LEVEL_BIG, MARIO_LEVEL_TAIL, MARIO_LEVEL_FIRE };

	int lv_height[] = { MARIO_SMALL_BBOX_HEIGHT, MARIO_BIG_BBOX_HEIGHT, MARIO_TAIL_BBOX_HEIGHT, MARIO_FIRE_BBOX_HEIGHT };
	int lv_width[] = { MARIO_SMALL_BBOX_WIDTH, MARIO_BIG_BBOX_WIDTH, MARIO_TAIL_BBOX_WIDTH, MARIO_FIRE_BBOX_WIDTH };

	int lv_sit_height[] = { MARIO_SMALL_BBOX_HEIGHT, MARIO_BIG_SITTING_BBOX_HEIGHT, MARIO_TAIL_SITTING_BBOX_HEIGHT, MARIO_FIRE_SITTING_BBOX_HEIGHT };
	int lv_sit_width[] = { MARIO_SMALL_BBOX_WIDTH, MARIO_BIG_SITTING_BBOX_WIDTH, MARIO_TAIL_SITTING_BBOX_WIDTH, MARIO_FIRE_SITTING_BBOX_WIDTH };

	int lv_width_marginLeft[] = { MARIO_SMALL_BBOX_MARGIN_LEFT, MARIO_BIG_BBOX_MARGIN_LEFT, MARIO_TAIL_BBOX_MARGIN_LEFT, MARIO_FIRE_BBOX_MARGIN_LEFT };
	int lv_width_marginRight[] = { MARIO_SMALL_BBOX_MARGIN_RIGHT, MARIO_BIG_BBOX_MARGIN_RIGHT, MARIO_TAIL_BBOX_MARGIN_RIGHT, MARIO_FIRE_BBOX_MARGIN_RIGHT };

	for (int j = 0; j < 4; j++)
	{
		if (lv[j] == level)
		{
			if (!sitting) y += height - lv_height[j];
			else y += height - lv_sit_height[j];

			if (nx > 0)
				x += (leftMargin - lv_width_marginLeft[j]);
			else
				x += (rightMargin - lv_width_marginRight[j]);
			return;
		}
	}
}

void CMario::GetMargins(int& leftMargin, int& rightMargin)
{
	switch (level)
	{
	case MARIO_LEVEL_SMALL:
		leftMargin = MARIO_SMALL_BBOX_MARGIN_LEFT;
		rightMargin = MARIO_SMALL_BBOX_MARGIN_RIGHT;
		break;
	case MARIO_LEVEL_BIG:
		leftMargin = MARIO_BIG_BBOX_MARGIN_LEFT;
		rightMargin = MARIO_BIG_BBOX_MARGIN_RIGHT;
		break;
	case MARIO_LEVEL_TAIL:
		leftMargin = MARIO_TAIL_BBOX_MARGIN_LEFT;
		rightMargin = MARIO_TAIL_BBOX_MARGIN_RIGHT;
		break;
	case MARIO_LEVEL_FIRE:
		leftMargin = MARIO_FIRE_BBOX_MARGIN_LEFT;
		rightMargin = MARIO_FIRE_BBOX_MARGIN_RIGHT;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (spinning && level == MARIO_LEVEL_TAIL)
	{
		float spinning_body = MARIO_TAIL_SPINNING_WIDTH - MARIO_TAIL_SPINNING_LENGTH;
		float body_face = MARIO_TAIL_FACING_SCREEN_WIDTH;

		if (spinningPhase == 1 || spinningPhase == 5)
		{
			if (nx > 0)
				left = x + MARIO_TAIL_SPINNING_LENGTH;
			else
				left = x;
		}
		else if (spinningPhase == 2 || spinningPhase == 4)
		{
			if (nx > 0)
				left = x;
			else
				left = x - spinning_body + body_face;
		}
		else if (spinningPhase == 3)
		{
			if (nx > 0)
				left = x;
			else
				left = x + MARIO_TAIL_SPINNING_LENGTH;
		}

		right = left + spinning_body;
		top = y;
		bottom = top + MARIO_TAIL_BBOX_HEIGHT;
		return;
	}

	left = x;
	top = y; 

	float leftMargin, rightMargin;

	if (level == MARIO_LEVEL_FIRE)
	{
		leftMargin = MARIO_FIRE_BBOX_MARGIN_LEFT;
		rightMargin = MARIO_FIRE_BBOX_MARGIN_RIGHT;

		if (nx < 0) swap(leftMargin, rightMargin);

		if (state == MARIO_STATE_IDLE)
			left = x + leftMargin;
		if (sitting)
		{
			right = x + MARIO_FIRE_SITTING_BBOX_WIDTH - rightMargin;
			bottom = y + MARIO_FIRE_SITTING_BBOX_HEIGHT;
		}
		else
		{
			right = x + MARIO_FIRE_BBOX_WIDTH - rightMargin;
			bottom = y + MARIO_FIRE_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_TAIL)
	{
		leftMargin = MARIO_TAIL_BBOX_MARGIN_LEFT;
		rightMargin = MARIO_TAIL_BBOX_MARGIN_RIGHT;

		if (nx < 0) swap(leftMargin, rightMargin);

		left = x + leftMargin;
		if (sitting)
		{
			right = x + MARIO_TAIL_SITTING_BBOX_WIDTH - rightMargin;
			bottom = y + MARIO_TAIL_SITTING_BBOX_HEIGHT;
		}
		else
		{
			right = x + MARIO_TAIL_BBOX_WIDTH - rightMargin;
			bottom = y + MARIO_TAIL_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		leftMargin = MARIO_BIG_BBOX_MARGIN_LEFT;
		rightMargin = MARIO_BIG_BBOX_MARGIN_RIGHT;

		if (nx < 0) swap(leftMargin, rightMargin);

		if (state == MARIO_STATE_IDLE)
			left = x + leftMargin;
		if (sitting)
		{
			right = x + MARIO_BIG_SITTING_BBOX_WIDTH - rightMargin;
			bottom = y + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			right = x + MARIO_BIG_BBOX_WIDTH - rightMargin;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		leftMargin = MARIO_SMALL_BBOX_MARGIN_LEFT;
		rightMargin = MARIO_SMALL_BBOX_MARGIN_RIGHT;

		if (nx < 0) swap(leftMargin, rightMargin);

		if (state == MARIO_STATE_IDLE)
			left = x + leftMargin;
		right = x + MARIO_SMALL_BBOX_WIDTH - rightMargin;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::StartSpinning()
{
	if (spinning != 1 && level == MARIO_LEVEL_TAIL && sitting != 1)
	{
		spinning = 1;
		spinning_start = GetTickCount64();

		hittableTail = 1;
		if (nx > 0)
		{
			x -= MARIO_TAIL_SPINNING_LENGTH - MARIO_TAIL_NORMAL_LENGTH;
			SetTail(x, x + MARIO_TAIL_SPINNING_LENGTH);
		}
		else SetTail(x + MARIO_TAIL_SPINNING_WIDTH - MARIO_TAIL_SPINNING_LENGTH, x + MARIO_TAIL_SPINNING_WIDTH);

		spinningPhase = 1;
	}
}

void CMario::SetTail(float start_x, float end_x)
{
	tail_start_x = start_x;
	tail_end_x = end_x;
	tail_start_y = y + MARIO_TAIL_HEAD_TO_TAIL;
	tail_end_y = tail_start_y + MARIO_TAIL_TAIL_WIDTH;
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


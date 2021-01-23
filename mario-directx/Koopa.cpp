#include "Koopa.h"
#include "Mario.h"
#include "Brick.h"
#include "ColoredBlock.h"
#include "Goomba.h"
#include "GroundBricks.h"
#include "Tube.h"
#include "QuestionBrick.h"
#include "SquareBrick.h"
#include "Beetle.h"
#include "HUD.h"
#include "PlatformSet.h"

bool CKoopa::UpdateKoopaParatroopaUpDown(DWORD dt)
{
	if (level == KOOPA_LEVEL_PARATROOPA_UP_DOWN)
	{
		// when Mario is outside moving area
		if (y <= topBound && state == KOOPA_STATE_UP)
			SetState(KOOPA_STATE_DOWN);
		else if (y >= bottomBound && state == KOOPA_STATE_DOWN)
			SetState(KOOPA_STATE_UP);
		// update Koopa position
		CGameObject::Update(dt);
		x += dx;
		y += dy;
		return true;
	}
	return false;
}

void CKoopa::CheckWakingKoopa()
{
	if (state == KOOPA_STATE_LYING_DOWN || state == KOOPA_STATE_LYING_UP)
	{
		if ((DWORD)GetTickCount64() - lying_start > KOOPA_LYING_TIME)
			WakeUp();
	}
}

bool CKoopa::CheckKoopaUpdatable()
{
	if (state == KOOPA_STATE_UNAVAILABLE) return false;
	return true;
}

void CKoopa::UpdateKoopaPosition(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isHolden)
		CGameObject::Update(dt, coObjects);
	else
	{
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
	}
}

void CKoopa::UpdateKoopaCollision(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT> coEvents)
{
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	CPlatformSet* platformSet = CPlatformSet::GetInstance();

	if (coEvents.size() == 0)
	{
		jumping = 1;
		if (!isHolden)
		{
			x += dx;
			y += dy;
		}
	}
	else
	{
		float min_tx, min_ty, nx, ny;
		float rdx, rdy;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		jumping = 1;
		int applyEdges = 0;
		for (unsigned int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			float l, t, r, b;
			e->obj->GetBoundingBox(l, t, r, b);

			float kl, kt, kr, kb;
			GetBoundingBox(kl, kt, kr, kb);

			if (e->ny < 0)
			{
				jumping = 0;

				if (dynamic_cast<CColoredBlock*>(e->obj))
				{
					if (((CColoredBlock*)e->obj)->IsEdge() == COLORED_CELL_LEFT_EDGE)
						leftEdge = l - 7;
					else if (((CColoredBlock*)e->obj)->IsEdge() == COLORED_CELL_RIGHT_EDGE)
						rightEdge = r + 7;
					applyEdges = 1;
				}
				else if (dynamic_cast<CSquareBrick*>(e->obj) || dynamic_cast<CBrick*>(e->obj) ||
					dynamic_cast<CQuestionBrick*>(e->obj))
				{
					// Koopa returns if reaching the end of bricks
					if (!platformSet->CheckAvailable(kl, t))
					{
						if (state == KOOPA_STATE_WALKING_LEFT)
							SetState(KOOPA_STATE_WALKING_RIGHT);
					}
					if (!platformSet->CheckAvailable(kr, t))
					{
						if (state == KOOPA_STATE_WALKING_RIGHT)
							SetState(KOOPA_STATE_WALKING_LEFT);
					}
					applyEdges = 0;

					if (CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj))
					{
						if (questionBrick->GetFlyingDirection() == FLYING_DIRECTION_UP)
							HitKoopa((l > kl) ? 1 : -1);
					}
				}
			}
			else if (e->nx != 0)
			{
				if (dynamic_cast<CGoomba*>(e->obj))
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

					if (state == KOOPA_STATE_ROLLING_DOWN_LEFT || state == KOOPA_STATE_ROLLING_UP_LEFT ||
						state == KOOPA_STATE_ROLLING_DOWN_RIGHT || state == KOOPA_STATE_ROLLING_UP_RIGHT ||
						isHolden)
					{
						goomba->HitGoomba(nx);
						SetState(state);
					}
					else if (state == KOOPA_STATE_WALKING_RIGHT)
						SetState(state);
					else if (state == KOOPA_STATE_WALKING_LEFT)
						SetState(state);
				}
				else if (dynamic_cast<CMario*>(e->obj) && !isHolden)
				{
					SetState(state);
				}
				else if (dynamic_cast<CGroundBricks*>(e->obj) || dynamic_cast<CHUD*>(e->obj))
				{
					if (isHolden)
					{
						KickKoopaOut((int)e->nx);
						return;
					}

					float brick_x, brick_y;
					e->obj->GetPosition(brick_x, brick_y);

					if (this->y + 10 > brick_y && !jumping)
						ChangeDirection();
					else if (jumping) ChangeDirection();
					else SetState(state);
				}
				else if (dynamic_cast<CTube*>(e->obj))
				{
					if (isHolden)
					{
						KickKoopaOut((int)e->nx);
						return;
					}

					ChangeDirection();
				}
				else if (dynamic_cast<CBrick*>(e->obj))
				{
					if (isHolden)
					{
						KickKoopaOut((int)e->nx);
						return;
					}
					
					if (this->nx != e->nx)
						ChangeDirection();
				}
				else if (dynamic_cast<CQuestionBrick*>(e->obj) && (kb > t))
				{
					if (isHolden)
					{
						KickKoopaOut((int)e->nx);
						return;
					}

					CQuestionBrick* questionbrick = dynamic_cast<CQuestionBrick*>(e->obj);
					if (state == KOOPA_STATE_ROLLING_DOWN_LEFT || state == KOOPA_STATE_ROLLING_UP_LEFT ||
						state == KOOPA_STATE_ROLLING_DOWN_RIGHT || state == KOOPA_STATE_ROLLING_UP_RIGHT)
						questionbrick->HitQuestionBrick(this->nx);
					ChangeDirection();
				}
				else if (dynamic_cast<CSquareBrick*>(e->obj) && (kb > t))
				{
					if (isHolden)
					{
						KickKoopaOut((int)e->nx);
						return;
					}

					CSquareBrick* squareBrick = dynamic_cast<CSquareBrick*>(e->obj);
					if (state == KOOPA_STATE_ROLLING_DOWN_LEFT || state == KOOPA_STATE_ROLLING_UP_LEFT ||
						state == KOOPA_STATE_ROLLING_DOWN_RIGHT || state == KOOPA_STATE_ROLLING_UP_RIGHT)
						squareBrick->Destroy();
					ChangeDirection();
				}
				else if (CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj))
				{
					if (state == KOOPA_STATE_ROLLING_DOWN_LEFT || state == KOOPA_STATE_ROLLING_UP_LEFT ||
						state == KOOPA_STATE_ROLLING_DOWN_RIGHT || state == KOOPA_STATE_ROLLING_UP_RIGHT ||
						isHolden)
						koopa->KickKoopaOut((int)nx);
				}
				else if (dynamic_cast<CBeetle*>(e->obj))
				{
					CBeetle* beetle = dynamic_cast<CBeetle*>(e->obj);
					beetle->KickBeetleOut((int)nx);
					SetState(state);
				}
				else SetState(state);
			}
		}

		if (!isHolden)
		{
			CGameObject::Update(dt);

			float l, t, r, b;
			GetBoundingBox(l, t, r, b);
			float width = r - l;

			if ((state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT) && applyEdges)
			{
				if (x < leftEdge) SetState(KOOPA_STATE_WALKING_RIGHT);
				else if (x + width > rightEdge) SetState(KOOPA_STATE_WALKING_LEFT);
			}
			x += dx;
			y += dy;

			int dir = CanBeHitByTail();
			if (dir)
			{
				SetPlayerSpinningSparkle();
				HitKoopa(dir);
			}
		}
	}
}

CKoopa::CKoopa()
{
	background = 0;
	SetState(KOOPA_STATE_WALKING_LEFT);

	renderScore = RENDER_SCORE_KOOPA;
}

void CKoopa::SetLevel(int level)
{
	this->level = level;
	if (level == KOOPA_LEVEL_PARATROOPA_UP_DOWN)
	{
		topBound = y;
		bottomBound = topBound + KOOPA_UP_DOWN_HEIGHT;
		SetState(KOOPA_STATE_DOWN);
	}
}

void CKoopa::LevelDown()
{
	if (level == KOOPA_LEVEL_PARATROOPA || level == KOOPA_LEVEL_PARATROOPA_UP_DOWN)
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
		lying_start = (DWORD)GetTickCount64();
		break;
	case KOOPA_STATE_LYING_UP:
		vx = 0.0f;
		lying_start = (DWORD)GetTickCount64();
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
	case KOOPA_STATE_DROPPING:
		vx = 0;
		break;
	case KOOPA_STATE_INTRO_JUMP_LEFT:
		vx = -KOOPA_INTRO_JUMP_SPEED_X;
		vy = -KOOPA_INTRO_JUMP_SPEED_Y;
		nx = -1;
		break;
	case KOOPA_STATE_RUNNING_RIGHT:
		vx = KOOPA_RUNNING_RIGHT_SPEED;
		nx = 1;
		break;
	case KOOPA_STATE_UP:
		vx = KOOPA_UP_DOWN_SPEED_X;
		vy = -KOOPA_UP_DOWN_SPEED_Y;
		nx = -1;
		break;
	case KOOPA_STATE_DOWN:
		vx = KOOPA_UP_DOWN_SPEED_X;
		vy = KOOPA_UP_DOWN_SPEED_Y;
		nx = -1;
		break;
	case KOOPA_STATE_FLYING_OUT:
		background = 1;
		break;
	}
}

void CKoopa::WakeUp()
{
	y -= KOOPA_STANDING_HEIGHT - KOOPA_LYING_HEIGHT;
	SetState(KOOPA_STATE_WALKING_LEFT);
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
	if (UpdateKoopaParatroopaUpDown(dt)) return;
	CheckWakingKoopa();

	if (!CheckKoopaUpdatable()) return;

	UpdateKoopaPosition(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	UpdateKoopaCollision(dt, coObjects, coEvents);
}

void CKoopa::Render()
{
	if (state == KOOPA_STATE_UNAVAILABLE) return;
	if (level == KOOPA_LEVEL_PARATROOPA_UP_DOWN)
	{
		animation_set->at(KOOPA_ANI_JUMPING_LEFT)->Render(x, y);
		return;
	}

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
	case KOOPA_STATE_DROPPING:
		ani = KOOPA_ANI_LYING_DOWN;
		break;
	case KOOPA_STATE_INTRO_JUMP_LEFT:
		ani = KOOPA_ANI_ROLLING_DOWN;
		break;
	case KOOPA_STATE_RUNNING_RIGHT:
		ani = KOOPA_ANI_RUNNING_RIGHT;
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
	else if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT || state == KOOPA_STATE_RUNNING_RIGHT)
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

#include "FloatingBlock.h"
#include "Camera.h"
#include "Game.h"

CFloatingBlock::CFloatingBlock()
{
	background = 0;
	renderScore = RENDER_SCORE_FLOATING_BLOCK;
}

void CFloatingBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + FLOAT_BLOCK_BBOX_WIDTH;
	bottom = top + FLOAT_BLOCK_BBOX_HEIGHT;
}

void CFloatingBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == FLOATING_BLOCK_STATE_IDLE)
	{
		CCamera* camera = CCamera::GetInstance();
		CGame* game = CGame::GetInstance();
		// get camera position
		float cx, cy;
		camera->GetPosition(cx, cy);
		// get screen width
		float sWidth = (float)game->GetScreenWidth();

		if (x > cx + sWidth)
			return;	// if the floating block is outside the camera -> stay idle
		else
			SetState(FLOATING_BLOCK_STATE_FLOAT);	// start setting floating state (start moving)
	}
	if (state == FLOATING_BLOCK_STATE_FLOAT)
	{
		vx = FLOAT_BLOCK_FLOATING_SPEED_X;
		vy = FLOAT_BLOCK_FLOATING_SPEED_Y;

		// Float block pushes player
		CGame* game = CGame::GetInstance();
		if (game->CheckPlayerOverlap(this))
		{
			CMario* mario = game->GetPlayer();

			if (mario->GetFloor() != this)
			{
				float l, t, r, b;
				GetBoundingBox(l, t, r, b);

				float ml, mt, mr, mb;
				mario->GetBoundingBox(ml, mt, mr, mb);

				float mx, my;
				mario->GetPosition(mx, my);

				mario->SetPosition(l - (mr - mx), my);
			}
		}
	}
	else if (state == FLOATING_BLOCK_STATE_DROP)
	{
		vx = FLOAT_BLOCK_DROPPING_SPEED_X;
		vy = FLOAT_BLOCK_DROPPING_SPEED_Y;
	}

	// update floating block position
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void CFloatingBlock::Render()
{
	animation_set->at(FLOATING_BLOCK_ANI_LEFT)->Render(x + FLOAT_BLOCK_LEFT_X, y);
	animation_set->at(FLOATING_BLOCK_ANI_MID)->Render(x + FLOAT_BLOCK_MID_X, y);
	animation_set->at(FLOATING_BLOCK_ANI_RIGHT)->Render(x + FLOAT_BLOCK_RIGHT_X, y);
}

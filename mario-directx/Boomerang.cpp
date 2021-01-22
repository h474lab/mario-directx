#include "Boomerang.h"
#include "Game.h"

CBoomerang::CBoomerang()
{
	background = 0;
	limitY = 0;
	direction = BOOMERANG_DIRECTION_RIGHT;
	renderScore = RENDER_SCORE_BOOMERANG;
	state = BOOMERANG_STATE_HIDE;
}

void CBoomerang::Throw(int dir)
{
	if (state != BOOMERANG_STATE_IDLE) return;
	direction = dir;
	SetState(BOOMERANG_STATE_FLY);
}

void CBoomerang::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	SetState(BOOMERANG_STATE_IDLE);
}

void CBoomerang::SetState(int state)
{
	switch (state)
	{
	case BOOMERANG_STATE_HIDE:
		background = 1;
		break;
	case BOOMERANG_STATE_IDLE:
		background = 0;
		vx = BOOMERANG_IDLE_SPEED_X;
		vy = BOOMERANG_IDLE_SPEED_Y;
		break;
	case BOOMERANG_STATE_FLY:
		background = 0;
		if (direction == BOOMERANG_DIRECTION_RIGHT)
		{
			vx = BOOMERANG_FLY_SPEED_X;
			vy = -BOOMERANG_FLY_SPEED_Y;
		}
		else
		{
			vx = -BOOMERANG_FLY_SPEED_X;
			vy = -BOOMERANG_FLY_SPEED_Y;
		}
		limitY = this->y + BOOMERANG_FLY_LIMIT_Y;	// set limit to let Boomerang know its maximum y value
		break;
	}
	this->state = state;
}

void CBoomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BOOMERANG_STATE_HIDE) return;

	left = x;
	top = y;
	right = x + BOOMERANG_BBOX_WIDTH;
	bottom = y + BOOMERANG_BBOX_HEIGHT;
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// no updating Boomerang when it's idling or hiding
	if (state == BOOMERANG_STATE_HIDE || state == BOOMERANG_STATE_IDLE) return;

	// Hide Boomerang if it's out of screen
	if (!CGame::GetInstance()->CheckInCameraState(this))
		SetState(BOOMERANG_STATE_HIDE);
	
	// update Boomerang movement (x axis)
	if (direction == BOOMERANG_DIRECTION_RIGHT)
		vx -= BOOMERANG_FLY_SPEED_DOWN_X;
	else
		vx += BOOMERANG_FLY_SPEED_DOWN_X;
	
	// update Boomerang movement (y axis)
	if (y >= limitY)
		y = limitY;	// put Boomerang back to its limit (y)
	else
		vy += BOOMERANG_FLY_SPEED_DOWN_Y;	// change Boomerang flying speed to reach its limit

	// update Boomerang position
	CGameObject::Update(dt);
	x += dx;
	y += dy;

	CGame* game = CGame::GetInstance();
	if (game->CheckPlayerOverlap(this))
	{
		CMario* mario = game->GetPlayer();
		if (!mario->GetUntouchable())
			mario->LevelDown();
	}
}

void CBoomerang::Render()
{
	if (state == BOOMERANG_STATE_HIDE) return;

	int ani = -1;
	if (state == BOOMERANG_STATE_IDLE)
	{
		if (direction == BOOMERANG_DIRECTION_RIGHT)
			ani = BOOMERANG_ANI_IDLE_RIGHT;
		else
			ani = BOOMERANG_ANI_IDLE_LEFT;
	}
	else if (state == BOOMERANG_STATE_FLY)
	{
		if (vx > 0)
			ani = BOOMERANG_ANI_CLOCKWISE_ROTATION;
		else
			ani = BOOMERANG_ANI_COUNTERCLOCKWISE_ROTATION;
	}
	animation_set->at(ani)->Render(x, y);
}

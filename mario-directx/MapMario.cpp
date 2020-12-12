#include "MapMario.h"
#include "Game.h"

CMapMario::CMapMario()
{
	level = MARIO_LEVEL_SMALL;
	state = MAP_MARIO_STATE_IDLING;
}

void CMapMario::SetDestination(float x, float y)
{
	destination_x = x;
	destination_y = y;

	if (this->x < destination_x) movingDirection = MAP_MARIO_MOVING_DIRECTION_RIGHT;
	else if (this->x > destination_x) movingDirection = MAP_MARIO_MOVING_DIRECTION_LEFT;
	else if (this->y < destination_y) movingDirection = MAP_MARIO_MOVING_DIRECTION_DOWN;
	else movingDirection = MAP_MARIO_MOVING_DIRECTION_UP;
}

void CMapMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetLevel(CGame::GetInstance()->GetPlayer()->GetLevel());
	if (state == MAP_MARIO_STATE_IDLING) return;

	switch (movingDirection)
	{
	case MAP_MARIO_MOVING_DIRECTION_UP:
		if (this->y > destination_y)
			y -= MAP_MARIO_MOVING_SPEED_Y * dt;
		else
		{
			y = destination_y;
			SetState(MAP_MARIO_STATE_IDLING);
		}
		break;
	case MAP_MARIO_MOVING_DIRECTION_DOWN:
		if (this->y < destination_y)
			y += MAP_MARIO_MOVING_SPEED_Y * dt;
		else
		{
			y = destination_y;
			SetState(MAP_MARIO_STATE_IDLING);
		}
		break;
	case MAP_MARIO_MOVING_DIRECTION_LEFT:
		if (this->x > destination_x)
			x -= MAP_MARIO_MOVING_SPEED_X * dt;
		else
		{
			x = destination_x;
			SetState(MAP_MARIO_STATE_IDLING);
		}
		break;
	case MAP_MARIO_MOVING_DIRECTION_RIGHT:
		if (this->x < destination_x)
			x += MAP_MARIO_MOVING_SPEED_X * dt;
		else
		{
			x = destination_x;
			SetState(MAP_MARIO_STATE_IDLING);
		}
		break;
	}
}

void CMapMario::Render()
{
	int ani = -1;
	switch (level)
	{
	case MARIO_LEVEL_SMALL:
		ani = MAP_MARIO_ANI_SMALL_MARIO;
		break;
	case MARIO_LEVEL_BIG:
		ani = MAP_MARIO_ANI_BIG_MARIO;
		break;
	case MARIO_LEVEL_FIRE:
		ani = MAP_MARIO_ANI_FIRE_MARIO;
		break;
	case MARIO_LEVEL_TAIL:
		ani = MAP_MARIO_ANI_TAIL_MARIO;
		break;
	}
	
	if (ani != -1) animation_set->at(ani)->Render(x, y);
}

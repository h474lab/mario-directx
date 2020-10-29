#include "FireTrap.h"

void CFireTrap::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	state = TUBE_ENEMY_STATE_POINT;
}

void CFireTrap::Render()
{
	if (state == TUBE_ENEMY_STATE_DIE) return;

	int ani = -1;

	if (state == TUBE_ENEMY_STATE_POINT)
	{
		switch (direction)
		{
		case TUBE_ENEMY_DIRECTION_BOTTOM_LEFT:
			ani = FIRE_TRAP_ANI_POINT_BOTTOM_LEFT;
			break;
		case TUBE_ENEMY_DIRECTION_BOTTOM_RIGHT:
			ani = FIRE_TRAP_ANI_POINT_BOTTOM_RIGHT;
			break;
		case TUBE_ENEMY_DIRECTION_TOP_LEFT:
			ani = FIRE_TRAP_ANI_POINT_TOP_LEFT;
			break;
		case TUBE_ENEMY_DIRECTION_TOP_RIGHT:
			ani = FIRE_TRAP_ANI_POINT_TOP_RIGHT;
			break;
		}
	}
	else if (state == TUBE_ENEMY_STATE_FIRE)
	{
		switch (direction)
		{
		case TUBE_ENEMY_DIRECTION_BOTTOM_LEFT:
			ani = FIRE_TRAP_ANI_FIRE_BOTTOM_LEFT;
			break;
		case TUBE_ENEMY_DIRECTION_BOTTOM_RIGHT:
			ani = FIRE_TRAP_ANI_FIRE_BOTTOM_RIGHT;
			break;
		case TUBE_ENEMY_DIRECTION_TOP_LEFT:
			ani = FIRE_TRAP_ANI_FIRE_TOP_LEFT;
			break;
		case TUBE_ENEMY_DIRECTION_TOP_RIGHT:
			ani = FIRE_TRAP_ANI_FIRE_TOP_RIGHT;
			break;
		}
	}

	animation_set->at(ani)->Render(x, y);
}

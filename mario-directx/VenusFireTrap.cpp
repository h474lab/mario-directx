#include "VenusFireTrap.h"
#include "Utils.h"

void CVenusFireTrap::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	minFlyingY = y - FIRE_TRAP_BBOX_HEIGHT;
	maxFlyingY = y + 1;
	flyingSpeedY = FIRE_TRAP_FLYING_SPEED_Y;
	delayAfterMovingUp = 1;
	delay_time = FIRE_TRAP_DELAY_FLYING_TIME;

	state = FIRE_TRAP_STATE_POINT;
}

void CVenusFireTrap::Firing()
{
	this->SetState(FIRE_TRAP_STATE_FIRE);

	bullet->SetState(BULLET_STATE_FLY);
	bullet->SetPosition(this->x + 5, this->y);

	switch (direction)
	{
	case FIRE_TRAP_DIRECTION_BOTTOM_LEFT:
		bullet->SetDirection(BULLET_FLYING_DIRECTION_BOT_LEFT);
		break;
	case FIRE_TRAP_DIRECTION_BOTTOM_RIGHT:
		bullet->SetDirection(BULLET_FLYING_DIRECTION_BOT_RIGHT);
		break;
	case FIRE_TRAP_DIRECTION_TOP_LEFT:
		bullet->SetDirection(BULLET_FLYING_DIRECTION_TOP_LEFT);
		break;
	case FIRE_TRAP_DIRECTION_TOP_RIGHT:
		bullet->SetDirection(BULLET_FLYING_DIRECTION_TOP_RIGHT);
		break;
	}
}

void CVenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIRE_TRAP_BBOX_WIDTH;
	bottom = y + FIRE_TRAP_BBOX_HEIGHT;
}

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	UpdateFlying(dt);

	CGameObject::Update(dt);

	x += dx;
	y += dy;

	if (followingObject)
	{
		float fX, fY;
		followingObject->GetPosition(fX, fY);

		if (fX > x)
		{
			if (fY > y)
				SetDirection(FIRE_TRAP_DIRECTION_BOTTOM_RIGHT);
			else
				SetDirection(FIRE_TRAP_DIRECTION_TOP_RIGHT);
		}
		else
		{
			if (fY > y)
				SetDirection(FIRE_TRAP_DIRECTION_BOTTOM_LEFT);
			else
				SetDirection(FIRE_TRAP_DIRECTION_TOP_LEFT);
		}
	}
}

void CVenusFireTrap::Render()
{
	int ani = -1;

	if (state == FIRE_TRAP_STATE_POINT)
	{
		switch (direction)
		{
		case FIRE_TRAP_DIRECTION_BOTTOM_LEFT:
			ani = FIRE_TRAP_ANI_POINT_BOTTOM_LEFT;
			break;
		case FIRE_TRAP_DIRECTION_BOTTOM_RIGHT:
			ani = FIRE_TRAP_ANI_POINT_BOTTOM_RIGHT;
			break;
		case FIRE_TRAP_DIRECTION_TOP_LEFT:
			ani = FIRE_TRAP_ANI_POINT_TOP_LEFT;
			break;
		case FIRE_TRAP_DIRECTION_TOP_RIGHT:
			ani = FIRE_TRAP_ANI_POINT_TOP_RIGHT;
			break;
		}
	}
	else if (state == FIRE_TRAP_STATE_FIRE)
	{
		switch (direction)
		{
		case FIRE_TRAP_DIRECTION_BOTTOM_LEFT:
			ani = FIRE_TRAP_ANI_FIRE_BOTTOM_LEFT;
			break;
		case FIRE_TRAP_DIRECTION_BOTTOM_RIGHT:
			ani = FIRE_TRAP_ANI_FIRE_BOTTOM_RIGHT;
			break;
		case FIRE_TRAP_DIRECTION_TOP_LEFT:
			ani = FIRE_TRAP_ANI_FIRE_TOP_LEFT;
			break;
		case FIRE_TRAP_DIRECTION_TOP_RIGHT:
			ani = FIRE_TRAP_ANI_FIRE_TOP_RIGHT;
			break;
		}
	}

	animation_set->at(ani)->Render(x, y);
}

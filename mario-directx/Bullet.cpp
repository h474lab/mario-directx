#include "Bullet.h"

void CBullet::SetDirection(int direction)
{
	switch (direction)
	{
	case BULLET_FLYING_DIRECTION_BOT_LEFT:
		vx = -BULLET_FLYING_SPEED_X;
		vy = BULLET_FLYING_SPEED_Y;
		break;
	case BULLET_FLYING_DIRECTION_MID_BOT_LEFT:
		vx = -BULLET_FLYING_MID_SPEED_X;
		vy = BULLET_FLYING_MID_SPEED_Y;
		break;
	case BULLET_FLYING_DIRECTION_BOT_RIGHT:
		vx = BULLET_FLYING_SPEED_X;
		vy = BULLET_FLYING_SPEED_Y;
		break;
	case BULLET_FLYING_DIRECTION_MID_BOT_RIGHT:
		vx = BULLET_FLYING_MID_SPEED_X;
		vy = BULLET_FLYING_MID_SPEED_Y;
		break;
	case BULLET_FLYING_DIRECTION_TOP_LEFT:
		vx = -BULLET_FLYING_SPEED_X;
		vy = -BULLET_FLYING_SPEED_Y;
		break;
	case BULLET_FLYING_DIRECTION_MID_TOP_LEFT:
		vx = -BULLET_FLYING_MID_SPEED_X;
		vy = -BULLET_FLYING_MID_SPEED_Y;
	case BULLET_FLYING_DIRECTION_TOP_RIGHT:
		vx = BULLET_FLYING_SPEED_X;
		vy = -BULLET_FLYING_SPEED_Y;
		break;
	case BULLET_FLYING_DIRECTION_MID_TOP_RIGHT:
		vx = BULLET_FLYING_MID_SPEED_X;
		vy = -BULLET_FLYING_MID_SPEED_Y;
		break;
	}

	this->direction = direction;
}

float CBullet::GetDistance(int direction, float xM, float yM)
{
	float a, b, c;
	switch (direction)
	{
	case BULLET_FLYING_DIRECTION_BOT_LEFT:
		a = -BULLET_FLYING_SPEED_Y;
		b = -BULLET_FLYING_SPEED_X;
		break;
	case BULLET_FLYING_DIRECTION_MID_BOT_LEFT:
		a = -BULLET_FLYING_MID_SPEED_Y;
		b = -BULLET_FLYING_MID_SPEED_X;
		break;
	case BULLET_FLYING_DIRECTION_BOT_RIGHT:
		a = -BULLET_FLYING_SPEED_Y;
		b = BULLET_FLYING_SPEED_X;
		break;
	case BULLET_FLYING_DIRECTION_MID_BOT_RIGHT:
		a = -BULLET_FLYING_MID_SPEED_Y;
		b = BULLET_FLYING_MID_SPEED_X;
		break;
	case BULLET_FLYING_DIRECTION_TOP_LEFT:
		a = BULLET_FLYING_SPEED_Y;
		b = -BULLET_FLYING_SPEED_X;
		break;
	case BULLET_FLYING_DIRECTION_MID_TOP_LEFT:
		a = BULLET_FLYING_MID_SPEED_Y;
		b = -BULLET_FLYING_MID_SPEED_X;
	case BULLET_FLYING_DIRECTION_TOP_RIGHT:
		a = BULLET_FLYING_SPEED_Y;
		b = BULLET_FLYING_SPEED_X;
		break;
	case BULLET_FLYING_DIRECTION_MID_TOP_RIGHT:
		a = BULLET_FLYING_MID_SPEED_Y;
		b = BULLET_FLYING_MID_SPEED_X;
		break;
	}

	c = - x * a - y * b;

	return abs(a * xM + b * yM + c) / sqrt(a * a + b * b);
}

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BULLET_STATE_ON_HOLD) return;

	CGameObject::Update(dt);

	x += dx;
	y += dy;
}

void CBullet::Render()
{
	if (state == BULLET_STATE_FLY)
		animation_set->at(0)->Render(x, y);
}

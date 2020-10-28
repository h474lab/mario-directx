#include "Bullet.h"

void CBullet::SetDirection(int direction)
{
	switch (direction)
	{
	case BULLET_FLYING_DIRECTION_BOT_LEFT:
		vx = -BULLET_FLYING_SPEED_X;
		vy = BULLET_FLYING_SPEED_Y;
		break;
	case BULLET_FLYING_DIRECTION_BOT_RIGHT:
		vx = BULLET_FLYING_SPEED_X;
		vy = BULLET_FLYING_SPEED_Y;
		break;
	case BULLET_FLYING_DIRECTION_TOP_LEFT:
		vx = -BULLET_FLYING_SPEED_X;
		vy = -BULLET_FLYING_SPEED_Y;
		break;
	case BULLET_FLYING_DIRECTION_TOP_RIGHT:
		vx = BULLET_FLYING_SPEED_X;
		vy = -BULLET_FLYING_SPEED_Y;
		break;
	}

	this->direction = direction;
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

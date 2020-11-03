#include "Leaf.h"
#include "Utils.h"

CLeaf::CLeaf()
{
	background = 0;
}

void CLeaf::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	leftEdge = x;
	rightEdge = x + EDGES_DISTANCE_X;

	minFlyingY = y - LEAF_FLYING_Y;
	maxFlyingY = y + 1;
	flyingSpeedY = LEAF_FLYING_SPEED_Y;
	delayAfterMovingUp = 0;
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case LEAF_STATE_DROP_LEFT:
		background = 0;
		vx = -LEAF_DROPPING_SPEED_X;
		break;
	case LEAF_STATE_DROP_RIGHT:
		background = 0;
		vx = LEAF_DROPPING_SPEED_X;
		break;
	case LEAF_STATE_UNAVAILABLE:
		background = 1;
		break;
	}
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + LEAF_BBOX_WIDTH;
	bottom = top + LEAF_BBOX_HEIGHT;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"\nVelocity: %f, %f", vx, vy);

	if (flyingDirection == FLYING_DIRECTION_UP)
	{
		UpdateFlying(dt);
		return;
	}

	if (state == LEAF_STATE_UNAVAILABLE) return;

	if (state == LEAF_STATE_DROP_RIGHT && x + LEAF_BBOX_WIDTH > rightEdge)
		SetState(LEAF_STATE_DROP_LEFT);
	else if (state == LEAF_STATE_DROP_LEFT && x < leftEdge)
		SetState(LEAF_STATE_DROP_RIGHT);

	vy = LEAF_GRAVITY;

	CGameObject::Update(dt);

	x += dx;
	y += dy;
}

void CLeaf::Render()
{
	if (state == LEAF_STATE_UNAVAILABLE) return;
	
	if (state == LEAF_STATE_DROP_LEFT)
		animation_set->at(LEAF_ANI_LEFT)->Render(x, y);
	else if (state == LEAF_STATE_DROP_RIGHT)
		animation_set->at(LEAF_ANI_RIGHT)->Render(x, y);
}

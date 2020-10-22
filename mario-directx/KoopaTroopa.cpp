#include "KoopaTroopa.h"
#include "Mario.h"
#include "Brick.h"
#include "ColoredBlock.h"

CKoopaTroopa::CKoopaTroopa(float leftEdge, float rightEdge)
{
	this->leftEdge = leftEdge;
	this->rightEdge = rightEdge;

	background = 0;
	SetState(KOOPATROOPA_STATE_WALKING_LEFT);
}

void CKoopaTroopa::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case KOOPATROOPA_STATE_WALKING_LEFT:
		vx = -KOOPATROOPA_WALKING_SPEED;
		nx = -1;
		break;
	case KOOPATROOPA_STATE_WALKING_RIGHT:
		vx = KOOPATROOPA_WALKING_SPEED;
		nx = 1;
		break;
	case KOOPATROOPA_STATE_LYING_DOWN | KOOPATROOPA_STATE_LYING_UP:
		vx = 0.0f;
		break;
	case KOOPATROOPA_STATE_ROLLING_UP_LEFT | KOOPATROOPA_STATE_ROLLING_DOWN_LEFT:
		vx = -KOOPATROOPA_ROLLING_SPEED;
		nx = -1;
		break;
	case KOOPATROOPA_STATE_ROLLING_UP_RIGHT | KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT:
		vx = KOOPATROOPA_ROLLING_SPEED;
		nx = 1;
		break;
	}
}

void CKoopaTroopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isPausing) {
		if (GetTickCount64() - pausingTime > KOOPATROOPA_PAUSING_TIME)
			isPausing = 0;
		else
			return;
	}

	float lastX, lastY;
	GetPosition(lastX, lastY);

	vy += KOOPATROOPA_GRAVITY * dt;

	CGameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny;
		float rdx, rdy;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			

			if (e->ny < 0 && (dynamic_cast<CBrick*>(e->obj) || dynamic_cast<CColoredBlock*>(e->obj)))
			{
				float l, t, r, b;
				e->obj->GetBoundingBox(l, t, r, b);

				leftEdge = l;
				rightEdge = r;
			}
		}

		CGameObject::Update(dt, coObjects);

		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		float width = r - l;

		if (x < leftEdge) SetState(KOOPATROOPA_STATE_WALKING_RIGHT);
		else if (x + width > rightEdge) SetState(KOOPATROOPA_STATE_WALKING_LEFT);
		x += dx;
		y += dy;
	}
}

void CKoopaTroopa::Render()
{
	int ani = -1;
	switch (state)
	{
	case KOOPATROOPA_STATE_WALKING_LEFT:
		ani = KOOPATROOPA_ANI_WALKING_LEFT;
		break;
	case KOOPATROOPA_STATE_WALKING_RIGHT:
		ani = KOOPATROOPA_ANI_WALKING_RIGHT;
		break;
	case KOOPATROOPA_STATE_LYING_UP:
		ani = KOOPATROOPA_ANI_LYING_UP;
		break;
	case KOOPATROOPA_STATE_LYING_DOWN:
		ani = KOOPATROOPA_ANI_LYING_DOWN;
		break;
	case KOOPATROOPA_STATE_ROLLING_UP_LEFT | KOOPATROOPA_STATE_ROLLING_UP_RIGHT:
		ani = KOOPATROOPA_ANI_ROLLING_UP;
		break;
	case KOOPATROOPA_STATE_ROLLING_DOWN_LEFT | KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT:
		ani = KOOPATROOPA_ANI_ROLLING_DOWN;
		break;
	}
	animation_set->at(ani)->Render(x, y);
}

void CKoopaTroopa::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;

	if (state == KOOPATROOPA_STATE_WALKING_LEFT || state == KOOPATROOPA_STATE_WALKING_RIGHT)
	{
		r = l + KOOPATROOPA_STANDING_WIDTH;
		b = t + KOOPATROOPA_STANDING_HEIGHT;
	}
	else if (state == KOOPATROOPA_STATE_LYING_UP || state == KOOPATROOPA_STATE_LYING_DOWN)
	{
		r = l + KOOPATROOPA_LYING_WIDTH;
		b = t + KOOPATROOPA_LYING_HEIGHT;
	}
	else
	{
		r = l + KOOPATROOPA_ROLLING_WIDTH;
		b = t + KOOPATROOPA_ROLLING_HEIGHT;
	}
}

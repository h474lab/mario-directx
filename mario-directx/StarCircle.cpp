#include "StarCircle.h"

CStar::CStar(int position)
{
	background = 1;
	this->position = position;
	velocity = 0.0f;

	SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_STAR));
}

void CStar::SetVelocity(float v)
{
	float velocity = v;

	switch (position)
	{
	case STAR_POSITION_TOP_LEFT_EDGE:
		vx -= velocity * STAR_EDGE_RATIO_X;
		vy -= velocity * STAR_EDGE_RATIO_Y;
		break;
	case STAR_POSITION_TOP_LEFT_MID:
		vx -= velocity * STAR_MID_RATIO_X;
		vy -= velocity * STAR_MID_RATIO_Y;
		break;
	case STAR_POSITION_TOP_RIGHT_MID:
		vx += velocity * STAR_MID_RATIO_X;
		vy -= velocity * STAR_MID_RATIO_Y;
		break;
	case STAR_POSITION_TOP_RIGHT_EDGE:
		vx += velocity * STAR_EDGE_RATIO_X;
		vy -= velocity * STAR_EDGE_RATIO_Y;
		break;
	case STAR_POSITION_BOT_LEFT_EDGE:
		vx -= velocity * STAR_EDGE_RATIO_X;
		vy += velocity * STAR_EDGE_RATIO_Y;
		break;
	case STAR_POSITION_BOT_LEFT_MID:
		vx -= velocity * STAR_MID_RATIO_X;
		vy += velocity * STAR_MID_RATIO_Y;
		break;
	case STAR_POSITION_BOT_RIGHT_MID:
		vx += velocity * STAR_MID_RATIO_X;
		vy += velocity * STAR_MID_RATIO_Y;
		break;
	case STAR_POSITION_BOT_RIGHT_EDGE:
		vx += velocity * STAR_EDGE_RATIO_X;
		vy += velocity * STAR_EDGE_RATIO_Y;
		break;
	}
	
	this->velocity = v;
}

void CStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void CStar::Render()
{
	animation_set->at(STAR_ANI_ROTATING_STAR)->Render(x, y);
}

CStarCircle::CStarCircle(float x, float y)
{
	state = STAR_CIRCLE_STATE_HIDING;

	stars[0] = new CStar(STAR_POSITION_TOP_LEFT_EDGE);
	stars[1] = new CStar(STAR_POSITION_TOP_LEFT_MID);
	stars[2] = new CStar(STAR_POSITION_TOP_RIGHT_MID);
	stars[3] = new CStar(STAR_POSITION_TOP_RIGHT_EDGE);
	stars[4] = new CStar(STAR_POSITION_BOT_LEFT_EDGE);
	stars[5] = new CStar(STAR_POSITION_BOT_LEFT_MID);
	stars[6] = new CStar(STAR_POSITION_BOT_RIGHT_MID);
	stars[7] = new CStar(STAR_POSITION_BOT_RIGHT_EDGE);

	SetPosition(x, y);
}

void CStarCircle::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case STAR_CIRCLE_STATE_EXPANDING:
		timer = (DWORD)GetTickCount64();
		break;
	case STAR_CIRCLE_STATE_COLLAPSING:
		timer = (DWORD)GetTickCount64();
		break;
	}
}

void CStarCircle::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	for (int i = 0; i < 8; i++)
	{
		stars[i]->SetPosition(x, y);
	}
}

void CStarCircle::Update(DWORD dt)
{
	switch (state)
	{
	case STAR_CIRCLE_STATE_HIDING:
		return;
	case STAR_CIRCLE_STATE_EXPANDING:
		for (int i = 0; i < 8; i++)
		{
			stars[i]->SetVelocity(STAR_CIRCLE_EXPANDING_SPEED);
			stars[i]->Update(dt);
		}
		if ((DWORD)GetTickCount64() - timer > STAR_CIRCLE_EXPANDING_TIME)
			SetState(STAR_CIRCLE_STATE_COLLAPSING);
		break;
	case STAR_CIRCLE_STATE_COLLAPSING:
		for (int i = 0; i < 8; i++)
		{
			stars[i]->SetVelocity(STAR_CIRCLE_COLLAPSING_SPEED);
			stars[i]->Update(dt);
		}
		if ((DWORD)GetTickCount64() - timer > STAR_CIRCLE_COLLAPSING_TIME)
			SetState(STAR_CIRCLE_STATE_HIDING);
		break;
	}
}

void CStarCircle::Render()
{
	for (int i = 0; i < 8; i++)
		stars[i]->Render();
}

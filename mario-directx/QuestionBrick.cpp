#include "QuestionBrick.h"
#include "Utils.h"
#include "Coin.h"
#include "Game.h"

CQuestionBrick::CQuestionBrick()
{
	background = 0;
	unemptiable = 0;

	flyingSpeedY = MOVEMENT_SPEED_Y;
	SetState(QUESTIONBRICK_STATE_CONTAINING_OBJECTS);

	delayAfterMovingUp = 0;
	disappear = 0;
	bottom_y = 0;

	renderScore = RENDER_SCORE_QUESTIONBRICK;
}

void CQuestionBrick::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	maxFlyingY = y;
	minFlyingY = y - QUESTIONBRICK_BBOX_HEIGHT * 0.75f;
	bottom_y = y + QUESTIONBRICK_BBOX_HEIGHT;

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects[i]->SetDisappearingState();
		objects[i]->SetPosition(this->x, this->y);
	}
}

void CQuestionBrick::AddNewObject(CGameObject* obj)
{
	objects.push_back(obj);
}

int CQuestionBrick::HitQuestionBrick(int side)
{
	SetFlyingDirection(FLYING_DIRECTION_UP, side);

	if (objects.size() > 0)
	{
		CGameObject* obj = objects.back();
		objects.pop_back();
		
		obj->SetFlyingDirection(FLYING_DIRECTION_UP, -side);

		if (dynamic_cast<CCoin*>(obj)) ((CCoin*)obj)->Affect(COIN_AFFECT_TYPE_GAINED);
		return 1;
	}

	return 0;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (((flyingDirection != FLYING_DIRECTION_NOMOVE || y != maxFlyingY) &&
		!(y == maxFlyingY && state == QUESTIONBRICK_STATE_NONE_OBJECTS)) || unemptiable)
		UpdateFlying(dt);

	if (objects.size() == 0)
		SetState(QUESTIONBRICK_STATE_NONE_OBJECTS);

	if (state == QUESTIONBRICK_STATE_CONTAINING_OBJECTS)
	{
		int dir = CanBeHitByTail();
		if (dir)
			HitQuestionBrick(dir);
	}

	// Avoid Mario overlaps question brick
	CGame* game = CGame::GetInstance();
	if (game->CheckPlayerOverlap(this))
	{
		CMario* mario = game->GetPlayer();
		if (!mario->IsJumping())
		{
			float mx, my;
			mario->GetPosition(mx, my);

			float l, t, r, b;
			GetBoundingBox(l, t, r, b);

			float ml, mt, mr, mb;
			mario->GetBoundingBox(ml, mt, mr, mb);

			if (abs((mr + ml) / 2 - l) > abs((mr + ml) / 2 - r))
				mx = x + (r - l);
			else
				mx = x - (mr - ml);

			mario->SetPosition(mx, my);
		}
	}
}

void CQuestionBrick::Render()
{
	int ani = -1;
	if (state == QUESTIONBRICK_STATE_CONTAINING_OBJECTS || unemptiable)
		ani = QUESTIONBRICK_ANI_CONTAINING_OBJECTS;
	else
		ani = QUESTIONBRICK_ANI_NONE_OBJECTS;

	animation_set->at(ani)->Render(x, y);
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + QUESTIONBRICK_BBOX_WIDTH;
	b = bottom_y;
}

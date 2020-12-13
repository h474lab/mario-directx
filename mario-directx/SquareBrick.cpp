#include "SquareBrick.h"

CSquareBrick::CSquareBrick()
{
	background = 0;
	SetState(SQUARE_BRICK_STATE_AVAILABLE);
	fragmentAnimationSet = NULL;
	renderScore = RENDER_SCORE_SQUARE_BRICK;
}

void CSquareBrick::Destroy()
{
	background = 1;
	SetState(SQUARE_BRICK_STATE_UNAVAILABLE);

	for (int i = 0; i < 4; i++)
	{
		fragments[i] = new CBrickFragment();
		fragments[i]->SetAnimationSet(fragmentAnimationSet);
		fragments[i]->SetPosition(x + i % 2, y + i / 2);
	}
	
	fragments[0]->SetPos(FRAGMENT_POSITION_TOP_LEFT);
	fragments[1]->SetPos(FRAGMENT_POSITION_TOP_RIGHT);
	fragments[2]->SetPos(FRAGMENT_POSITION_BOT_LEFT);
	fragments[3]->SetPos(FRAGMENT_POSITION_BOT_RIGHT);

	for (int i = 0; i < 4; i++) fragments[i]->Hit();
}

CSquareBrick* CSquareBrick::Duplicate()
{
	CSquareBrick* result = new CSquareBrick();
	result->SetPosition(x, y);
	result->SetState(state);
	result->SetAnimationSet(animation_set);
	result->SetFragmentAnimationSet(fragmentAnimationSet);
	return result;
}

void CSquareBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == SQUARE_BRICK_STATE_AVAILABLE && CanBeHitByTail()) Destroy();

	if (fragments[0])
	{
		if (fragments[0]->GetState() != FRAGMENT_STATE_OUT)
		{
			for (int i = 0; i < 4; i++) fragments[i]->Update(dt);
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				delete fragments[i];
				fragments[i] = NULL;
			}
		}
	}
}

void CSquareBrick::Render()
{
	if (state == SQUARE_BRICK_STATE_AVAILABLE)
		animation_set->at(0)->Render(x, y);
	else if (fragments[0])
	{
		for (int i = 0; i < 4; i++) fragments[i]->Render();
	}
}

void CSquareBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == SQUARE_BRICK_STATE_UNAVAILABLE) return;
	l = x;
	t = y;
	r = l + SQUARE_BRICK_BBOX_WIDTH;
	b = t + SQUARE_BRICK_BBOX_HEIGHT;
}

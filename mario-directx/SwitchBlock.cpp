#include "SwitchBlock.h"
#include "Coin.h"
#include "Utils.h"
#include "Grid.h"

CSwitchBlock::CSwitchBlock()
{
	SetState(SWITCH_BLOCK_STATE_UNAVAILABLE);
	hasBeenSwitched = 0;
}

void CSwitchBlock::AddObject(CGameObject* object)
{
	DebugOut(L"\nAdd Object pointer: %p", object);
	objects.push_back(object);
}

void CSwitchBlock::Switch()
{
	SetState(SWITCH_BLOCK_STATE_PRESSED);
	switching_start = (DWORD)GetTickCount64();

	savingObjects.clear();
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		savingObjects.push_back(objects[i]);
		if (dynamic_cast<CSquareBrick*>(savingObjects[i]))
		{
			CSquareBrick* squareBrick = dynamic_cast<CSquareBrick*>(savingObjects[i]);
			CGameObject* coin = new CCoin();

			if (squareBrick->GetState() != SQUARE_BRICK_STATE_AVAILABLE) continue;

			float x, y;
			savingObjects[i]->GetPosition(x, y);
			coin->SetPosition(x, y);
			coin->SetAnimationSet(squareBrick->GetCoinAnimationSet());
			objects[i] = coin;

			CGrids::GetInstance()->Get(gridId)->ReplaceObject(savingObjects[i], objects[i]);
		}
	}
}

void CSwitchBlock::SwitchBack()
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CCoin*>(objects[i]))
		{
			if (objects[i]->GetState() == COIN_STATE_AVAILABLE)
				CGrids::GetInstance()->Get(gridId)->ReplaceObject(objects[i], savingObjects[i]);
		}
	}
}

void CSwitchBlock::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	minFlyingY = y - SWITCH_BLOCK_HEIGHT;
	maxFlyingY = y - SWITCH_BLOCK_HEIGHT;
	flyingSpeedY = SWITCH_BLOCK_FLYING_SPEED_Y;
	delayAfterMovingUp = 0;
}

void CSwitchBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SWITCH_BLOCK_STATE_UNPRESSED:
		background = 0;
		break;
	case SWITCH_BLOCK_STATE_PRESSED:
		background = 1;
		break;
	case SWITCH_BLOCK_STATE_UNAVAILABLE:
		background = 1;
		break;
	}
}

void CSwitchBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == SWITCH_BLOCK_STATE_UNPRESSED)
	{
		left = x;
		top = y;
		right = x + SWITCH_BLOCK_WIDTH;
		bottom = y + SWITCH_BLOCK_HEIGHT;
	}
}

void CSwitchBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (flyingDirection != FLYING_DIRECTION_NOMOVE)
	{
		UpdateFlying(dt);
		return;
	}

	if (state == SWITCH_BLOCK_STATE_PRESSED)
	{
		if ((DWORD)GetTickCount64() - switching_start > SWITCHING_TIME && !hasBeenSwitched)
		{
			SwitchBack();
			hasBeenSwitched = 1;
		}
	}
}

void CSwitchBlock::Render()
{
	if (state == SWITCH_BLOCK_STATE_UNAVAILABLE) return;

	if (state == SWITCH_BLOCK_STATE_UNPRESSED)
		animation_set->at(SWITCH_BLOCK_ANI_UNPRESSED)->Render(x, y);
	else
		animation_set->at(SWITCH_BLOCK_ANI_PRESSED)->Render(x, y);
}

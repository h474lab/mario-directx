#include "Coin.h"
#include "Utils.h"
#include "Game.h"
#include "HUD.h"

CCoin::CCoin()
{
	background = 1;
	SetState(COIN_STATE_AVAILABLE);

	flyingSpeedY = COIN_FLYING_SPEED_Y;
	delayAfterMovingUp = 0;
	disappear = 1;

	renderScore = RENDER_SCORE_COIN;
}

void CCoin::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	minFlyingY = y - 4 * COIN_BBOX_HEIGHT;
	maxFlyingY = y - 2 * COIN_BBOX_HEIGHT;
}

void CCoin::Affect(int type)
{
	if (type == COIN_AFFECT_TYPE_GAINED)
	{
		CHUD* hud = CHUD::GetInstance();
		hud->AddScore(COIN_SCORE_GAINED);
		hud->AddMoney(COIN_MONEY_GAINED);
	}
}

void CCoin::SetDisappearingState()
{
	SetState(COIN_STATE_UNAVAILABLE);
}

void CCoin::SetAppearingState()
{
	SetState(COIN_STATE_AVAILABLE);
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (flyingDirection != FLYING_DIRECTION_NOMOVE) UpdateFlying(dt);
	if (state == COIN_STATE_AVAILABLE)
	{
		CGame* game = CGame::GetInstance();
		if (game->CheckPlayerOverlap(this))
		{
			Affect(COIN_AFFECT_TYPE_GAINED);
			SetState(COIN_STATE_UNAVAILABLE);
		}
	}

}

void CCoin::Render()
{
	if (state == COIN_STATE_AVAILABLE)
		animation_set->at(0)->Render(x, y);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

#include "HUD.h"
#include "Textures.h"
#include "Game.h"

CHUD* CHUD::__instance = NULL;

CHUD::CHUD()
{
	background = 1;
	scoreBoard = new CScoreboard();
}

void CHUD::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case HUD_STATE_INTRO_SCENE:
		scoreBoard->SetState(SCORE_BOARD_STATE_DISAPPEAR);
		break;
	case HUD_STATE_PLAY_SCENE:
		scoreBoard->SetState(SCORE_BOARD_STATE_APPEAR);
		break;
	}
}

void CHUD::Delete()
{
	if (scoreBoard)
	{
		scoreBoard->Delete();
		delete scoreBoard;
		scoreBoard = NULL;
	}
}

void CHUD::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);

	scoreBoard->SetPosition(x + SCOREBOARD_POSITION_X, y + SCOREBOARD_POSITION_Y);
}

void CHUD::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void CHUD::Render()
{
	for (int i = 0; i < HUD_RENDERING_COLUMN; i++)
	{
		if (state == HUD_STATE_INTRO_SCENE)
			animation_set->at(HUD_ANI_BG_INTRO)->Render(x + i * HUD_BG_WIDTH, y);
		else
			animation_set->at(HUD_ANI_BG_PLAY)->Render(x + i * HUD_ANI_BG_PLAY, y);
	}

	scoreBoard->Render();
}

CHUD* CHUD::GetInstance()
{
	if (__instance == NULL) __instance = new CHUD();
	return __instance;
}

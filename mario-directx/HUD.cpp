#include "HUD.h"
#include "Textures.h"
#include "Game.h"
#include "Camera.h"

CHUD* CHUD::__instance = NULL;

CHUD::CHUD()
{
	background = 1;
	scoreBoard = new CScoreboard();
	card_1 = new CCard();
	card_2 = new CCard();
	card_3 = new CCard();
}

void CHUD::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case HUD_STATE_INTRO_SCENE:
		scoreBoard->SetState(SCORE_BOARD_STATE_DISAPPEAR);
		SetCards(CARD_STATE_HIDING, CARD_STATE_HIDING, CARD_STATE_HIDING);
		background = 0;
		break;
	case HUD_STATE_MAP_SCENE:
		scoreBoard->SetState(SCORE_BOARD_STATE_APPEAR);
		SetCards(CARD_STATE_APPEAR, CARD_STATE_APPEAR, CARD_STATE_APPEAR);
		background = 1;
		break;
	case HUD_STATE_PLAY_SCENE:
		scoreBoard->SetState(SCORE_BOARD_STATE_APPEAR);
		SetCards(CARD_STATE_APPEAR, CARD_STATE_APPEAR, CARD_STATE_APPEAR);
		background = 1;
		break;
	}
}

void CHUD::SetCards(int card_1_state, int card_2_state, int card_3_state)
{
	this->card_1->SetState(card_1_state);
	this->card_2->SetState(card_2_state);
	this->card_3->SetState(card_3_state);
}

void CHUD::GetCards(int& card_1_state, int& card_2_state, int& card_3_state)
{
	card_1_state = card_1->GetState();
	card_2_state = card_2->GetState();
	card_3_state = card_3->GetState();
}

void CHUD::AddCard(int type)
{
	if (card_1->GetType() == CARD_TYPE_BLANK)
		card_1->SetType(type);
	else if (card_2->GetType() == CARD_TYPE_BLANK)
		card_2->SetType(type);
	else if (card_3->GetType() == CARD_TYPE_BLANK)
		card_3->SetType(type);
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

	card_1->SetPosition(x + CARD_1_POSITION_X, y + CARD_1_POSITION_Y);
	card_2->SetPosition(x + CARD_2_POSITION_X, y + CARD_2_POSITION_Y);
	card_3->SetPosition(x + CARD_3_POSITION_X, y + CARD_3_POSITION_Y);
}

void CHUD::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + CGame::GetInstance()->GetScreenWidth();
	bottom = top + CGame::GetInstance()->GetScreenHeight() - GAME_PLAY_HEIGHT;
}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cam_x, cam_y;
	CCamera::GetInstance()->GetPosition(cam_x, cam_y);
	SetPosition(cam_x, cam_y + GAME_PLAY_HEIGHT);
}

void CHUD::Render()
{
	for (int i = 0; i < HUD_RENDERING_COLUMN; i++)
	{
		if (state == HUD_STATE_INTRO_SCENE)
			animation_set->at(HUD_ANI_BG_INTRO)->Render(x + i * HUD_BG_WIDTH, y);
		else
			animation_set->at(HUD_ANI_BG_PLAY)->Render(x + i * HUD_BG_WIDTH, y);
	}

	scoreBoard->Render();

	card_1->Render();
	card_2->Render();
	card_3->Render();
}

CHUD* CHUD::GetInstance()
{
	if (__instance == NULL) __instance = new CHUD();
	return __instance;
}

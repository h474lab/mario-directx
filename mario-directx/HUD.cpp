#include "HUD.h"
#include "Textures.h"
#include "Game.h"

CHUD::CHUD()
{
	background = 1;

	scoreBoard = new CScoreboard();
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
	RECT rect;

	LPDIRECT3DTEXTURE9 hud = CTextures::GetInstance()->Get(ID_HUD_BG);

	CGame* game = CGame::GetInstance();

	rect.left = 0;
	rect.top = 0;
	rect.right = game->GetScreenWidth();
	rect.bottom = game->GetScreenHeight() - GAME_PLAY_HEIGHT;

	CGame::GetInstance()->Draw(x, y, hud, rect.left, rect.top, rect.right, rect.bottom);

	scoreBoard->Render();
}

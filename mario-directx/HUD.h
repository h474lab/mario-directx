#pragma once
#include "GameObject.h"
#include "Scoreboard.h"
#include "Card.h"

#define HUD_STATE_INTRO_SCENE	0
#define HUD_STATE_MAP_SCENE		1
#define HUD_STATE_PLAY_SCENE	2

#define HUD_ANI_BG_INTRO	0
#define HUD_ANI_BG_PLAY		1

#define HUD_BG_WIDTH			256
#define HUD_RENDERING_COLUMN	2

#define SCOREBOARD_POSITION_X	4
#define SCOREBOARD_POSITION_Y	1

#define CARD_1_POSITION_X	200
#define CARD_1_POSITION_Y	2

#define CARD_2_POSITION_X	225
#define CARD_2_POSITION_Y	2

#define CARD_3_POSITION_X	250
#define CARD_3_POSITION_Y	2

class CHUD : public CGameObject
{
	static CHUD* __instance;
	CScoreboard* scoreBoard;

	CCard* card_1, * card_2, * card_3;
public:
	CHUD();

	virtual void SetState(int state);
	
	// Scoreboard
	void SetWorld(int world) { scoreBoard->SetWorld(world); }
	void SetMoney(int money) { scoreBoard->SetMoney(money); }
	void SetScore(int score) { scoreBoard->SetScore(score); }
	void SetLives(int lives) { scoreBoard->SetLives(lives); }
	void SetPowerLevel(int powerLevel) { scoreBoard->SetPowerLevel(powerLevel); }
	void SetRemainingTime(int remainingTime) { scoreBoard->SetRemainingTime(remainingTime); }

	void AddMoney(int money) { scoreBoard->SetMoney(scoreBoard->GetMoney() + money); }
	void AddScore(int score) { scoreBoard->SetScore(scoreBoard->GetScore() + score); }
	void AddLives(int lives) { scoreBoard->SetLives(scoreBoard->GetLives() + lives); }

	int GetWorld() { return scoreBoard->GetWorld(); }
	int GetMoney() { return scoreBoard->GetMoney(); }
	int GetScore() { return scoreBoard->GetScore(); }
	int GetLives() { return scoreBoard->GetLives(); }
	int GetPowerLevel() { return scoreBoard->GetPowerLevel(); }
	int GetRemainingTime() { return scoreBoard->GetRemainingTime(); }

	// Cards
	void SetCards(int card_1_state, int card_2_state, int card_3_state);
	void GetCards(int& card_1_state, int& card_2_state, int& card_3_state);

	void AddCard(int state);

	void Delete();

	virtual void SetPosition(float x, float y);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	static CHUD* GetInstance();
};


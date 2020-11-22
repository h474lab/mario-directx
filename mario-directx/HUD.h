#pragma once
#include "GameObject.h"
#include "Scoreboard.h"

#define SCOREBOARD_POSITION_X	4
#define SCOREBOARD_POSITION_Y	1

class CHUD : public CGameObject
{
	static CHUD* __instance;
	CScoreboard* scoreBoard;
public:
	CHUD();

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

	void Delete();

	virtual void SetPosition(float x, float y);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	static CHUD* GetInstance();
};


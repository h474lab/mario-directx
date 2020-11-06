#pragma once
#include "GameObject.h"
#include "Number.h"
#include "PowerArrow.h"
#include "PowerSign.h"

#define WORLD_NUMBER_POSITION_X	38
#define WORLD_NUMBER_POSITION_Y	8

#define MONEY_NUMBER_POSITION_X	132
#define MONEY_NUMBER_POSITION_Y	8

#define LIVES_NUMBER_POSITION_X	30
#define LIVES_NUMBER_POSITION_Y	16

#define SCORE_NUMBER_POSITION_X	52
#define SCORE_NUMBER_POSITION_Y	16

#define REMAINING_TIME_NUMBER_POSITION_X	124
#define REMAINING_TIME_NUMBER_POSITION_Y	16

#define POWER_ARROW_POSITION_X	52
#define POWER_ARROW_POSITION_Y	8
#define MAXIMUM_POWER_LEVEL		6

class CScoreboard : public CGameObject
{
	int world;
	int score, lives;
	int money;
	int powerLevel;
	int remainingTime;

	vector<CGameObject*> objectSet;

	CNumber* number_World;
	CNumber* number_Money[2];
	CNumber* number_Lives[2];
	CNumber* number_Score[7];
	CNumber* number_RemainingTime[3];
	CPowerArrow* powerArrow[6];
	CPowerSign* powerSign;
public:
	CScoreboard();

	void SetWorld(int world);
	void SetMoney(int money);
	void SetScore(int score);
	void SetLives(int lives);
	void SetPowerLevel(int powerLevel);
	void SetRemainingTime(int remainingTime);

	int GetWorld() { return world; }
	int GetMoney() { return money; }
	int GetScore() { return score; }
	int GetLives() { return lives; }
	int GetPowerLevel() { return powerLevel; }
	int GetRemainingTime() { return remainingTime; }

	void Delete();

	virtual void SetPosition(float x, float y);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};


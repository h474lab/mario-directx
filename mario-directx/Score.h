#pragma once
#include "GameObject.h"

#define SCORE_FLYING_SPEED_Y	0.3f
#define SCORE_STAYING_TIME		1000

#define SCORE_ANI_100	0
#define SCORE_ANI_200	1
#define SCORE_ANI_400	2
#define SCORE_ANI_800	3
#define SCORE_ANI_1000	4
#define SCORE_ANI_2000	5
#define SCORE_ANI_4000	6
#define SCORE_ANI_8000	7
#define SCORE_ANI_1UP	8

#define SCORE_STATE_APPEAR		0
#define SCORE_STATE_DISAPPEAR	1

class CScore : public CGameObject
{
	int score;
	DWORD score_start_appearing;
public:
	CScore();
	void SetScore(int score) { this->score = score; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};

typedef CScore* LPSCORE;

class CScores
{
	vector<LPSCORE> scores;
	static CScores* __instance;
public:
	void CreateNewScoreObject(int score, CGameObject *object);
	void Update(DWORD dt);
	void Render();

	static CScores* GetInstance();
};
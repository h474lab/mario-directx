#include "Score.h"
#include "Mario.h"

CScore::CScore()
{
	background = 1;
	SetState(SCORE_STATE_APPEAR);
	score_start_appearing = GetTickCount64();
	SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_SCORE));
}

void CScore::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == SCORE_STATE_DISAPPEAR) return;
	
	if (GetTickCount64() - score_start_appearing > SCORE_STAYING_TIME)
		SetState(SCORE_STATE_DISAPPEAR);
	else y -= SCORE_FLYING_SPEED_Y;
}

void CScore::Render()
{
	if (state == SCORE_STATE_DISAPPEAR) return;

	int ani = -1;
	if (score == MARIO_SCORE_100) ani = SCORE_ANI_100;
	else if (score == MARIO_SCORE_200) ani = SCORE_ANI_200;
	else if (score == MARIO_SCORE_400) ani = SCORE_ANI_400;
	else if (score == MARIO_SCORE_800) ani = SCORE_ANI_800;
	else if (score == MARIO_SCORE_1000) ani = SCORE_ANI_1000;
	else if (score == MARIO_SCORE_2000) ani = SCORE_ANI_2000;
	else if (score == MARIO_SCORE_4000) ani = SCORE_ANI_4000;
	else if (score == MARIO_SCORE_8000) ani = SCORE_ANI_8000;
	else if (score == MARIO_SCORE_1UP) ani = SCORE_ANI_1UP;
	
	if (ani != -1) animation_set->at(ani)->Render(x, y);
}

CScores * CScores::__instance = NULL;

void CScores::CreateNewScoreObject(int scoreType, CGameObject *object)
{
	// get current object's position for displaying score
	float x, y;
	object->GetPosition(x, y);

	// initialize new LPSCORE object
	LPSCORE score = new CScore();
	score->SetPosition(x, y);
	score->SetScore(scoreType);

	// push this object into Score Manager
	scores.push_back(score);
}

void CScores::Update(DWORD dt)
{
	for (LPSCORE score : scores)
	{
		if (!score) continue;
		/*if (score->GetState() == SCORE_STATE_DISAPPEAR)
		{
			delete score;
			score = NULL;
			continue;
		}*/
		score->Update(dt);
	}
}

void CScores::Render()
{
	for (LPSCORE score : scores)
	{
		if (!score) continue;
		if (score->GetState() == SCORE_STATE_DISAPPEAR) continue;
		score->Render();
	}
}

CScores* CScores::GetInstance()
{
	if (__instance == NULL) __instance = new CScores();
	return __instance;
}

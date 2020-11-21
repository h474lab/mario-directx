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
	
	if (score_start_appearing > SCORE_STAYING_TIME)
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

#include "Scoreboard.h"

CScoreboard::CScoreboard()
{
	background = 1;

	SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_SCOREBOARD));

	objectSet.clear();

	number_World = new CNumber();
	objectSet.push_back(number_World);

	for (int i = 0; i < 2; i++)
	{
		number_Money[i] = new CNumber();
		objectSet.push_back(number_Money[i]);

		number_Lives[i] = new CNumber();
		objectSet.push_back(number_Lives[i]);
	}

	for (int i = 0; i < 7; i++)
	{
		number_Score[i] = new CNumber();
		objectSet.push_back(number_Score[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		number_RemainingTime[i] = new CNumber();
		objectSet.push_back(number_RemainingTime[i]);
	}

	for (int i = 0; i < MAXIMUM_POWER_LEVEL; i++)
	{
		powerArrow[i] = new CPowerArrow();
		objectSet.push_back(powerArrow[i]);
	}

	powerSign = new CPowerSign();
	objectSet.push_back(powerSign);

	SetWorld(DEFAULT_WORLD);
	SetMoney(DEFAULT_MONEY);
	SetLives(DEFAULT_LIVES);
	SetScore(DEFAULT_SCORE);
	SetRemainingTime(DEFAULT_TIME);
}

void CScoreboard::SetWorld(int world)
{
	this->world = world;
	number_World->SetState(NUMBER_STATE_AVAILABLE);
	number_World->SetCurrentNumber(this->world);
}

void CScoreboard::SetMoney(int money)
{
	this->money = money;

	if (this->money < 10)
	{
		number_Money[0]->SetState(NUMBER_STATE_UNAVAILABLE);

		number_Money[1]->SetState(NUMBER_STATE_AVAILABLE);
		number_Money[1]->SetCurrentNumber(this->money);
	}
	else
	{
		number_Money[0]->SetState(NUMBER_STATE_AVAILABLE);
		number_Money[0]->SetCurrentNumber(this->money / 10);

		number_Money[1]->SetState(NUMBER_STATE_AVAILABLE);
		number_Money[1]->SetCurrentNumber(this->money % 10);
	}
}

void CScoreboard::SetScore(int score)
{
	this->score = score;
	int temp = this->score;

	for (int i = 6; i >= 0; i--)
	{
		number_Score[i]->SetState(NUMBER_STATE_AVAILABLE);
		number_Score[i]->SetCurrentNumber(temp % 10);
		temp /= 10;
	}
}

void CScoreboard::SetLives(int lives)
{
	this->lives = lives;
	if (this->lives < 10)
	{
		number_Lives[0]->SetState(NUMBER_STATE_UNAVAILABLE);

		number_Lives[1]->SetState(NUMBER_STATE_AVAILABLE);
		number_Lives[1]->SetCurrentNumber(this->lives);
	}
	else
	{
		number_Lives[0]->SetState(NUMBER_STATE_AVAILABLE);
		number_Lives[0]->SetCurrentNumber(this->lives / 10);

		number_Lives[1]->SetState(NUMBER_STATE_AVAILABLE);
		number_Lives[1]->SetCurrentNumber(this->lives % 10);
	}
}

void CScoreboard::SetPowerLevel(int powerLevel)
{
	this->powerLevel = powerLevel;

	for (int i = 0; i < 6; i++)
	{
		if (i < powerLevel)
			powerArrow[i]->SetState(POWER_OBJECT_STATE_ON);
		else
			powerArrow[i]->SetState(POWER_OBJECT_STATE_OFF);
	}

	if (powerLevel >= MAXIMUM_POWER_LEVEL)
		powerSign->SetState(POWER_OBJECT_STATE_ON);
	else
		powerSign->SetState(POWER_OBJECT_STATE_OFF);
}

void CScoreboard::SetRemainingTime(int remainingTime)
{
	this->remainingTime = remainingTime;
	int temp = this->remainingTime;
	
	for (int i = 2; i >= 0; i--)
	{
		number_RemainingTime[i]->SetState(NUMBER_STATE_AVAILABLE);
		number_RemainingTime[i]->SetCurrentNumber(temp % 10);
		temp /= 10;
	}
}

void CScoreboard::Delete()
{
	for (unsigned int i = 0; i < objectSet.size(); i++)
	{
		if (objectSet.at(i))
		{
			delete objectSet.at(i);
			objectSet.at(i) = NULL;
		}
	}
}

void CScoreboard::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);

	number_World->SetPosition(x + WORLD_NUMBER_POSITION_X, y + WORLD_NUMBER_POSITION_Y);

	for (int i = 0; i < 2; i++)
	{
		number_Money[i]->SetPosition(x + MONEY_NUMBER_POSITION_X + NUMBER_WIDTH * i, y + MONEY_NUMBER_POSITION_Y);
		number_Lives[i]->SetPosition(x + LIVES_NUMBER_POSITION_X + NUMBER_WIDTH * i, y + LIVES_NUMBER_POSITION_Y);
	}

	for (int i = 0; i < 7; i++)
		number_Score[i]->SetPosition(x + SCORE_NUMBER_POSITION_X + NUMBER_WIDTH * i, y + SCORE_NUMBER_POSITION_Y);

	for (int i = 0; i < 3; i++)
		number_RemainingTime[i]->SetPosition(x + REMAINING_TIME_NUMBER_POSITION_X + NUMBER_WIDTH * i, y + REMAINING_TIME_NUMBER_POSITION_Y);
	
	for (int i = 0; i < MAXIMUM_POWER_LEVEL; i++)
		powerArrow[i]->SetPosition(x + POWER_ARROW_POSITION_X + POWER_ARROW_WIDTH * i, y + POWER_ARROW_HEIGHT);

	powerSign->SetPosition(x + POWER_ARROW_POSITION_X + POWER_ARROW_WIDTH * MAXIMUM_POWER_LEVEL, y + POWER_ARROW_HEIGHT);
}

void CScoreboard::Render()
{
	if (state == SCORE_BOARD_STATE_DISAPPEAR) return;
	animation_set->at(0)->Render(x, y);

	for (unsigned int i = 0; i < objectSet.size(); i++)
		objectSet.at(i)->Render();
}

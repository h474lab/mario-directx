#include "Reward.h"

CReward::CReward()
{
	background = 0;
	type = REWARD_TYPE_MUSHROOM;
	state = REWARD_STATE_AVAILABLE;
	switching_start = (DWORD)GetTickCount64();
}

int CReward::GetNextRewardType()
{
	if (type == REWARD_TYPE_MUSHROOM)
		return REWARD_TYPE_FLOWER;
	else if (type == REWARD_TYPE_FLOWER)
		return REWARD_TYPE_STAR;
	
	return REWARD_TYPE_MUSHROOM;
}

void CReward::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + REWARD_BBOX_WIDTH;
	bottom = top + REWARD_BBOX_HEIGHT;
}

void CReward::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// stop updating when Reward has been acquired
	if (state == REWARD_STATE_ACQUIRED) return;

	// switching type after an amount of time
	if ((DWORD)GetTickCount64() - switching_start > REWARD_DELAY_SWICHING_TYPE_TIME)
	{
		type = GetNextRewardType();
		switching_start = (DWORD)GetTickCount64();
	}
}

void CReward::Render()
{
	if (state == REWARD_STATE_ACQUIRED) return;

	int ani = -1;
	switch (type)
	{
	case REWARD_TYPE_MUSHROOM:
		ani = REWARD_ANI_MUSHROOM;
		break;
	case REWARD_TYPE_FLOWER:
		ani = REWARD_ANI_FLOWER;
		break;
	case REWARD_TYPE_STAR:
		ani = REWARD_ANI_STAR;
		break;
	}

	if (ani != -1)
		animation_set->at(ani)->Render(x, y);
}

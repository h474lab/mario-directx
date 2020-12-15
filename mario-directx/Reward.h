#pragma once
#include "GameObject.h"

#define REWARD_STATE_AVAILABLE	0
#define REWARD_STATE_ACQUIRED	1

#define REWARD_ANI_MUSHROOM	0
#define REWARD_ANI_FLOWER	1
#define REWARD_ANI_STAR		2

#define REWARD_ANI_MUSHROOM_ACQUIRED	3
#define REWARD_ANI_FLOWER_ACQUIRED		4
#define REWARD_ANI_STAR_ACQUIRED		5

#define REWARD_TYPE_MUSHROOM	0
#define REWARD_TYPE_FLOWER		1
#define REWARD_TYPE_STAR		2

#define REWARD_BBOX_WIDTH	16
#define REWARD_BBOX_HEIGHT	16

#define REWARD_DELAY_SWICHING_TYPE_TIME	100
#define REWARD_ACQUIRED_FLYING_SPEED_Y	0.05f

class CReward : public CGameObject
{
	int type;
	DWORD switching_start;
public:
	CReward();
	virtual void SetState(int state);

	int GetNextRewardType();
	void Gain();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


#pragma once
#include "GameObject.h"

#define TITLE_TYPE_MONOCHROME	0
#define TITLE_TYPE_COLORFUL		1

#define TITLE_STATE_DROPPING	0
#define TITLE_STATE_VIBRATING	1
#define TITLE_STATE_IDLE		2

#define TITLE_ANI_TEXT						0
#define TITLE_ANI_NUMBER					1
#define TITLE_ANI_COLORFUL_BIG_CLOUD		2
#define TITLE_ANI_COLORFUL_SMALL_CLOUD		3
#define TITLE_ANI_MONOCHROME_BIG_CLOUD		4
#define TITLE_ANI_MONOCHROME_SMALL_CLOUD	5

#define TITLE_DROPPING_SPEED		0.02f
#define TITLE_VIBRATING_DISTANCE	0.5f

#define VIBRATING_DIRECTION_UP		0
#define VIBRATING_DIRECTION_DOWN	1
#define VIBRATING_TIME				100

#define SMALL_CLOUD_1_POSITION_X	0.0f
#define SMALL_CLOUD_1_POSITION_Y	0.0f
#define BIG_CLOUD_1_POSITION_X		0.0f
#define BIG_CLOUD_1_POSITION_Y		0.0f
#define BIG_CLOUD_2_POSITION_X		0.0f
#define BIG_CLOUD_2_POSITION_Y		0.0f

#define NUMBER_POSITION_X			0.0f
#define NUMBER_POSITION_Y			0.0f

class CTitle : public CGameObject
{
	int vibratingDirection;
	DWORD vibrate_start;
public:
	CTitle();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


#pragma once
#include "GameObject.h"

#define TITLE_TYPE_MONOCHROME	0
#define TITLE_TYPE_COLORFUL		1

#define TITLE_STATE_MONOCHROME_DROPPING				0
#define TITLE_STATE_MONOCHROME_VIBRATING			1
#define TITLE_STATE_MONOCHROME_IDLE					2
#define TITLE_STATE_MONOCHROME_IDLE_COLOR_NUMBER	3
#define TITLE_STATE_COLORFUL_DROPPING				4
#define TITLE_STATE_COLORFUL_VIBRATING				5
#define TITLE_STATE_COLORFUL_IDLE					6
#define TITLE_STATE_COLORFUL_IDLE_COLOR_NUMBER		7

#define TITLE_ANI_TEXT						0
#define TITLE_ANI_NUMBER_COLOR_CHANGING		1
#define TITLE_ANI_NUMBER_COLOR_NOT_CHANGING	2
#define TITLE_ANI_COLORFUL_BIG_CLOUD		3
#define TITLE_ANI_COLORFUL_SMALL_CLOUD		4
#define TITLE_ANI_MONOCHROME_BIG_CLOUD		5
#define TITLE_ANI_MONOCHROME_SMALL_CLOUD	6

#define TITLE_DROPPING_SPEED		2.0f
#define TITLE_VIBRATING_DISTANCE	1.0f

#define VIBRATING_DIRECTION_UP		0
#define VIBRATING_DIRECTION_DOWN	1
#define VIBRATING_TIME				50

#define SMALL_CLOUD_1_POSITION_X	-40.0f
#define SMALL_CLOUD_1_POSITION_Y	64.0f
#define BIG_CLOUD_1_POSITION_X		-24.0f
#define BIG_CLOUD_1_POSITION_Y		16.0f
#define BIG_CLOUD_2_POSITION_X		168.0f
#define BIG_CLOUD_2_POSITION_Y		0.0f

#define NUMBER_POSITION_X			72.0f
#define NUMBER_POSITION_Y			72.0f

class CTitle : public CGameObject
{
	int vibratingDirection;
	int type;
	DWORD vibrate_start;
public:
	CTitle();

	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


#include "Title.h"

CTitle::CTitle()
{
	background = 1;
	SetState(TITLE_STATE_MONOCHROME_IDLE);
}

void CTitle::SetState(int state)
{
	CGameObject::SetState(state);

	if (state == TITLE_STATE_MONOCHROME_VIBRATING || state == TITLE_STATE_COLORFUL_VIBRATING)
	{
		vibrate_start = (DWORD)GetTickCount64();
		vibratingDirection = VIBRATING_DIRECTION_UP;

	}
}

void CTitle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == TITLE_STATE_MONOCHROME_IDLE || state == TITLE_STATE_COLORFUL_IDLE) return;
	if (state == TITLE_STATE_MONOCHROME_DROPPING || state == TITLE_STATE_COLORFUL_DROPPING)
	{
		y += TITLE_DROPPING_SPEED;
		return;
	}
	if ((state == TITLE_STATE_MONOCHROME_VIBRATING || state == TITLE_STATE_COLORFUL_VIBRATING) && GetTickCount64() - vibrate_start >= VIBRATING_TIME)
	{
		if (vibratingDirection == VIBRATING_DIRECTION_UP)
		{
			y -= TITLE_VIBRATING_DISTANCE;
			vibratingDirection = VIBRATING_DIRECTION_DOWN;
		}
		else
		{
			y += TITLE_VIBRATING_DISTANCE;
			vibratingDirection = VIBRATING_DIRECTION_UP;
		}
		vibrate_start = (DWORD)GetTickCount64();
	}
}

void CTitle::Render()
{
	int ani_cloud_big, ani_cloud_small, ani_text, ani_number;
	
	ani_text = TITLE_ANI_TEXT;
	if (state == TITLE_STATE_MONOCHROME_IDLE || state == TITLE_STATE_COLORFUL_IDLE)
		ani_number = TITLE_ANI_NUMBER_COLOR_CHANGING;
	else
		ani_number = TITLE_ANI_NUMBER_COLOR_NOT_CHANGING;

	if (state == TITLE_STATE_MONOCHROME_DROPPING || state == TITLE_STATE_MONOCHROME_IDLE || state == TITLE_STATE_MONOCHROME_VIBRATING || state == TITLE_STATE_MONOCHROME_IDLE_COLOR_NUMBER)
	{
		ani_cloud_big = TITLE_ANI_MONOCHROME_BIG_CLOUD;
		ani_cloud_small = TITLE_ANI_MONOCHROME_SMALL_CLOUD;
	}
	else
	{
		ani_cloud_big = TITLE_ANI_COLORFUL_BIG_CLOUD;
		ani_cloud_small = TITLE_ANI_COLORFUL_SMALL_CLOUD;
	}

	animation_set->at(ani_text)->Render(x, y);
	animation_set->at(ani_number)->Render(x + NUMBER_POSITION_X, y + NUMBER_POSITION_Y);
	animation_set->at(ani_cloud_small)->Render(x + SMALL_CLOUD_1_POSITION_X, y + SMALL_CLOUD_1_POSITION_Y);
	animation_set->at(ani_cloud_big)->Render(x + BIG_CLOUD_1_POSITION_X, y + BIG_CLOUD_1_POSITION_Y);
	animation_set->at(ani_cloud_big)->Render(x + BIG_CLOUD_2_POSITION_X, y + BIG_CLOUD_2_POSITION_Y);
}

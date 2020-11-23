#include "Title.h"

CTitle::CTitle()
{
	background = 1;
}

void CTitle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == TITLE_STATE_IDLE) return;
	if (state == TITLE_STATE_DROPPING)
	{
		y += TITLE_DROPPING_SPEED;
		return;
	}
	if (state == TITLE_STATE_VIBRATING && GetTickCount64() - vibrate_start >= VIBRATING_TIME)
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
	}
}

void CTitle::Render()
{
	int ani_cloud_big, ani_cloud_small, ani_text, ani_number;
	
	ani_text = TITLE_ANI_TEXT;
	ani_number = TITLE_ANI_NUMBER;
	if (state == TITLE_TYPE_MONOCHROME)
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

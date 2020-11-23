#include "Curtain.h"

CCurtain::CCurtain(int numberOfRows)
{
	background = 1;
	numRows = numberOfRows;
}

void CCurtain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == CURTAIN_STATE_IDLE) return;
	if (state == CURTAIN_STATE_PULLING_UP)
		y -= CURTAIN_PULLING_SPEED_Y;
}

void CCurtain::Render()
{
	if (type == CURTAIN_TYPE_COLLAPSED)
		animation_set->at(CURTAIN_ANI_HEADING)->Render(x, y);
	else if (type == CURTAIN_TYPE_LARGE)
	{
		for (int i = 0; i < numRows - 1; i++)
			animation_set->at(CURTAIN_ANI_MID)->Render(x, y + i * CURTAIN_SIZE_LARGE_HEIGHT);

		animation_set->at(CURTAIN_ANI_END)->Render(x, y * (numRows - 1) * CURTAIN_SIZE_LARGE_HEIGHT);
	}
}

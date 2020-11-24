#include "Curtain.h"

CCurtain::CCurtain(int numberOfColumns, int numberOfRows, int type)
{
	background = 1;
	numColumns = numberOfColumns;
	numRows = numberOfRows;
	this->type = type;
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
	{
		for (int i = 0; i < numColumns; i++)
			animation_set->at(CURTAIN_ANI_HEADING)->Render(x + i * CURTAIN_SIZE_COLLAPSED_WIDTH, y);
	}
	else if (type == CURTAIN_TYPE_LARGE)
	{
		for (int i = 0; i < numRows; i++)
			for (int j = 0; j < numColumns; j++)
			{
				if (i < numRows - 1)
					animation_set->at(CURTAIN_ANI_MID)->Render(x + j * CURTAIN_SIZE_LARGE_WIDTH, y + i * CURTAIN_SIZE_LARGE_HEIGHT);
				else
					animation_set->at(CURTAIN_ANI_END)->Render(x + j * CURTAIN_SIZE_LARGE_WIDTH, y + i * CURTAIN_SIZE_LARGE_HEIGHT);
			}
	}
}

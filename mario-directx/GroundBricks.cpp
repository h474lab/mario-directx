#include "GroundBricks.h"

void CGroundBricks::Render()
{
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numColumns; j++)
		{
			if (i == 0)
			{
				if (j == 0)
					animation_set->at(BRICK_ANI_TOPLEFT)->Render(x + j * BRICK_BBOX_WIDTH, y);
				else if (j == numColumns - 1)
					animation_set->at(BRICK_ANI_TOPRIGHT)->Render(x + j * BRICK_BBOX_WIDTH, y);
				else
					animation_set->at(BRICK_ANI_TOPMID)->Render(x + j * BRICK_BBOX_WIDTH, y);
			}
			else if (i == numRows - 1)
			{
				if (j == 0)
					animation_set->at(BRICK_ANI_BOTLEFT)->Render(x + j * BRICK_BBOX_WIDTH, y + i * BRICK_BBOX_HEIGHT);
				else if (j == numColumns - 1)
					animation_set->at(BRICK_ANI_BOTRIGHT)->Render(x + j * BRICK_BBOX_WIDTH, y + i * BRICK_BBOX_HEIGHT);
				else
					animation_set->at(BRICK_ANI_BOTMID)->Render(x + j * BRICK_BBOX_WIDTH, y + i * BRICK_BBOX_HEIGHT);
			}
		}
}

void CGroundBricks::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BRICK_BBOX_WIDTH * numColumns;
	b = t + BRICK_BBOX_HEIGHT * numRows;
}

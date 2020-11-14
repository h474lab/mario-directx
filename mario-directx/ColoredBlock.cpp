#include "ColoredBlock.h"

void CColoredBlock::Render()
{
	int cellWidth = COLORED_BLOCK_CELL_WIDTH;
	int cellHeight = COLORED_BLOCK_CELL_HEIGHT;

	float lastX = x + cellWidth * (numColumns - 1);
	float lastY = y + cellHeight * (numRows - 1);

	animation_set->at(COLORED_BLOCK_ANI_TOP_LEFT)->Render(x, y);
	animation_set->at(COLORED_BLOCK_ANI_TOP_RIGHT)->Render(lastX, y);
	animation_set->at(COLORED_BLOCK_ANI_BOT_LEFT)->Render(x, lastY);
	animation_set->at(COLORED_BLOCK_ANI_BOT_RIGHT)->Render(lastX, lastY);

	for (float i = x + cellWidth; i < lastX; i += cellWidth)
	{
		animation_set->at(COLORED_BLOCK_ANI_TOP_MID)->Render(i, y);
		animation_set->at(COLORED_BLOCK_ANI_BOT_MID)->Render(i, lastY);
		for (float j = y + cellHeight; j < lastY; j += cellHeight)
			animation_set->at(COLORED_BLOCK_ANI_MID_MID)->Render(i, j);
	}

	for (float i = y + cellHeight; i < lastY; i += cellHeight)
	{
		animation_set->at(COLORED_BLOCK_ANI_MID_LEFT)->Render(x, i);
		animation_set->at(COLORED_BLOCK_ANI_MID_RIGHT)->Render(lastX, i);
	}

	RenderShadow();
}

void CColoredBlock::RenderShadow()
{
	int width = BRICK_SHADOW_WIDTH;
	int height = BRICK_SHADOW_HEIGHT;

	float bRight = x + numColumns * COLORED_BLOCK_CELL_WIDTH;
	float bBottom = y + numRows * COLORED_BLOCK_CELL_HEIGHT;

	float startX = x + width;
	float startY = y + height;

	//float endX = bRight + width;
	//float endY = bBottom + height;

	animation_set->at(BRICK_SHADOW_TOP)->Render(bRight, startY);
	animation_set->at(BRICK_SHADOW_LEFT)->Render(startX, bBottom);
	animation_set->at(BRICK_SHADOW_RIGHT)->Render(bRight, bBottom);

	for (float i = startX + width; i < bRight; i += width)
		animation_set->at(BRICK_SHADOW_MID)->Render(i, bBottom);

	for (float i = startY + height; i < bBottom; i += height)
		animation_set->at(BRICK_SHADOW_MID)->Render(bRight, i);
}

void CColoredBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + numColumns * COLORED_BLOCK_CELL_WIDTH;
	b = y + numRows * COLORED_BLOCK_CELL_HEIGHT;
}

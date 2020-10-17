#include "ColoredBlock.h"

void CColoredBlock::Render()
{
	float cellWidth = COLORED_BLOCK_CELL_WIDTH;
	float cellHeight = COLORED_BLOCK_CELL_HEIGHT;

	float lastX = x + cellWidth * (numColumns - 1);
	float lastY = y + cellHeight * (numRows - 1);

	animation_set->at(COLORED_BLOCK_ANI_TOP_LEFT)->Render(x, y);
	animation_set->at(COLORED_BLOCK_ANI_TOP_RIGHT)->Render(lastX, y);
	animation_set->at(COLORED_BLOCK_ANI_BOT_LEFT)->Render(x, lastY);
	animation_set->at(COLORED_BLOCK_ANI_BOT_RIGHT)->Render(lastX, lastY);

	for (int i = x + cellWidth; i < lastX; i += cellWidth)
	{
		animation_set->at(COLORED_BLOCK_ANI_TOP_MID)->Render(i, y);
		animation_set->at(COLORED_BLOCK_ANI_BOT_MID)->Render(i, lastY);
		for (int j = y + cellHeight; j < lastY; j += cellHeight)
			animation_set->at(COLORED_BLOCK_ANI_MID_MID)->Render(i, j);
	}

	for (int i = y + cellHeight; i < lastY; i += cellHeight)
	{
		animation_set->at(COLORED_BLOCK_ANI_MID_LEFT)->Render(x, i);
		animation_set->at(COLORED_BLOCK_ANI_MID_RIGHT)->Render(lastX, i);
	}

	//RenderShadow();
}

void CColoredBlock::RenderShadow()
{
	float width = BRICK_SHADOW_WIDTH;
	float height = BRICK_SHADOW_HEIGHT;

	float bRight = x + 16 * COLORED_BLOCK_CELL_WIDTH;
	float bBottom = y + 16 * COLORED_BLOCK_CELL_HEIGHT;

	float startX = x + width;
	float startY = y + height;

	//float endX = bRight + width;
	//float endY = bBottom + height;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	if (!animation_sets) return;

	LPANIMATION_SET ani_set = animation_sets->Get(BRICK_SHADOW_ANI_ID);

	ani_set->at(BRICK_SHADOW_TOP)->Render(bRight, startY);
	ani_set->at(BRICK_SHADOW_LEFT)->Render(startX, bBottom);
	ani_set->at(BRICK_SHADOW_RIGHT)->Render(bRight, bBottom);

	for (int i = startX; i < bRight; i += width)
		ani_set->at(BRICK_SHADOW_MID)->Render(i, bBottom);

	for (int i = startY; i < bBottom; i += height)
		ani_set->at(BRICK_SHADOW_MID)->Render(bRight, i);

	CAnimationSets::SetInstance(NULL);
}

void CColoredBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}

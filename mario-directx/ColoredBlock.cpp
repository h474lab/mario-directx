#include "ColoredBlock.h"

CColoredBlock::CColoredBlock(int type)
{
	background = 0;
	this->type = type;
}

int CColoredBlock::IsTop()
{
	if (type == COLORED_BLOCK_TYPE_TOP_LEFT || type == COLORED_BLOCK_TYPE_TOP_MID || type == COLORED_BLOCK_TYPE_TOP_RIGHT)
		return 1;
	return 0;
}

int CColoredBlock::IsEdge()
{
	if (type == COLORED_BLOCK_TYPE_TOP_LEFT || type == COLORED_BLOCK_TYPE_BOT_LEFT)
		return COLORED_CELL_LEFT_EDGE;
	else if (type == COLORED_BLOCK_TYPE_TOP_RIGHT || type == COLORED_BLOCK_TYPE_BOT_RIGHT)
		return COLORED_CELL_RIGHT_EDGE;
	return 0;
}

void CColoredBlock::Render()
{
	switch (type)
	{
	case COLORED_BLOCK_TYPE_TOP_LEFT:
		animation_set->at(COLORED_BLOCK_ANI_TOP_LEFT)->Render(x, y);
		break;
	case COLORED_BLOCK_TYPE_TOP_MID:
		animation_set->at(COLORED_BLOCK_ANI_TOP_MID)->Render(x, y);
		break;
	case COLORED_BLOCK_TYPE_TOP_RIGHT:
		animation_set->at(COLORED_BLOCK_ANI_TOP_RIGHT)->Render(x, y);
		break;
	case COLORED_BLOCK_TYPE_MID_LEFT:
		animation_set->at(COLORED_BLOCK_ANI_MID_LEFT)->Render(x, y);
		break;
	case COLORED_BLOCK_TYPE_MID_MID:
		animation_set->at(COLORED_BLOCK_ANI_MID_MID)->Render(x, y);
		break;
	case COLORED_BLOCK_TYPE_MID_RIGHT:
		animation_set->at(COLORED_BLOCK_ANI_MID_RIGHT)->Render(x, y);
		break;
	case COLORED_BLOCK_TYPE_BOT_LEFT:
		animation_set->at(COLORED_BLOCK_ANI_BOT_LEFT)->Render(x, y);
		break;
	case COLORED_BLOCK_TYPE_BOT_MID:
		animation_set->at(COLORED_BLOCK_ANI_BOT_MID)->Render(x, y);
		break;
	case COLORED_BLOCK_TYPE_BOT_RIGHT:
		animation_set->at(COLORED_BLOCK_ANI_BOT_RIGHT)->Render(x, y);
		break;
	}

	RenderShadow();
}

void CColoredBlock::RenderShadow()
{
	switch (type)
	{
	case COLORED_BLOCK_TYPE_BOT_LEFT:
		animation_set->at(BRICK_SHADOW_LEFT)->Render(x + BRICK_SHADOW_WIDTH, y + COLORED_BLOCK_CELL_HEIGHT);
		break;
	case COLORED_BLOCK_TYPE_BOT_MID:
		animation_set->at(BRICK_SHADOW_MID)->Render(x, y + COLORED_BLOCK_CELL_HEIGHT);
		animation_set->at(BRICK_SHADOW_MID)->Render(x + BRICK_SHADOW_WIDTH, y + COLORED_BLOCK_CELL_HEIGHT);
		break;
	case COLORED_BLOCK_TYPE_TOP_RIGHT:
		animation_set->at(BRICK_SHADOW_TOP)->Render(x + COLORED_BLOCK_CELL_WIDTH, y + BRICK_SHADOW_HEIGHT);
		break;
	case COLORED_BLOCK_TYPE_MID_RIGHT:
		animation_set->at(BRICK_SHADOW_MID)->Render(x + COLORED_BLOCK_CELL_WIDTH, y);
		animation_set->at(BRICK_SHADOW_MID)->Render(x + COLORED_BLOCK_CELL_WIDTH, y + BRICK_SHADOW_HEIGHT);
		break;
	case COLORED_BLOCK_TYPE_BOT_RIGHT:
		animation_set->at(BRICK_SHADOW_MID)->Render(x, y + COLORED_BLOCK_CELL_HEIGHT);
		animation_set->at(BRICK_SHADOW_MID)->Render(x + BRICK_SHADOW_WIDTH, y + COLORED_BLOCK_CELL_HEIGHT);
		animation_set->at(BRICK_SHADOW_MID)->Render(x + COLORED_BLOCK_CELL_WIDTH, y);
		animation_set->at(BRICK_SHADOW_MID)->Render(x + COLORED_BLOCK_CELL_WIDTH, y + BRICK_SHADOW_HEIGHT);
		animation_set->at(BRICK_SHADOW_RIGHT)->Render(x + COLORED_BLOCK_CELL_WIDTH, y + COLORED_BLOCK_CELL_HEIGHT);
	}
}

void CColoredBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COLORED_BLOCK_CELL_WIDTH;
	b = y + COLORED_BLOCK_CELL_HEIGHT;
}

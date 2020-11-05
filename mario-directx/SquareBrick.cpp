#include "SquareBrick.h"

void CSquareBrick::Destroy()
{
	background = 1;
	SetState(SQUARE_BRICK_STATE_UNAVAILABLE);
}

void CSquareBrick::Render()
{
	if (state == SQUARE_BRICK_STATE_AVAILABLE)
		animation_set->at(0)->Render(x, y);
}

void CSquareBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == SQUARE_BRICK_STATE_UNAVAILABLE) return;
	l = x;
	t = y;
	r = l + SQUARE_BRICK_BBOX_WIDTH;
	b = t + SQUARE_BRICK_BBOX_HEIGHT;
}

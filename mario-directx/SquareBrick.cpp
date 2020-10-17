#include "SquareBrick.h"

void CSquareBrick::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CSquareBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + SQUARE_BRICK_BBOX_WIDTH;
	b = t + SQUARE_BRICK_BBOX_HEIGHT;
}

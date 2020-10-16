#include "Background.h"

void CBackground::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CBackground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BACKGROUND_WIDTH;
	b = t + BACKGROUND_HEIGHT;
}

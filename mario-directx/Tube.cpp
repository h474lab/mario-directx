#include "Tube.h"

void CTube::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CTube::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + TUBE_CELL_WIDTH;
	b = t + TUBE_CELL_HEIGHT;
}

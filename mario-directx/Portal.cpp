#include "Portal.h"


CPortal::CPortal(float l, float t, float r, float b, int scene_id )
{
	this->scene_id = scene_id;

	background = 0;

	x = l; 
	y = t;
	width = r - l + 1.0f;
	height = b - t + 1.0f;
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
 	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
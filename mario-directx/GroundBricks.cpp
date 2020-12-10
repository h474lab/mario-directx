#include "GroundBricks.h"

CGroundBricks::CGroundBricks(int position)
{
	background = 0;
	renderScore = RENDER_SCORE_GROUNDBRICK;
	this->position = position;
}

void CGroundBricks::Render()
{
	int ani = -1;
	switch (position)
	{
	case BRICK_POSITION_TOPLEFT:
		ani = BRICK_ANI_TOPLEFT;
		break;
	case BRICK_POSITION_TOPMID:
		ani = BRICK_ANI_TOPMID;
		break;
	case BRICK_POSITION_TOPRIGHT:
		ani = BRICK_ANI_TOPRIGHT;
		break;
	case BRICK_POSITION_BOTLEFT:
		ani = BRICK_ANI_BOTLEFT;
		break;
	case BRICK_POSITION_BOTMID:
		ani = BRICK_ANI_BOTMID;
		break;
	case BRICK_POSITION_BOTRIGHT:
		ani = BRICK_ANI_BOTRIGHT;
		break;
	}

	if (ani != -1) animation_set->at(ani)->Render(x, y);
}

void CGroundBricks::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

#include "QuestionBrick.h"

void CQuestionBrick::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + QUESTIONBRICK_BBOX_WIDTH;
	b = t + QUESTIONBRICK_BBOX_HEIGHT;
}

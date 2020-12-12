#include "IntroTree.h"

CIntroTree::CIntroTree(int type)
{
	this->type = type;
	background = 1;
}

void CIntroTree::Render()
{
	if (state == TREE_STATE_UNAVAILABLE) return;
	if (type == TREE_TYPE_SHORT)
		animation_set->at(TREE_ANI_SHORT)->Render(x, y);
	else
		animation_set->at(TREE_ANI_HIGH)->Render(x, y);
}

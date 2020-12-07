#include "GameOverBox.h"

CGameOverBox::CGameOverBox()
{
	background = 0;
	SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_GAME_OVER_BOX));

	state = BOX_STATE_DISAPPEAR;
	focusingOption = 0;
}

void CGameOverBox::SwitchOption()
{
	if (focusingOption == BOX_FOCUS_OPTION_1)
		focusingOption = BOX_FOCUS_OPTION_2;
	else
		focusingOption = BOX_FOCUS_OPTION_1;
}

void CGameOverBox::Render()
{
	if (state == BOX_STATE_DISAPPEAR) return;

	if (focusingOption == BOX_FOCUS_OPTION_1)
		animation_set->at(BOX_ANI_FOCUS_OPTION_1)->Render(x, y);
	else
		animation_set->at(BOX_ANI_FOCUS_OPTION_2)->Render(x, y);
}

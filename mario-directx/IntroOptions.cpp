#include "IntroOptions.h"

CIntroOptions::CIntroOptions()
{
	background = 1;
	focusingOption = OPTION_1;
	SetState(OPTIONS_STATE_UNAVAILABLE);
}

void CIntroOptions::SwitchFocusingOption()
{
	if (focusingOption == OPTION_1)
		focusingOption = OPTION_2;
	else
		focusingOption = OPTION_1;
}

void CIntroOptions::Render()
{
	if (state == OPTIONS_STATE_UNAVAILABLE) return;
	if (focusingOption == OPTION_1)
		animation_set->at(OPTIONS_ANI_OPTION_1)->Render(x, y);
	else
		animation_set->at(OPTIONS_ANI_OPTION_2)->Render(x, y);
}

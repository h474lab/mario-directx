#include "IntroOptions.h"
#include "Game.h"

CIntroOptions::CIntroOptions(int sceneOption1, int sceneOption2)
{
	background = 1;
	focusingOption = OPTION_1;
	this->sceneOption1 = sceneOption1;
	this->sceneOption2 = sceneOption2;

	SetState(OPTIONS_STATE_UNAVAILABLE);
}

void CIntroOptions::SwitchFocusingOption()
{
	if (focusingOption == OPTION_1)
		focusingOption = OPTION_2;
	else
		focusingOption = OPTION_1;
}

void CIntroOptions::SwitchSceneOption()
{
	if (focusingOption == OPTION_1)
		CGame::GetInstance()->SwitchScene(sceneOption1);
	else
		CGame::GetInstance()->SwitchScene(sceneOption2);
}

void CIntroOptions::Render()
{
	if (state == OPTIONS_STATE_UNAVAILABLE) return;
	if (focusingOption == OPTION_1)
		animation_set->at(OPTIONS_ANI_OPTION_1)->Render(x, y);
	else
		animation_set->at(OPTIONS_ANI_OPTION_2)->Render(x, y);
}

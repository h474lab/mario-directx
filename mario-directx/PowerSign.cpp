#include "PowerSign.h"

CPowerSign::CPowerSign()
{
	background = 1;

	SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_POWER_LETTERS));
}

void CPowerSign::Render()
{
	CPowerObject::Render();
}

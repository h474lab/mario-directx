#include "PowerArrow.h"

CPowerArrow::CPowerArrow()
{
	background = 1;

	SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_POWER_ARROW));
}

void CPowerArrow::Render()
{
	CPowerObject::Render();
}

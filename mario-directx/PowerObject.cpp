#include "PowerObject.h"

void CPowerObject::Render()
{
	int ani = -1;
	if (state == POWER_OBJECT_STATE_ON)
		ani = POWER_OBJECT_ANI_ON;
	else
		ani = POWER_OBJECT_ANI_OFF;

	animation_set->at(ani)->Render(x, y);
}

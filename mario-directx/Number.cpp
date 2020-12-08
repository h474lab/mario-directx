#include "Number.h"
#include "Utils.h"

CNumber::CNumber()
{
	background = 1;
	SetState(NUMBER_STATE_UNAVAILABLE);
	SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_NUMBERS));
}

void CNumber::Render()
{
	if (state == NUMBER_STATE_UNAVAILABLE) return;

	int ani = -1;

	switch (currentNumber)
	{
	case 0:
		ani = NUMBER_ANI_0;
		break;
	case 1:
		ani = NUMBER_ANI_1;
		break;
	case 2:
		ani = NUMBER_ANI_2;
		break;
	case 3:
		ani = NUMBER_ANI_3;
		break;
	case 4:
		ani = NUMBER_ANI_4;
		break;
	case 5:
		ani = NUMBER_ANI_5;
		break;
	case 6:
		ani = NUMBER_ANI_6;
		break;
	case 7:
		ani = NUMBER_ANI_7;
		break;
	case 8:
		ani = NUMBER_ANI_8;
		break;
	case 9:
		ani = NUMBER_ANI_9;
		break;
	}

	if (ani != -1) animation_set->at(ani)->Render(x, y);
}

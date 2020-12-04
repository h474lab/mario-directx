#include "Card.h"

CCard::CCard()
{
	background = 1;
	SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_CARDS));
}

void CCard::Render()
{
	if (state == CARD_STATE_HIDING) return;

	int ani = 0;
	switch (state)
	{
	case CARD_STATE_BLANK:
		ani = CARD_ANI_BLANK;
		break;
	case CARD_STATE_MUSHROOM:
		ani = CARD_ANI_MUSHROOM;
		break;
	case CARD_STATE_FLOWER:
		ani = CARD_ANI_FLOWER;
		break;
	case CARD_STATE_STAR:
		ani = CARD_ANI_STAR;
		break;
	}

	animation_set->at(ani)->Render(x, y);
}

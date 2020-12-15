#include "Background.h"

CBackground::CBackground()
{
	background = 1;
	SetState(BACKGROUND_STATE_HIDE);
	card = NULL;
}

void CBackground::SetType(int type)
{
	CAnimationSets* ani_sets = CAnimationSets::GetInstance();
	switch (type)
	{
	case BACKGROUND_TYPE_END_GAME_PANEL:
		SetAnimationSet(ani_sets->GetInstance()->Get(ID_ANI_SET_END_GAME_PANEL));
		break;
	}
	this->type = type;
}

void CBackground::SetCardType(int cardType)
{
	if (card) card->SetType(cardType);
}

void CBackground::SetPosition(float x, float y)
{
	if (type == BACKGROUND_TYPE_END_GAME_PANEL)
	{
		this->x = x + END_GAME_PANEL_PADDING_LEFT;
		this->y = y + END_GAME_PANEL_PADDING_TOP;
	}
	else CGameObject::SetPosition(x, y);

	if (!card)
		card = new CCard();

	card->SetPosition(x + END_GAME_CARD_POSITION_X, y + END_GAME_CARD_POSITION_Y);
}

void CBackground::Render()
{
	if (state == BACKGROUND_STATE_HIDE) return;
	if (animation_set) animation_set->at(0)->Render(x, y);
	if (card) card->Render();
}

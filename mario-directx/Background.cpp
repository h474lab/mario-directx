#include "Background.h"

CBackground::CBackground()
{
	background = 1;
	SetState(BACKGROUND_STATE_HIDE);
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

void CBackground::SetPosition(float x, float y)
{
	if (type == BACKGROUND_TYPE_END_GAME_PANEL)
	{
		this->x = x + END_GAME_PANEL_PADDING_LEFT;
		this->y = y + END_GAME_PANEL_PADDING_TOP;
	}
	else CGameObject::SetPosition(x, y);
}

void CBackground::Render()
{
	if (state == BACKGROUND_STATE_HIDE) return;
	if (animation_set) animation_set->at(0)->Render(x, y);
}

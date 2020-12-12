#pragma once
#include "GameObject.h"

#define BOX_STATE_APPEAR		0
#define BOX_STATE_DISAPPEAR		1

#define BOX_FOCUS_OPTION_1	0
#define BOX_FOCUS_OPTION_2	1

#define BOX_ANI_FOCUS_OPTION_1	0
#define BOX_ANI_FOCUS_OPTION_2	1

class CGameOverBox : public CGameObject
{
	int focusingOption;
public:
	CGameOverBox();

	void SwitchOption();
	int GetFocusingOption() { return focusingOption; }

	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};
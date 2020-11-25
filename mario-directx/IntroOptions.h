#pragma once
#include "GameObject.h"

#define OPTIONS_STATE_UNAVAILABLE	0
#define OPTIONS_STATE_AVAILABLE		1

#define OPTIONS_ANI_OPTION_1	0
#define OPTIONS_ANI_OPTION_2	1

#define OPTION_1	0
#define OPTION_2	1

class CIntroOptions : public CGameObject
{
	int focusingOption;
	int sceneOption1, sceneOption2;
public:
	CIntroOptions(int sceneOption1, int sceneOption2);

	void SwitchFocusingOption();
	void SwitchSceneOption();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};


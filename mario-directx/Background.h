#pragma once
#include "GameObject.h"

#define BACKGROUND_STATE_HIDE	0
#define BACKGROUND_STATE_APPEAR	1

#define BACKGROUND_TYPE_END_GAME_PANEL 0

#define END_GAME_PANEL_PADDING_LEFT	48.0f
#define END_GAME_PANEL_PADDING_TOP	0.0f

class CBackground : public CGameObject
{
	int type;
public:
	CBackground();
	void SetType(int type);

	virtual void SetPosition(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { }
};
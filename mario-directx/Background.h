#pragma once
#include "GameObject.h"
#include "Card.h"

#define BACKGROUND_STATE_HIDE	0
#define BACKGROUND_STATE_APPEAR	1

#define BACKGROUND_TYPE_END_GAME_PANEL 0

#define END_GAME_PANEL_PADDING_LEFT	48.0f
#define END_GAME_PANEL_PADDING_TOP	0.0f

#define END_GAME_CARD_POSITION_X	215.0f
#define END_GAME_CARD_POSITION_Y	20.0f

class CBackground : public CGameObject
{
	int type;

	CCard* card;
public:
	CBackground();
	void SetType(int type);
	void SetCardType(int cardType);

	virtual void SetPosition(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { }
};
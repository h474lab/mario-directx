#pragma once
#include "GameObject.h"

#define CARD_ANI_BLANK		0
#define CARD_ANI_MUSHROOM	1
#define CARD_ANI_FLOWER		2
#define CARD_ANI_STAR		3

#define CARD_STATE_APPEAR	0
#define CARD_STATE_HIDING	1

#define CARD_TYPE_BLANK		0
#define CARD_TYPE_MUSHROOM	1
#define CARD_TYPE_FLOWER	2
#define CARD_TYPE_STAR		3

class CCard : public CGameObject
{
	int type;
public:
	CCard();

	void SetType(int type) { this->type = type; }
	int GetType() { return type; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};


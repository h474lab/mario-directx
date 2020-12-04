#pragma once
#include "GameObject.h"

#define CARD_ANI_BLANK		0
#define CARD_ANI_MUSHROOM	1
#define CARD_ANI_FLOWER		2
#define CARD_ANI_STAR		3

#define CARD_STATE_BLANK	0
#define CARD_STATE_MUSHROOM	1
#define CARD_STATE_FLOWER	2
#define CARD_STATE_STAR		3
#define CARD_STATE_HIDING	4

class CCard : public CGameObject
{
public:
	CCard();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};


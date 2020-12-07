#pragma once
#include "GameObject.h"

#define LETTER_STATE_APPEAR		0
#define LETTER_STATE_DISAPPEAR	1

#define LETTER_HEIGHT	7
#define LETTER_WIDTH	7

#define LETTER_NUMBER	25

class CLetter : public CGameObject
{
	// 0 -> 24 = 'A' -> 'Z'
	int letter;
public:
	CLetter();
	void SetLetter(int letter) { this->letter = letter; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};

typedef CLetter* LPLETTER;

class CLetters
{
	LPLETTER* letters;
	int numberOfLetters;
public:
	CLetters(string str);
};
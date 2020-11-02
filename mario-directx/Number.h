#pragma once
#include "GameObject.h"

#define NUMBER_WIDTH	8
#define NUMBER_HEIGHT	7

#define NUMBER_STATE_AVAILABLE		0
#define NUMBER_STATE_UNAVAILABLE	1

#define NUMBER_ANI_0	0
#define NUMBER_ANI_1	1
#define NUMBER_ANI_2	2
#define NUMBER_ANI_3	3
#define NUMBER_ANI_4	4
#define NUMBER_ANI_5	5
#define NUMBER_ANI_6	6
#define NUMBER_ANI_7	7
#define NUMBER_ANI_8	8
#define NUMBER_ANI_9	9

class CNumber : public CGameObject
{
	int currentNumber;
public:
	CNumber();

	void SetCurrentNumber(int number) { currentNumber = number; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};


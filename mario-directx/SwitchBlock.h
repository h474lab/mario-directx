#pragma once
#include "GameObject.h"

#define SWITCH_BLOCK_FLYING_SPEED_Y	0.04f
#define SWITCHING_TIME	2000

#define SWITCH_BLOCK_STATE_UNAVAILABLE	0
#define SWITCH_BLOCK_STATE_UNPRESSED	1
#define SWITCH_BLOCK_STATE_PRESSED		2

#define SWITCH_BLOCK_ANI_UNPRESSED	0
#define SWITCH_BLOCK_ANI_PRESSED	1

#define SWITCH_BLOCK_HEIGHT	15
#define SWITCH_BLOCK_WIDTH	16

class CSwitchBlock : public CGameObject
{
public:
	CSwitchBlock();
	void Switch();
	
	virtual void SetAppearingState() { SetState(SWITCH_BLOCK_STATE_UNPRESSED); }
	virtual void SetDisappearingState() { SetState(SWITCH_BLOCK_STATE_UNAVAILABLE); }
	virtual void SetPosition(float x, float y);
	virtual void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


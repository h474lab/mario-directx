#pragma once
#include "GameObject.h"
#include "SquareBrick.h"

#define SWITCH_BLOCK_FLYING_SPEED_Y	0.04f
#define SWITCHING_TIME	2000

#define SWITCH_BLOCK_STATE_UNAVAILABLE	0
#define SWITCH_BLOCK_STATE_UNPRESSED	1
#define SWITCH_BLOCK_STATE_PRESSED		2

#define SWITCH_BLOCK_ANI_UNPRESSED	0
#define SWITCH_BLOCK_ANI_PRESSED	1

#define SWITCH_BLOCK_HEIGHT	15
#define SWITCH_BLOCK_WIDTH	16

#define SWITCH_BLOCK_AREA_X		128.0f
#define SWITCH_BLOCK_AREA_Y		64.0f

class CSwitchBlock : public CGameObject
{
	// objects vector (originally contains switch block addresses) will be replaced by coins
	vector <CGameObject*> objects;
	// square bricks will be saved in savingObjects for future replacement
	vector <CGameObject*> savingObjects;
	// grid id is used to get grid containing square bricks
	int gridId;
	// when switch block is pressed
	DWORD switching_start;
	int hasBeenSwitched;
public:
	CSwitchBlock();

	void AddObject(CGameObject* object);
	void SetGridId(int id) { gridId = id; }

	void Switch();
	void SwitchBack();
	
	virtual void SetAppearingState() { SetState(SWITCH_BLOCK_STATE_UNPRESSED); }
	virtual void SetDisappearingState() { SetState(SWITCH_BLOCK_STATE_UNAVAILABLE); }
	virtual void SetPosition(float x, float y);
	virtual void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};


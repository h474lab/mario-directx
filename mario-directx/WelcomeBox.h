#pragma once
#include "GameObject.h"
#include "Number.h"
#include "MapMario.h"

#define WELCOME_BOX_APPEARING_TIME	2000

#define DEFAULT_WORLD	0
#define DEFAULT_LIVES	0

#define WELCOME_ANI_FRAME	0

#define WELCOME_BOX_STATE_APPEAR	0
#define WELCOME_BOX_STATE_DISAPPEAR	1

#define WORLD_POSITION_X	80.0f
#define WORLD_POSITION_Y	16.0f

#define LIVES_POSITION_X	96.0f
#define LIVES_POSITION_Y	40.0f

#define MARIO_POSITION_X	64.0f
#define MARIO_POSITION_Y	32.0f

class CWelcomeBox : public CGameObject
{
	CNumber* world;
	CNumber* lives[2];
	CMapMario* mario;
	float mario_starting_x, mario_starting_y;

	DWORD appearing_time;
public:
	CWelcomeBox();

	void SetWorld(int world);
	void SetLives(int lives);
	void SetMario(CMapMario* mario, float savedPosX = 0.0f, float savedPosY = 0.0f);

	virtual void SetPosition(float x, float y);

	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};
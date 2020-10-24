#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED	0.05f;
#define GOOMBA_GRAVITY			0.001f
#define GOOMBA_DEFLECT_SPEED_X	0.04f
#define GOOMBA_DEFLECT_SPEED_Y	0.3f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING_LEFT	100
#define GOOMBA_STATE_WALKING_RIGHT	200
#define GOOMBA_STATE_DIE			300
#define GOOMBA_STATE_DIE_AND_FLY	400

#define GOOMBA_CORPSE_STAYING_TIME	200

#define GOOMBA_ANI_WALKING		0
#define GOOMBA_ANI_DIE			1
#define GOOMBA_ANI_DIE_AND_FLY	2

class CGoomba : public CGameObject
{
	DWORD corpse_start;
public: 	
	CGoomba();
	void StartDying() { corpse_start = GetTickCount64(); }

	void HitGoomba(float direction);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetState(int state);
};
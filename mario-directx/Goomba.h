#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED	0.05f
#define GOOMBA_GRAVITY			0.001f
#define GOOMBA_DEFLECT_SPEED_X	0.04f
#define GOOMBA_DEFLECT_SPEED_Y	0.3f

#define GOOMBA_LOW_JUMP_SPEED_X		0.02
#define GOOMBA_LOW_JUMP_SPEED_Y		0.15
#define GOOMBA_MAXIMUM_LOW_JUMP		3

#define GOOMBA_HIGH_JUMP_SPEED_X	0.03
#define GOOMBA_HIGH_JUMP_SPEED_Y	0.3
#define GOOMBA_MAXIMUM_HIGH_JUMP	1

#define GOOMBA_WALKING_TIME			1000

#define GOOMBA_LEVEL_GOOMBA			0
#define GOOMBA_LEVEL_PARA_GOOMBA	1

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define PARA_GOOMBA_BBOX_WIDTH	20
#define PARA_GOOMBA_BBOX_HEIGHT	18

#define GOOMBA_STATE_WALKING_LEFT		100
#define GOOMBA_STATE_WALKING_RIGHT		200
#define GOOMBA_STATE_JUMPING_LOW_LEFT	300
#define GOOMBA_STATE_JUMPING_LOW_RIGHT	400
#define GOOMBA_STATE_JUMPING_HIGH_LEFT	500
#define GOOMBA_STATE_JUMPING_HIGH_RIGHT	600
#define GOOMBA_STATE_DIE				700
#define GOOMBA_STATE_DIE_AND_FLY		800

#define GOOMBA_CORPSE_STAYING_TIME		200

#define GOOMBA_ANI_WALKING				0
#define GOOMBA_ANI_DIE					1
#define GOOMBA_ANI_DIE_AND_FLY			2
#define GOOMBA_ANI_WALKING_WITH_WINGS	3
#define GOOMBA_ANI_JUMPING_LOW			4
#define GOOMBA_ANI_JUMPING_HIGH			5

class CGoomba : public CGameObject
{
	int level;
	int jumpCount;
	int jumping;

	DWORD corpse_start;
	DWORD walking_start;
public: 	
	CGoomba();

	void SetLevel(int level) { this->level = level; }

	void StartDying() { corpse_start = GetTickCount64(); }
	void StartWalking() { walking_start = GetTickCount64(); }

	void HitGoomba(float direction);
	void LevelDown();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetState(int state);
};
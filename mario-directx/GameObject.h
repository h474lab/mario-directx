#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define ID_HUD_BG	-1

#define ID_ANI_SET_SCOREBOARD		9901
#define ID_ANI_SET_CARDS			9902
#define ID_ANI_SET_POWER_ARROW		9903
#define ID_ANI_SET_POWER_LETTERS	9904
#define ID_ANI_SET_NUMBERS			9905
#define ID_ANI_SET_LETTERS			9906
#define ID_ANI_SET_SCORE			9907

#define FLYING_DIRECTION_NOMOVE		0
#define FLYING_DIRECTION_UP			1
#define FLYING_DIRECTION_DOWN		2

#define MOVING_DIRECTION_LEFT		-1
#define MOVING_DIRECTION_RIGHT		1

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	
	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
protected:
	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int background;

	int flyingDirection;	// 0 - no movement, 1 - move up, 2 - move down
	float minFlyingY, maxFlyingY;
	float flyingSpeedY;
	int disappear, movingSideAfter;
	CGameObject* waitedObj;
	int delayAfterMovingUp;
	DWORD delay_time, delay_start;

	int nx;

	int state;

	DWORD dt;

	LPANIMATION_SET animation_set;

public: 
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	virtual void Affect(int type) {}

	int GetState() { return this->state; }

	int isBackground() { return this->background; }

	void SetFlyingDirection(int direction, int side) { flyingDirection = direction; movingSideAfter = side; }
	int GetFlyingDirection() { return flyingDirection; }
	
	void StartDelayingFlying() { delay_start = (DWORD)GetTickCount64(); }

	virtual void UpdateFlying(DWORD dt);
	virtual void SetMovingDirection(int movDirection) {}
	virtual void SetDisappearingState() {}
	virtual void SetAppearingState() {}

	int CanBeHitByTail();

	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny, 
		float &rdx, 
		float &rdy);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }


	~CGameObject();
};


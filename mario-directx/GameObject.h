#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"

#include "Utils.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define ID_HUD_BG	-1

#define ID_ANI_SET_HUD_BACKGROUND	9900
#define ID_ANI_SET_SCOREBOARD		9901
#define ID_ANI_SET_CARDS			9902
#define ID_ANI_SET_POWER_ARROW		9903
#define ID_ANI_SET_POWER_LETTERS	9904
#define ID_ANI_SET_NUMBERS			9905
#define ID_ANI_SET_LETTERS			9906
#define ID_ANI_SET_SCORE			9907

#define ID_ANI_SET_GAME_OVER_BOX	9860
#define ID_ANI_SET_WELCOME_BOX		9861
#define ID_ANI_SET_STAR				9862
#define ID_ANI_SET_END_GAME_PANEL	9710

#define FLYING_DIRECTION_NOMOVE		0
#define FLYING_DIRECTION_UP			1
#define FLYING_DIRECTION_DOWN		2

#define MOVING_DIRECTION_LEFT		-1
#define MOVING_DIRECTION_RIGHT		1

#define OBJECT_TYPE_NONE			-1
#define OBJECT_TYPE_MARIO			0
#define OBJECT_TYPE_BRICK			1
#define OBJECT_TYPE_GROUNDBRICK		2
#define OBJECT_TYPE_GOOMBA			3
#define OBJECT_TYPE_KOOPA			4
#define OBJECT_TYPE_VENUS_FIRE_TRAP	5
#define OBJECT_TYPE_SHORT_FIRE_TRAP	6
#define OBJECT_TYPE_PIRANHA_PLANT	7
#define OBJECT_TYPE_COLORED_BLOCK	8
#define OBJECT_TYPE_TUBE			9
#define OBJECT_TYPE_QUESTIONBRICK	10
#define OBJECT_TYPE_SQUARE_BRICK	11
#define OBJECT_TYPE_COIN			12
#define OBJECT_TYPE_MUSHROOM		13
#define OBJECT_TYPE_LEAF			14
#define OBJECT_TYPE_BACKGROUND		15
#define OBJECT_TYPE_INTRO_CURTAIN	16
#define OBJECT_TYPE_INTRO_TITLE		17
#define OBJECT_TYPE_INTRO_OPTIONS	18
#define OBJECT_TYPE_MAP_GATE		19
#define OBJECT_TYPE_MAP_GRASS		20
#define OBJECT_TYPE_REWARD			21
#define OBJECT_TYPE_BEETLE			22
#define OBJECT_TYPE_INTRO_TREE		23
#define OBJECT_TYPE_SWITCH_BLOCK	24

#define RENDER_SCORE_COLORED_BLOCK		0
#define RENDER_SCORE_GROUNDBRICK		1
#define RENDER_SCORE_BRICK				2
#define RENDER_SCORE_VENUS_FIRE_TRAP	3
#define RENDER_SCORE_SHORT_FIRE_TRAP	4
#define RENDER_SCORE_PIRANHA_PLANT		5
#define RENDER_SCORE_TUBE				6
#define RENDER_SCORE_MUSHROOM			7
#define RENDER_SCORE_QUESTIONBRICK		8
#define RENDER_SCORE_SQUARE_BRICK		9
#define RENDER_SCORE_COIN				10
#define RENDER_SCORE_LEAF				11
#define RENDER_SCORE_REWARD				12
#define RENDER_SCORE_GOOMBA				13
#define RENDER_SCORE_KOOPA				14
#define RENDER_SCORE_FIREBALL			15
#define RENDER_SCORE_BULLET				16
#define RENDER_SCORE_BRICK_FRAGMENT		17

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

	CGameObject* nextObject, * previousObject;
	int grid_row, grid_column;

	int renderScore;
	int objectPriority;
public: 
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

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

	void SetGridPosition(int row, int column) { grid_row = row; grid_column = column; }
	void GetGridPosition(int& row, int& column) { row = grid_row, column = grid_column; }
	void SetPreviousObject(CGameObject* object) { previousObject = object; }
	CGameObject* GetPreviousObject() { return previousObject; }
	void SetNextObject(CGameObject* object) { nextObject = object; }
	CGameObject* GetNextObject() { return nextObject; }

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

	int GetRenderScore() { return renderScore; }
	void SetObjectPriority(int priority) { objectPriority = priority; }
	int GetObjectPriority() { return objectPriority; }

	~CGameObject();
};


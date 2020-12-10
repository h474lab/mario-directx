#pragma once
#include "GameObject.h"

#define STAR_ANI_ROTATING_STAR	0

#define STAR_POSITION_TOP_LEFT_EDGE		0
#define STAR_POSITION_TOP_LEFT_MID		1
#define STAR_POSITION_TOP_RIGHT_MID		2
#define STAR_POSITION_TOP_RIGHT_EDGE	3
#define STAR_POSITION_BOT_LEFT_EDGE		4
#define STAR_POSITION_BOT_LEFT_MID		5
#define STAR_POSITION_BOT_RIGHT_MID		6
#define STAR_POSITION_BOT_RIGHT_EDGE	7

#define STAR_MID_RATIO_X	0.37f
#define STAR_MID_RATIO_Y	0.63f
#define STAR_EDGE_RATIO_X	0.71f
#define STAR_EDGE_RATIO_Y	0.29f

#define STAR_CIRCLE_EXPANDING_TIME	300
#define STAR_CIRCLE_COLLAPSING_TIME	800

#define STAR_CIRCLE_EXPANDING_SPEED		0.03f
#define STAR_CIRCLE_COLLAPSING_SPEED	-0.03f

#define STAR_CIRCLE_MOVING_SPEED_X		0.8f
#define STAR_CIRCLE_MOVING_SPEED_Y		0.4f

#define STAR_CIRCLE_STATE_HIDING		0
#define STAR_CIRCLE_STATE_EXPANDING		1
#define STAR_CIRCLE_STATE_COLLAPSING	2

#define STAR_CIRCLE_DIRECTION_UP	0
#define STAR_CIRCLE_DIRECTION_DOWN	1
#define STAR_CIRCLE_DIRECTION_LEFT	2
#define STAR_CIRCLE_DIRECTION_RIGHT	3

class CStar : public CGameObject
{
	int position;
	float velocity;
public:
	CStar(int position);

	void SetVelocity(float v);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};

typedef CStar* LPSTAR;

class CStarCircle
{
	CStar* stars[8];
	float x, y;
	int state;
	DWORD timer;

	float destination_x, destination_y;
	int direction_x, direction_y;
public:
	CStarCircle(float x, float y, float des_x, float des_y);

	int GetState() { return state; }
	void SetState(int state);

	void SetPosition(float x, float y);
	void Update(DWORD dt);
	void Render();
};
#pragma once
#include "GameObject.h"

#define KOOPATROOPA_WALKING_SPEED			0.038f
#define KOOPATROOPA_ROLLING_SPEED			0.25f
#define KOOPATROOPA_GRAVITY					0.002f
#define KOOPATROOPA_PAUSING_TIME			2000

#define KOOPATROOPA_STATE_WALKING_LEFT			0
#define KOOPATROOPA_STATE_WALKING_RIGHT			1
#define KOOPATROOPA_STATE_LYING_UP				2
#define KOOPATROOPA_STATE_LYING_DOWN			3
#define KOOPATROOPA_STATE_ROLLING_UP_LEFT		4
#define KOOPATROOPA_STATE_ROLLING_UP_RIGHT		5
#define KOOPATROOPA_STATE_ROLLING_DOWN_LEFT		6
#define KOOPATROOPA_STATE_ROLLING_DOWN_RIGHT	7

#define KOOPATROOPA_ANI_WALKING_RIGHT			0
#define KOOPATROOPA_ANI_WALKING_LEFT			1
#define KOOPATROOPA_ANI_LYING_UP				2
#define KOOPATROOPA_ANI_ROLLING_UP				3
#define KOOPATROOPA_ANI_LYING_DOWN				4
#define KOOPATROOPA_ANI_ROLLING_DOWN			5

#define KOOPATROOPA_STANDING_WIDTH			16
#define KOOPATROOPA_STANDING_HEIGHT			27

#define KOOPATROOPA_LYING_WIDTH				18
#define KOOPATROOPA_LYING_HEIGHT			16

#define KOOPATROOPA_ROLLING_WIDTH			16
#define KOOPATROOPA_ROLLING_HEIGHT			16

class CKoopaTroopa : public CGameObject
{
private:
	float leftEdge, rightEdge;
	
	int isHolden;
public:
	CKoopaTroopa(float leftEdge, float rightEdge);

	virtual void SetState(int state);
	void SetHolden(int holdenState) { isHolden = holdenState; background = isHolden; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


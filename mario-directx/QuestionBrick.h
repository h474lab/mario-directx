#pragma once
#include "GameObject.h"

#define QUESTIONBRICK_STATE_CONTAINING_OBJECTS	0
#define QUESTIONBRICK_STATE_NONE_OBJECTS		1

#define QUESTIONBRICK_BBOX_WIDTH	16
#define QUESTIONBRICK_BBOX_HEIGHT	16

#define QUESTIONBRICK_ANI_CONTAINING_OBJECTS	0
#define QUESTIONBRICK_ANI_NONE_OBJECTS			1

#define MOVEMENT_SPEED_Y			0.1f

class CQuestionBrick : public CGameObject
{
	// state in which Question Brick can be hit as normal
	int unemptiable;
	// objects that included in Question Brick
	vector<CGameObject*> objects;

	float bottom_y;
public:
	CQuestionBrick();

	virtual void SetPosition(float x, float y);

	int GetUnemptiable() { return unemptiable; }
	void SetUnemptiable(int value) { unemptiable = value; }

	void AddNewObject(CGameObject* obj);
	int HitQuestionBrick(int side);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
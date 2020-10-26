#pragma once
#include "GameObject.h"

#define QUESTIONBRICK_STATE_CONTAINING_OBJECTS	0
#define QUESTIONBRICK_STATE_NONE_OBJECTS		1

#define QUESTIONBRICK_BBOX_WIDTH	16
#define QUESTIONBRICK_BBOX_HEIGHT	16

#define QUESTIONBRICK_ANI_CONTAINING_OBJECTS	0
#define QUESTIONBRICK_ANI_NONE_OBJECTS			1

#define MOVEMENT_SPEED_Y			0.25f

class CQuestionBrick : public CGameObject
{
	vector<CGameObject*> objects;
public:
	CQuestionBrick();

	virtual void SetPosition(float x, float y);

	void AddNewObject(CGameObject* obj);
	void HitQuestionBrick();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
#include <d3dx9.h>
#include <algorithm>


#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "ColoredBlock.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
		if (!coObjects->at(i)->isBackground())
		{
			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

			if (e->t > 0.0f && e->t <= 1.0f)
				coEvents.push_back(e);
			else
				delete e;
		}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny, float &rdx, float &rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < /*min_tx*/ 1.0f && c->nx != 0) {
			if (dynamic_cast<CColoredBlock*>(c->obj))
				continue;
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			coEventsResult.push_back(coEvents[i]);
		}

		if (c->t < /*min_ty*/ 1.0f  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
			coEventsResult.push_back(coEvents[i]);
		}
	}

	//DebugOut(L"\nmin_tx=%f", min_tx);
	//DebugOut(L"\nmin_ty=%f", min_ty);

	//if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]);
	//if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}


void CGameObject::UpdateFlying(DWORD dt)
{
	if (flyingDirection == FLYING_DIRECTION_UP)
	{
		SetAppearingState();
		vy = -flyingSpeedY;
		vx = 0;
		CGameObject::Update(dt);
		if (y + dy > minFlyingY)
		{
			y += dy;
		}
		else
		{
			y = minFlyingY;
			flyingDirection = FLYING_DIRECTION_DOWN;
		}
	}
	else if (flyingDirection == FLYING_DIRECTION_DOWN)
	{
		SetAppearingState();
		vy = flyingSpeedY;
		vx = 0;
		CGameObject::Update(dt);

		if (y + dy < maxFlyingY)
		{
			y += dy;
		}
		else
		{
			if (disappear == 1)
				SetDisappearingState();
			SetMovingDirection(movingSideAfter);
			y = maxFlyingY;
			vy = 0;
			flyingDirection = FLYING_DIRECTION_NOMOVE;
		}
	}
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
}


CGameObject::~CGameObject()
{

}
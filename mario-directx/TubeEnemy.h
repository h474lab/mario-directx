#pragma once
#include "GameObject.h"
#include "Bullet.h"

#define TUBE_ENEMY_STATE_POINT	0
#define TUBE_ENEMY_STATE_FIRE	1
#define TUBE_ENEMY_STATE_IDLE	2
#define TUBE_ENEMY_STATE_DIE	3

#define TUBE_ENEMY_DIRECTION_BOTTOM_LEFT	0
#define TUBE_ENEMY_DIRECTION_BOTTOM_RIGHT	1
#define TUBE_ENEMY_DIRECTION_TOP_LEFT		2
#define TUBE_ENEMY_DIRECTION_TOP_RIGHT		3

class CTubeEnemy : public CGameObject
{
protected:
	int direction;
	CGameObject* followingObject;
	CBullet* bullet;
public:
	virtual void SetPosition(float x, float y) {}
	void SetDirection(int direction) { this->direction = direction; }

	void Firing();

	virtual void SetAppearingState(int state) {}
	void SetFollowingObject(CGameObject* followingObject) { this->followingObject = followingObject; }
	void SetBullet(CBullet* bullet) { this->bullet = bullet; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
};


#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"
#include "GameObject.h"

#define SCENE_TYPE_INTRO	0
#define SCENE_TYPE_MAP		1
#define SCENE_TYPE_PLAY		2

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

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


class CScene
{
protected:
	CKeyEventHandler * key_handler;
	int id;
	LPCWSTR sceneDirectory, objectsFileName;

	vector<LPGAMEOBJECT> objects;
public: 
	CScene(int id, LPCWSTR filePath);

	CKeyEventHandler * GetKeyEventHandler() { return key_handler; }

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
};
typedef CScene * LPSCENE;


class CScenceKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence;

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene *s) :CKeyEventHandler() { scence = s; }
};
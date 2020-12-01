#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"
#include "GameObject.h"
#include "Grid.h"

#define SCENE_TYPE_INTRO	0
#define SCENE_TYPE_MAP		1
#define SCENE_TYPE_PLAY		2

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


class CScene
{
protected:
	CKeyEventHandler * key_handler;
	int id;
	LPCWSTR sceneDirectory, objectsFileName;

	vector<LPGAMEOBJECT> objects;
	virtual void ParseObjects(string line) = 0;
public: 
	CScene(int id, LPCWSTR filePath);

	CKeyEventHandler * GetKeyEventHandler() { return key_handler; }

	void LoadObjects();

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
};
typedef CScene * LPSCENE;


class CSceneKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scene;

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(CScene *s) :CKeyEventHandler() { scene = s; }
};
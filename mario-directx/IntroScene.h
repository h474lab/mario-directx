#pragma once
#include "scene.h"
#include "Game.h"
#include "IntroOptions.h"
#include "IntroTree.h"

#define CHANGE_BACKGROUND_COLOR_TIME	9000
#define MENU_APPEARING_TIME				29000

#define MARIO_FLY_JUMP_PUSHING_TIME		270

#define INTRO_TREE_RENDER_BEFORE	0
#define INTRO_TREE_RENDER_AFTER		1

#define INTRO_TITLE_POSITION_X		70.0f
#define INTRO_TITLE_POSITION_Y		48.0f

class CIntroScene : public CScene
{
protected:
	DWORD intro_start;
	int skip;

	vector<CIntroTree*> introTrees;
	int renderIntroTreeLater;

	CIntroOptions *gameModeMenu;
	DWORD mario_flyjump_timer;
	virtual void ParseObjects(string line);
public:
	CIntroScene(int id, LPCWSTR filePath, LPCWSTR objectFileName);

	CIntroOptions* GetMenu() { return gameModeMenu; }
	void SetAppearingMenu() { skip = 1; }

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};


class CIntroSceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CIntroSceneKeyHandler(CScene* s) : CSceneKeyHandler(s) {};
};
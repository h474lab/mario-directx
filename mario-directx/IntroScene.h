#pragma once
#include "scene.h"
#include "Game.h"
#include "IntroOptions.h"

#define CHANGE_BACKGROUND_COLOR_TIME	9000
#define MENU_APPEARING_TIME			9000

class CIntroScene : public CScene
{
protected:
	DWORD intro_start;
	LPCWSTR objectsFileName;

	CIntroOptions *gameModeMenu;

	virtual void ParseObjects(string line);
public:
	CIntroScene(int id, LPCWSTR filePath, LPCWSTR objectFileName);

	CIntroOptions* GetMenu() { return gameModeMenu; }
	void SetAppearingMenu() { intro_start = MENU_APPEARING_TIME; }

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
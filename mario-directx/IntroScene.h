#pragma once
#include "Scence.h"
#include "Game.h"
#include "IntroOptions.h"

#define CHANGE_BACKGROUND_COLOR_TIME	10000

class CIntroScene : public CScene
{
protected:
	DWORD intro_start;
	LPCWSTR objectsFileName;
	vector<pair<DWORD, int>> events;

	CIntroOptions *gameModeMenu;

	void ParseObjects(string line);
public:
	CIntroScene(int id, LPCWSTR filePath, LPCWSTR objectFileName);

	CIntroOptions* GetMenu() { return gameModeMenu; }

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};


class CIntroScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CIntroScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};
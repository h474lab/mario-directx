#pragma once
#include "Scence.h"
#include "Tilemap.h"

class CMapScene : public CScene
{
	LPCWSTR tiledBackgroundFileName, tilesetFileName, mapNodeList;
	int world;
public:
	CMapScene(int id, LPCWSTR filePath, LPCWSTR tilesetFileName, LPCWSTR tiledBackgroundFileName, LPCWSTR mapNodeList, int world);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};

class CMapScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CMapScenceKeyHandler(CScene* s) : CScenceKeyHandler(s) {};
};
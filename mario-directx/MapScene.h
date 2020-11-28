#pragma once
#include "Scence.h"
#include <fstream>

#include "Tilemap.h"
#include "MapNode.h"

#include "MapMario.h"

class CMapScene : public CScene
{
	int tilemapId;
	LPCWSTR mapNodeList;
	int world;

	CMapMario* CMario;
public:
	CMapScene(int id, LPCWSTR filePath, LPCWSTR mapNodeList, int world);

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
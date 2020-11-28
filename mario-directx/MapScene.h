#pragma once
#include "Scence.h"
#include <fstream>

#include "Tilemap.h"
#include "MapNode.h"

#include "MapMario.h"

class CMapScene : public CScene
{
	int tilemapId;
	int world;

	CMapMario* mario;

	virtual void ParseObjects(string line);
public:
	CMapScene(int id, LPCWSTR filePath, LPCWSTR objectList, int tilemapId, int world);

	CMapMario* GetMario() { return mario; }
	int GetWorld() { return world; }

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
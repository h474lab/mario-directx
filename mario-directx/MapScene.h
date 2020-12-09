#pragma once
#include "scene.h"
#include <fstream>

#include "Tilemap.h"
#include "MapNode.h"

#include "MapMario.h"
#include "StarCircle.h"
#include "GameOverBox.h"
#include "WelcomeBox.h"

#define CAMERA_POSITION_X	-42.0f
#define CAMERA_POSITION_Y	-10.0f

#define GAME_OVER_BOX_POSITION_X	48.0f
#define GAME_OVER_BOX_POSITION_Y	32.0f

class CMapScene : public CScene
{
	int tilemapId;
	int world;

	float start_pos_x, start_pos_y;

	CMapMario* mario;
	CStarCircle* starCircle;
	CWelcomeBox* welcomeBox;
	CGameOverBox *gameOverBox;

	virtual void ParseObjects(string line);
public:
	CMapScene(int id, LPCWSTR filePath, LPCWSTR objectList, int tilemapId, int world);

	CMapMario* GetMario() { return mario; }
	int GetWorld() { return world; }
	CGameOverBox* GetGameOverBox() { return gameOverBox; }

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};

class CMapSceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CMapSceneKeyHandler(CScene* s) : CSceneKeyHandler(s) {};
};
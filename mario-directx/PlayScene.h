#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "HUD.h"
#include "Tilemap.h"
#include "PlayZone.h"

#define GAMETIME	301000

#define GAME_PAUSING_TIME	1000

class CPlayScene: public CScene
{
protected: 
	CMario *player;					// A play scene has to have player, right?
	int tilemapId;
	int gridId;

	int currentZone;
	vector<CPlayZone> playZones;

	vector<LPGAMEOBJECT> workingCellsInGrid;

	int world;
	float tile_x, tile_y;

	int waitingZone;

	DWORD gameStartingTime;

	virtual void ParseObjects(string line);
public: 
	CPlayScene(int id, LPCWSTR filePath, int tilemapId,float tile_startX, float tile_startY, LPCWSTR objectsFileName, int gridId, int initialZone, vector<CPlayZone> playZones, int world);

	void StartGameTime() { gameStartingTime = (DWORD)GetTickCount64(); }

	void ChangePlayZone(unsigned int zoneID);
	void StartSettingCurrentZone();

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario * GetPlayer() { return player; } 

	//friend class CPlaySceneKeyHandler;
};

class CPlaySceneKeyHandler : public CSceneKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlaySceneKeyHandler(CScene *s) :CSceneKeyHandler(s) {};
};


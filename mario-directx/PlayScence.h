#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
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

	int currentZone;
	vector<CPlayZone> playZones;

	int world;
	float tile_x, tile_y;

	int waitingZone;

	DWORD gameStartingTime;

	void ParseObjects(string line);
	
public: 
	CPlayScene(int id, LPCWSTR filePath, int tilemapId,float tile_startX, float tile_startY, LPCWSTR objectsFileName, int initialZone, vector<CPlayZone> playZones, int world);

	void StartGameTime() { gameStartingTime = (DWORD)GetTickCount64(); }

	void ChangePlayZone(int zoneID);
	void StartSettingCurrentZone();

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario * GetPlayer() { return player; } 

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};


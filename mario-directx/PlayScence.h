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
	CHUD* HUD;

	LPCWSTR tilesetFileName, tiledBackgroundFileName, objectsFileName;

	int currentZone;
	vector<CPlayZone> playZones;

	int world;

	vector<LPGAMEOBJECT> objects;

	CTilemap* tiled_background;
	float tile_x, tile_y;

	DWORD gameStartingTime;

	void _ParseObjects(string line);
	
public: 
	CPlayScene(int id, LPCWSTR filePath, LPCWSTR tilesetFileName, LPCWSTR tiledBackgroundFileName, float tile_startX, float tile_startY, LPCWSTR objectsFileName, int initialZone, vector<CPlayZone> playZones, int world);

	void StartGameTime() { gameStartingTime = (DWORD)GetTickCount64(); }

	void ChangePlayZone(int zoneID);

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


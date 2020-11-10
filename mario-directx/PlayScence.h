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

#define GAMETIME	301000

#define GAME_PAUSING_TIME	1000

class CPlayScene: public CScene
{
protected: 
	CMario *player;					// A play scene has to have player, right? 
	CHUD* HUD;

	vector<LPGAMEOBJECT> objects;
	CTilemap* tiled_background;

	DWORD gameStartingTime;

	void _ParseObjects(string line);
	
public: 
	CPlayScene(int id, LPCWSTR filePath, int minPixelWidth, int maxPixelWidth, int minPixelHeight, int maxPixelHeight, int world);

	void StartGameTime() { gameStartingTime = GetTickCount64(); }

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


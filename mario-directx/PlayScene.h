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
#include "MapScene.h"
#include "Background.h"

#define GAMETIME	301000

#define GAME_PAUSING_TIME	1000

class CPlayScene: public CScene
{
protected: 
	CMario *player;					// A play scene has to have player, right?
	// id of tilemap and grid - which are used to access tilemap and grid in their sets
	int tilemapId;
	int gridId;

	// the gate from which Mario got in!
	CMapNode* gate;
	// panel that appear to notify user that Mario has passed the level
	CBackground* endGamePanel;

	// game play zone that Mario is in
	int currentZone;
	int defaultZone;
	// a combination of play zones in the play scene
	vector<CPlayZone> playZones;

	// all cells in current grid including in the camera
	vector<LPGAMEOBJECT> workingCellsInGrid;

	// weapons will be splited and update/render seperately
	vector<LPGAMEOBJECT> weapons;

	int world;
	float tile_x, tile_y;
	
	// when Mario swich from this play zone to others, take zone (into which Mario will switch) into waiting position
	int waitingZone;

	// time has passed since the game started
	DWORD gameStartingTime;

	virtual void ParseObjects(string line);
	static bool RenderCompare(CGameObject* a, CGameObject* b);
public: 
	CPlayScene(int id, LPCWSTR filePath, int tilemapId,float tile_startX, float tile_startY, LPCWSTR objectsFileName, int gridId, int initialZone, vector<CPlayZone> playZones, int world);

	void StartGameTime() { gameStartingTime = (DWORD)GetTickCount64(); }

	void ChangePlayZone(unsigned int zoneID, float mario_switch_x, float mario_switch_y);
	void StartSettingCurrentZone();

	void SetGate(CMapNode* gate) { this->gate = gate; }

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario * GetPlayer() { return player; }
};

class CPlaySceneKeyHandler : public CSceneKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlaySceneKeyHandler(CScene *s) :CSceneKeyHandler(s) {};
};


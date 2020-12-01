#pragma once

#include <unordered_map>

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>


#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Scene.h"
#include "Mario.h"

using namespace std;

#define KEYBOARD_BUFFER_SIZE 1024

#define BACKGROUND_COLOR_INTRO_SCENE_BEFORE	D3DCOLOR_XRGB(0, 0, 0)
#define BACKGROUND_COLOR_INTRO_SCENE_AFTER	D3DCOLOR_XRGB(255, 219, 161)
#define BACKGROUND_COLOR_MAP_SCENE			D3DCOLOR_XRGB(0, 0, 0)
#define BACKGROUND_COLOR_PLAY_SCENE			D3DCOLOR_XRGB(156, 252, 240)

#define GAME_PLAY_HEIGHT	168

class CGame
{
	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;		
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;
	
	D3DCOLOR background_color;

	int screen_width;
	int screen_height; 

	CMario* player;

	unordered_map<int, LPSCENE> scenes;
	int current_scene; 

	int score;
	int lives;
	int money;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);

public:
	void InitKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	void Load(LPCWSTR gameFile);
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void SwitchScene(int scene_id);

	void ChangePlayZone(int zoneID);

	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st, 
		float sr, 
		float sb,
		float &t, 
		float &nx, 
		float &ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetPlayer(CMario* player) { this->player = player; }
	CMario* GetPlayer() { return player; }

	void SetBackgroundColor(D3DCOLOR color) { background_color = color; }
	D3DCOLOR GetBackgroundColor() { return background_color; }

	static CGame * GetInstance();

	~CGame();
};



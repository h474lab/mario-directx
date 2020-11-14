#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"

class CScene
{
protected:
	CKeyEventHandler * key_handler;
	int id;
	LPCWSTR sceneDirectory;
	LPCWSTR tilesetFileName, tiledBackgroundFileName, objectsFileName;
	int minPixelWidth, maxPixelWidth;
	int minPixelHeight, maxPixelHeight;
	int world;

public: 
	CScene(int id, LPCWSTR filePath, LPCWSTR tilesetFileName, LPCWSTR tiledBackgroundFileName, LPCWSTR objectsFileName, int minPixelWidth, int maxPixelWidth, int minPixelHeight, int maxPixelHeight, int world);

	void GetBounds(int& minPixelWidth, int& maxPixelWidth);

	CKeyEventHandler * GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
};
typedef CScene * LPSCENE;


class CScenceKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence;

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene *s) :CKeyEventHandler() { scence = s; }
};
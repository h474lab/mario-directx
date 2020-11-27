#include "MapScene.h"

void CMapScenceKeyHandler::KeyState(BYTE* states)
{
}

void CMapScenceKeyHandler::OnKeyDown(int KeyCode)
{
}

void CMapScenceKeyHandler::OnKeyUp(int KeyCode)
{
}

CMapScene::CMapScene(int id, LPCWSTR filePath, LPCWSTR tilesetFileName, LPCWSTR tiledBackgroundFileName, LPCWSTR mapNodeList, int world)
{
	this->id = id;
	this->sceneDirectory = filePath;
	this->tilesetFileName = tilesetFileName;
	this->tiledBackgroundFileName = tiledBackgroundFileName;
	this->mapNodeList = mapNodeList;
	this->world = world;

	key_handler = new CMapScenceKeyHandler(this);
}

void CMapScene::Load()
{
}

void CMapScene::Update(DWORD dt)
{
}

void CMapScene::Render()
{
}

void CMapScene::Unload()
{
}

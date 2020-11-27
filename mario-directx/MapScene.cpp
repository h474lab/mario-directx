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

CMapScene::CMapScene(int id, LPCWSTR filePath, LPCWSTR tilesetFilePath, LPCWSTR tiledBackgroundFilePath, LPCWSTR mapNodeList, int world) : CScene(id, filePath)
{
	this->tilesetFilePath = tilesetFilePath;
	this->tiledBackgroundFilePath = tiledBackgroundFilePath;
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

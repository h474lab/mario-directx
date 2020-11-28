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

CMapScene::CMapScene(int id, LPCWSTR filePath, LPCWSTR mapNodeList, int world) : CScene(id, filePath)
{
	this->mapNodeList = mapNodeList;
	this->world = world;

	key_handler = new CMapScenceKeyHandler(this);
}

void CMapScene::Load()
{
	// load tiled-background
	CTilemap* tilemap = CTilemaps::GetInstance()->Get(tilemapId);
	tilemap->LoadTiles();
	tilemap->LoadMap();
}

void CMapScene::Update(DWORD dt)
{
	
}

void CMapScene::Render()
{
	CMapNodeSets* mapNode_sets = CMapNodeSets::GetInstance();
	vector<LPMAPNODE> mapNodes = mapNode_sets->Get(world)->GetAllNodes();
	for (LPMAPNODE node : mapNodes)
	{
		node->GetNodeObject()->Render();
	}
}

void CMapScene::Unload()
{
}

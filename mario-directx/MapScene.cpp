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

CMapScene::CMapScene(int id, LPCWSTR filePath, int tilemapId, int world) : CScene(id, filePath)
{
	this->tilemapId = tilemapId;
	this->world = world;
	this->mario = new CMapMario();

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
	mario->Update(dt);
}

void CMapScene::Render()
{
	CTilemaps::GetInstance()->Get(tilemapId)->DrawFullTilemap(0, 0);

	CMapNodeSets* mapNode_sets = CMapNodeSets::GetInstance();
	vector<LPMAPNODE> mapNodes = mapNode_sets->Get(world)->GetAllNodes();
	for (LPMAPNODE node : mapNodes)
	{
		CGameObject* nodeObject = node->GetNodeObject();
		if (nodeObject) nodeObject->Render();
	}
}

void CMapScene::Unload()
{
}

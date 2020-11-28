#include "MapScene.h"

void CMapScenceKeyHandler::KeyState(BYTE* states)
{
}

void CMapScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CMapScene* mapScene = (CMapScene*)scence;
	CMapMario* mario = mapScene->GetMario();
	LPMAPNODES mapNodes = CMapNodeSets::GetInstance()->Get(mapScene->GetWorld());

	LPMAPNODE currentNode = mapNodes->GetCurrentNode();
	LPMAPNODE nextNode = NULL;

	if (mario && mario->GetState() == MAP_MARIO_STATE_IDLING)
	{
		switch (KeyCode)
		{
		case DIK_UP:
			nextNode = mapNodes->Get(currentNode->GetNode(TOP_NODE));
			break;
		case DIK_DOWN:
			nextNode = mapNodes->Get(currentNode->GetNode(BOTTOM_NODE));
			break;
		case DIK_LEFT:
			nextNode = mapNodes->Get(currentNode->GetNode(LEFT_NODE));
			break;
		case DIK_RIGHT:
			nextNode = mapNodes->Get(currentNode->GetNode(RIGHT_NODE));
			break;
		}

		if (nextNode)
		{
			mapNodes->SetCurrentNode(nextNode);
			float x, y;
			nextNode->GetPosition(x, y);
			mario->SetDestination(x, y);
			mario->SetState(MAP_MARIO_STATE_MOVING);
		}
	}
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

	mario->SetAnimationSet(CAnimationSets::GetInstance()->Get(MAP_MARIO_ANI_SET));

	float x, y;
	CMapNodeSets::GetInstance()->Get(world)->GetCurrentNode()->GetPosition(x, y);
	mario->SetPosition(x, y);

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

	mario->Render();
}

void CMapScene::Unload()
{
}

#include "MapScene.h"

#include "MapGate.h"
#include "MapGrass.h"

#include "Camera.h"
#include "HUD.h"

void CMapSceneKeyHandler::KeyState(BYTE* states)
{
}

void CMapSceneKeyHandler::OnKeyDown(int KeyCode)
{
	CMapScene* mapScene = (CMapScene*)scene;

	if (CGame::GetInstance()->GetGameState() == GAME_STATE_PLAY)
	{
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
			case DIK_RETURN:
				CGameObject* nodeObject = currentNode->GetNodeObject();
				if (nodeObject)
				{
					if (dynamic_cast<CMapGate*>(nodeObject))
					{
						CGame::GetInstance()->SwitchScene(((CMapGate*)nodeObject)->GetSceneId(), currentNode);
						scene->Unload();
					}
				}
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
	else if (CGame::GetInstance()->GetGameState() == GAME_STATE_OVER)
	{
		CGameOverBox* gameOverBox = mapScene->GetGameOverBox();
		
		switch (KeyCode)
		{
		case DIK_UP:
			gameOverBox->SwitchOption();
			break;
		case DIK_DOWN:
			gameOverBox->SwitchOption();
			break;
		}
	}
}

void CMapSceneKeyHandler::OnKeyUp(int KeyCode)
{
}

void CMapScene::ParseObjects(string line)
{
	vector<string> tokens = split(line);

	int type_id = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	int ani_set_id = atoi(tokens[3].c_str());

	int numRows, numColumns;

	CGameObject* object = NULL;

	switch (type_id)
	{
	case OBJECT_TYPE_MAP_GRASS:
		numRows = atoi(tokens[4].c_str());
		numColumns = atoi(tokens[5].c_str());
		object = new CMapGrass(numRows, numColumns);
		objects.push_back(object);
		break;
	}

	object->SetAnimationSet(CAnimationSets::GetInstance()->Get(ani_set_id));
	object->SetPosition(x, y);
}

CMapScene::CMapScene(int id, LPCWSTR filePath, LPCWSTR objectList, int tilemapId, int world) : CScene(id, filePath)
{
	this->objectsFileName = objectList;

	this->tilemapId = tilemapId;
	this->world = world;
	this->mario = new CMapMario();


	key_handler = new CMapSceneKeyHandler(this);
}

void CMapScene::Load()
{
	// load tiled-background
	CTilemap* tilemap = CTilemaps::GetInstance()->Get(tilemapId);
	tilemap->LoadTiles();
	tilemap->LoadMap();

	LoadObjects();

	mario->SetAnimationSet(CAnimationSets::GetInstance()->Get(MAP_MARIO_ANI_SET));

	this->welcomeBox = new CWelcomeBox();

	this->gameOverBox = new CGameOverBox();
	gameOverBox->SetPosition(GAME_OVER_BOX_POSITION_X, GAME_OVER_BOX_POSITION_Y);

	this->starCircle = new CStarCircle(50.0f, 50.0f);
	starCircle->SetState(STAR_CIRCLE_STATE_EXPANDING);

	float x, y;
	CMapNodeSets::GetInstance()->Get(world)->GetCurrentNode()->GetPosition(x, y);
	mario->SetPosition(x, y);
	start_pos_x = x;
	start_pos_y = y;

	CCamera::GetInstance()->SetPosition(CAMERA_POSITION_X, CAMERA_POSITION_Y);
}

void CMapScene::Update(DWORD dt)
{
	mario->Update(dt);
	CHUD* hud = CHUD::GetInstance();

	hud->SetPowerLevel(0);
	hud->SetWorld(world);
	hud->Update(dt);

	if (hud->GetLives() < 0)
		gameOverBox->SetState(BOX_STATE_APPEAR);

	if (CGame::GetInstance()->GetGameState() == GAME_STATE_WELCOME)
	{
		// show welcome box
		welcomeBox->SetState(WELCOME_BOX_STATE_APPEAR);
		// set parameters
		welcomeBox->SetWorld(world);
		welcomeBox->SetLives(CHUD::GetInstance()->GetLives());
		welcomeBox->SetMario(mario, start_pos_x, start_pos_y);
		// locate welcome box
		welcomeBox->SetPosition(GAME_OVER_BOX_POSITION_X, GAME_OVER_BOX_POSITION_Y);
	}
	welcomeBox->Update(dt);
	starCircle->Update(dt);
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

	for (LPGAMEOBJECT object : objects)
		object->Render();

	if (CGame::GetInstance()->GetGameState() != GAME_STATE_WELCOME) mario->Render();
	gameOverBox->Render();
	welcomeBox->Render();

	CHUD::GetInstance()->Render();
	starCircle->Render();
}

void CMapScene::Unload()
{
}

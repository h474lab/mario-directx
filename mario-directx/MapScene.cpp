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

	this->starCircle = NULL;
	this->welcomeBox = NULL;
	this->gameOverBox = NULL;

	key_handler = new CMapSceneKeyHandler(this);
}

void CMapScene::Load()
{
	// load tiled-background
	CTilemap* tilemap = CTilemaps::GetInstance()->Get(tilemapId);
	tilemap->LoadTiles();
	tilemap->LoadMap();

	// load object list
	LoadObjects();

	// initialize boxes
	this->welcomeBox = new CWelcomeBox();
	this->gameOverBox = new CGameOverBox();

	// set animation set for Map Mario
	mario->SetAnimationSet(CAnimationSets::GetInstance()->Get(MAP_MARIO_ANI_SET));

	// load nodes and put Mario in current node
	float x, y;
	CMapNodeSets::GetInstance()->Get(world)->GetCurrentNode()->GetPosition(x, y);
	mario->SetPosition(x, y);
	start_pos_x = x;
	start_pos_y = y;

	// set parameters for welcome box
	welcomeBox->SetWorld(world);
	welcomeBox->SetLives(CHUD::GetInstance()->GetLives());
	welcomeBox->SetMario(mario);

	// set position for game over box
	gameOverBox->SetPosition(GAME_OVER_BOX_POSITION_X, GAME_OVER_BOX_POSITION_Y);

	// if game state is "welcome"
	if (CGame::GetInstance()->GetGameState() == GAME_STATE_WELCOME)
	{
		// show welcome box
		welcomeBox->SetState(WELCOME_BOX_STATE_APPEAR);
	}

	// set camera position
	CCamera::GetInstance()->SetPosition(CAMERA_POSITION_X, CAMERA_POSITION_Y);
}

void CMapScene::Update(DWORD dt)
{
	mario->Update(dt);
	if (welcomeBox) welcomeBox->Update(dt);
	if (starCircle) starCircle->Update(dt);

	CHUD* hud = CHUD::GetInstance();

	hud->SetPowerLevel(0);
	hud->SetWorld(world);
	hud->Update(dt);

	if (hud->GetLives() < 0)
		gameOverBox->SetState(BOX_STATE_APPEAR);

	CGame* game = CGame::GetInstance();

	if (game->GetGameState() == GAME_STATE_WELCOME)
	{
		// locate welcome box
		welcomeBox->SetPosition(GAME_OVER_BOX_POSITION_X, GAME_OVER_BOX_POSITION_Y);
		// load star circle when welcome box has been disappeared
		if (welcomeBox->GetState() == WELCOME_BOX_STATE_DISAPPEAR && !starCircle)
		{
			starCircle = new CStarCircle(STAR_CIRCLE_POSITION_X, STAR_CIRCLE_POSITION_Y);
			starCircle->SetPosition(STAR_CIRCLE_POSITION_X, STAR_CIRCLE_POSITION_Y);
			starCircle->SetState(STAR_CIRCLE_STATE_EXPANDING);
		}
	}
	else if (game->GetLastGameState() == GAME_STATE_WELCOME && starCircle)
	{
		if (starCircle->GetState() == STAR_CIRCLE_STATE_HIDING)
		{
			mario->SetPosition(start_pos_x, start_pos_y);
			starCircle = NULL;
		}
	}
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
	if (gameOverBox) gameOverBox->Render();
	if (welcomeBox) welcomeBox->Render();

	CHUD::GetInstance()->Render();
	if (starCircle) starCircle->Render();
}

void CMapScene::Unload()
{
}

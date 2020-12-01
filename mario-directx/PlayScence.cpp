#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Resources.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Background.h"
#include "ColoredBlock.h"
#include "Tube.h"
#include "QuestionBrick.h"
#include "SquareBrick.h"
#include "Coin.h"
#include "Koopa.h"
#include "GroundBricks.h"
#include "Mushroom.h"
#include "VenusFireTrap.h"
#include "PiranhaPlant.h"
#include "ShortFireTrap.h"
#include "Leaf.h"
#include "Camera.h"
#include "Score.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath, int tilemapId, float tile_startX, float tile_startY, LPCWSTR objectsFileName, int gridId, int initialZone, vector<CPlayZone> playZones, int world) :
	CScene(id, filePath)
{
	this->tilemapId = tilemapId;
	this->tile_x = tile_startX;
	this->tile_y = tile_startY;

	this->objectsFileName = objectsFileName;
	this->gridId = gridId;

	currentZone = initialZone;
	this->playZones = playZones;

	this->world = world;
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::ParseObjects(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;
	CFireball* fireball = NULL;
	int nFireballs = 2;
	int fireball_ani_set;

	CGameObject* includedObj = NULL;
	vector<LPGAMEOBJECT> queuedObject;
	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		{
			fireball_ani_set = atoi(tokens[4].c_str());
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				return;
			}
			obj = new CMario(x, y);
			obj->SetPosition(x, y);
			player = (CMario*)obj;

			CGame::GetInstance()->SetPlayer(player);

			for (int i = 0; i < nFireballs; i++)
			{
				fireball = new CFireball();
				fireball->SetAnimationSet(animation_sets->Get(fireball_ani_set));
				player->AddFireball(fireball);
				queuedObject.push_back(fireball);
			}

			playZones[currentZone].GetPlayerStartPosition(x, y);

			DebugOut(L"[INFO] Player object created!\n");
			break;
		}
	case OBJECT_TYPE_GOOMBA: 
		{
			obj = new CGoomba();
			obj->SetPosition(x, y);
			dynamic_cast<CGoomba*>(obj)->SetLevel(atoi(tokens[4].c_str()));
			dynamic_cast<CGoomba*>(obj)->SetFollowingObject(player);
			break;
		}
	case OBJECT_TYPE_BRICK: 
		{
			int numRows = atoi(tokens[4].c_str());
			int numColumns = atoi(tokens[5].c_str());
			for (int i = 0; i < numRows; i++)
				for (int j = 0; j < numColumns; j++)
				{
					obj = new CBrick();
					obj->SetPosition(x + BRICK_BBOX_WIDTH * j, y + BRICK_BBOX_HEIGHT * i);
					obj->SetAnimationSet(animation_sets->Get(ani_set_id));
					obj->SetPosition(x, y);
					queuedObject.push_back(obj);
				}
			obj = NULL;
			break;
		}
	case OBJECT_TYPE_GROUNDBRICK:
		{
			int numRows = atoi(tokens[4].c_str());
			int numColumns = atoi(tokens[5].c_str());
			int position = 0;
			for (int i = 0; i < numRows; i++)
				for (int j = 0; j < numColumns; j++)
				{
					if (i == 0)
					{
						if (j == 0)
							obj = new CGroundBricks(BRICK_POSITION_TOPLEFT);
						else if (j == numColumns - 1)
							obj = new CGroundBricks(BRICK_POSITION_TOPRIGHT);
						else
							obj = new CGroundBricks(BRICK_POSITION_TOPMID);
					}
					else if (i == numRows - 1)
					{
						if (j == 0)
							obj = new CGroundBricks(BRICK_POSITION_BOTLEFT);
						else if (j == numColumns - 1)
							obj = new CGroundBricks(BRICK_POSITION_BOTRIGHT);
						else
							obj = new CGroundBricks(BRICK_POSITION_BOTMID);
					}
					obj->SetAnimationSet(animation_sets->Get(ani_set_id));
					obj->SetPosition(x + j * BRICK_BBOX_WIDTH, y + i * BRICK_BBOX_HEIGHT);
					queuedObject.push_back(obj);
				}
			obj = NULL;
			break;
		}
	case OBJECT_TYPE_COLORED_BLOCK:
		{
			int numRows = atoi(tokens[4].c_str());
			int numColumns = atoi(tokens[5].c_str());
			obj = new CColoredBlock(numRows, numColumns);
			obj->SetPosition(x, y);
			break;
		}
	case OBJECT_TYPE_TUBE:
		{
			int numRows = atoi(tokens[4].c_str());
			int lidType = atoi(tokens[5].c_str());
			int zoneID = atoi(tokens[6].c_str());
			obj = new CTube(numRows, lidType, zoneID);
			CTube* tube = dynamic_cast<CTube*>(obj);
			tube->SetFollowingObject(player);

			if (tokens.size() > 7)
			{
				int obj_type = atoi(tokens[7].c_str());
				int obj_ani_set = atoi(tokens[8].c_str());
				int bullet_ani_set;
				CBullet* bullet = NULL;

				switch (obj_type)
				{
				case OBJECT_TYPE_VENUS_FIRE_TRAP:
					includedObj = new CVenusFireTrap();
					includedObj->SetAnimationSet(animation_sets->Get(obj_ani_set));

					if (player)
						dynamic_cast<CVenusFireTrap*>(includedObj)->SetFollowingObject(player);

					bullet_ani_set = atoi(tokens[9].c_str());
					bullet = new CBullet();
					bullet->SetAnimationSet(animation_sets->Get(bullet_ani_set));
					((CVenusFireTrap*)includedObj)->SetBullet(bullet);

					queuedObject.push_back(bullet);
					break;
				case OBJECT_TYPE_SHORT_FIRE_TRAP:
					includedObj = new CShortFireTrap();
					includedObj->SetAnimationSet(animation_sets->Get(obj_ani_set));

					if (player)
						dynamic_cast<CShortFireTrap*>(includedObj)->SetFollowingObject(player);

					bullet_ani_set = atoi(tokens[9].c_str());
					bullet = new CBullet();
					bullet->SetAnimationSet(animation_sets->Get(bullet_ani_set));
					((CShortFireTrap*)includedObj)->SetBullet(bullet);

					queuedObject.push_back(bullet);
					break;
				case OBJECT_TYPE_PIRANHA_PLANT:
					includedObj = new CPiranhaPlant();
					includedObj->SetAnimationSet(animation_sets->Get(obj_ani_set));
					break;
				}

				tube->SetObject(includedObj);
			}

			if (includedObj)
			{
				queuedObject.push_back(includedObj);
				includedObj = NULL;
			}

			obj->SetPosition(x, y);
			break;
		}
	case OBJECT_TYPE_QUESTIONBRICK: 
		{
			obj = new CQuestionBrick();
			CQuestionBrick* brick = dynamic_cast<CQuestionBrick*>(obj);
			unsigned int i = 4;
			while (i < tokens.size())
			{
				
				int ani_set;
				int mushroom_level;

				switch (atoi(tokens[i].c_str()))
				{
				case OBJECT_TYPE_COIN:
					includedObj = new CCoin();
					includedObj->SetAnimationSet(animation_sets->Get(atoi(tokens[i + 1].c_str())));
					brick->AddNewObject(includedObj);
					i += 2;
					break;
				case OBJECT_TYPE_MUSHROOM:
					ani_set = atoi(tokens[i + 1].c_str());
					mushroom_level = atoi(tokens[i + 2].c_str());
					includedObj = new CMushroom(mushroom_level);
					includedObj->SetAnimationSet(animation_sets->Get(ani_set));
					dynamic_cast<CMushroom*>(includedObj)->SetContainer(obj);
					brick->AddNewObject(includedObj);
					i += 3;
					break;
				case OBJECT_TYPE_LEAF:
					ani_set = atoi(tokens[i + 1].c_str());
					includedObj = new CLeaf();
					includedObj->SetAnimationSet(animation_sets->Get(ani_set));
					brick->AddNewObject(includedObj);
					objects.push_back(includedObj);
					includedObj = NULL;
					i += 2;
					break;
				}

				if (includedObj)
				{
					queuedObject.push_back(includedObj);
					includedObj = NULL;
				}
			}

			obj->SetPosition(x, y);
			break;
		}
	case OBJECT_TYPE_SQUARE_BRICK:
		{
			obj = new CSquareBrick();
			obj->SetPosition(x, y);
			((CSquareBrick*)obj)->SetFragmentAnimationSet(animation_sets->Get(atoi(tokens[4].c_str())));
			break;
		}
	case OBJECT_TYPE_COIN:
		{
			obj = new CCoin();
			obj->SetPosition(x, y);
			break;
		}
	case OBJECT_TYPE_KOOPA:
		{
			obj = new CKoopa();
			obj->SetPosition(x, y);
			dynamic_cast<CKoopa*>(obj)->SetLevel(atoi(tokens[4].c_str()));
			break;
		}
	case OBJECT_TYPE_BACKGROUND:
		{
			obj = new CBackground();
			obj->SetPosition(x, y);
			break;
		}
	case OBJECT_TYPE_PORTAL:
		{	
			float r = (float)atof(tokens[4].c_str());
			float b = (float)atof(tokens[5].c_str());
			int scene_id = atoi(tokens[6].c_str());
			obj = new CPortal(x, y, r, b, scene_id);
			obj->SetPosition(x, y);
			break;
		}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	if (obj)
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
	}

	if (!queuedObject.empty())
	{
		for (LPGAMEOBJECT object : queuedObject) objects.push_back(object);
	}
}

void CPlayScene::ChangePlayZone(int zoneID)
{
	if (zoneID >= playZones.size())
	{
		DebugOut(L"[INFO] Cannot switch to Zone %d!\n", zoneID);
		return;
	}
	if (playZones[currentZone].GetAllowSavingPosition())
	{
		float x, y;
		float l, t, r, b;
		player->SetSittingState(0);
		player->GetPosition(x, y);
		player->GetBoundingBox(l, t, r, b);
		playZones[currentZone].SetPlayerStartPosition(x, y);
	}
	waitingZone = zoneID;
}

void CPlayScene::StartSettingCurrentZone()
{
	if (waitingZone == -1) return;

	currentZone = waitingZone;

	float x, y;
	playZones[currentZone].GetPlayerStartPosition(x, y);
	player->SetPosition(x, y);
	player->SetAllowSwitchingZone(0);

	waitingZone = -1;
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneDirectory);

	// load background
	CTilemaps* tiled_background = CTilemaps::GetInstance();
	LPTILEMAP tilemap = tiled_background->Get(tilemapId);
	tiled_background->Get(tilemapId)->LoadTiles();
	tiled_background->Get(tilemapId)->LoadMap();

	// load map
	LoadObjects();
	for (int i = 0; i < objects.size(); i++)
		CGrids::GetInstance()->Get(gridId)->AddObject(objects[i]);

	//CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\Textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	//CTextures::GetInstance()->Add(ID_HUD_BG, L"Resources\\Textures\\black-bg.png", D3DCOLOR_XRGB(255, 255, 255));
	
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneDirectory);

	StartGameTime();
}

void CPlayScene::Update(DWORD dt)
{
	workingCellsInGrid = CGrids::GetInstance()->Get(gridId)->LoadCellsWithinCamera();

	vector<LPGAMEOBJECT> coObjects;
	for (LPGAMEOBJECT workingCell : workingCellsInGrid)
	{
		LPGAMEOBJECT currentObject = workingCell;
		while (currentObject)
		{
			coObjects.push_back(currentObject);
			currentObject = currentObject->GetNextObject();
		}
	}

	player->Update(dt, &coObjects);
	player->GetHittableTail();

	//DebugOut(L"\nHittable Tail: %d", player->GetHittableTail());

	for (LPGAMEOBJECT workingCell : workingCellsInGrid)
	{
		LPGAMEOBJECT currentObject = workingCell;
		while (currentObject)
		{
			currentObject->Update(dt, &coObjects);
			currentObject = currentObject->GetNextObject();
		}
	}

	/*for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
		objects[i]->Update(dt, &coObjects);*/

	// update score animations
	CScores::GetInstance()->Update(dt);

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	if (player->GetAllowSwitchingZone())
		StartSettingCurrentZone();

	// get current zone's active area
	float minPixelWidth, maxPixelWidth;
	playZones[currentZone].GetHorizontalBounds(minPixelWidth, maxPixelWidth);
	float minPixelHeight, maxPixelHeight;
	playZones[currentZone].GetVerticalBounds(minPixelHeight, maxPixelHeight);

	// Reposition mario if needed
	float px, py;
	player->GetPosition(px, py);

	// set camera position
	float pLeft, pTop, pRight, pBottom;
	player->GetBoundingBox(pLeft, pTop, pRight, pBottom);
	float pWidth = pRight - pLeft;

	if (px < minPixelWidth) px = minPixelWidth;
	else if (px > maxPixelWidth - pWidth) px = maxPixelWidth - pWidth;

	if (py < minPixelHeight) py = minPixelHeight;

	player->SetPosition(px, py);

	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	int screenWidth = game->GetScreenWidth();
	int screenHeight = game->GetScreenHeight();

	cx -= screenWidth / 2;
	cy -= screenHeight / 2;

	if (cx < minPixelWidth) cx = minPixelWidth;
	else if (cx > maxPixelWidth - screenWidth) cx = maxPixelWidth - screenWidth;

	if (cy > maxPixelHeight - screenHeight) cy = maxPixelHeight - screenHeight;
	else if (cy < minPixelHeight) cy = minPixelHeight;

	cy = (cy + (game->GetScreenHeight() - GAME_PLAY_HEIGHT));

	CCamera* camera = CCamera::GetInstance();
	camera->SetPosition((float)((int)cx), (float)((int)cy));
	
	// set parameters for HUD
	float HUD_x, HUD_y;
	camera->GetPosition(HUD_x, HUD_y);
	HUD_y += GAME_PLAY_HEIGHT;

	CHUD *HUD = CHUD::GetInstance();

	HUD->Update(dt);
	HUD->SetPowerLevel(player->GetPowerLevel());
	HUD->SetWorld(this->world);
	HUD->SetRemainingTime((int)(GAMETIME - (GetTickCount64() - gameStartingTime)) / 1000);
}

void CPlayScene::Render()
{
	float cx, cy;
	CCamera::GetInstance()->GetPosition(cx, cy);

	float topBound, bottomBound, leftBound, rightBound;
	playZones[currentZone].GetVerticalBounds(topBound, bottomBound);
	playZones[currentZone].GetHorizontalBounds(leftBound, rightBound);

	float screen_width = CGame::GetInstance()->GetScreenWidth();
	float screen_height = CGame::GetInstance()->GetScreenHeight();

	CTilemaps::GetInstance()->Get(tilemapId)->DrawFullTilemap(tile_x, tile_y, cx, cy, (cx + screen_width < rightBound) ? cx + screen_width : rightBound, (cy + screen_height < bottomBound) ? cy + screen_height : bottomBound);

	for (LPGAMEOBJECT workingCell : workingCellsInGrid)
	{
		LPGAMEOBJECT currentObject = workingCell;
		while (currentObject)
		{
			currentObject->Render();
			currentObject = currentObject->GetNextObject();
		}
	}
	player->Render();

	/*for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();*/

	// render score animation
	CScores::GetInstance()->Render();

	CHUD::GetInstance()->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (unsigned int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneDirectory);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_X:
		if (mario->IsJumping())
			mario->FlyJump();
		else
			mario->SetJumpingUp(1);
		break;
	case DIK_Z:
		mario->StartSpinning();
		mario->SetThrowing();
		break;
	case DIK_A: 
		mario->Reset();
		break;
	case DIK_S:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_B:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_T:
		mario->SetLevel(MARIO_LEVEL_TAIL);
		break;
	case DIK_F:
		mario->SetLevel(MARIO_LEVEL_FIRE);
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	mario->SetJumpingUp(0);
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;

	if (game->IsKeyDown(DIK_X) && mario->GetJumpingUp())
		mario->SetState(MARIO_STATE_JUMPING);

	int skillButtonPressed = 0;
	if (game->IsKeyDown(DIK_Z))
		skillButtonPressed = 1;

	if (game->IsKeyDown(DIK_DOWN))
	{
		mario->SetSittingState(1);
		mario->SetReadyDown(1);
	}
	else
	{
		mario->SetSittingState(0);
		mario->SetReadyDown(0);
	}

	if (game->IsKeyDown(DIK_UP)) mario->SetReadyUp(1);
	else mario->SetReadyUp(0);

	if (game->IsKeyDown(DIK_RIGHT))
	{
		mario->SetMovingRight(skillButtonPressed);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		mario->SetMovingLeft(skillButtonPressed);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}
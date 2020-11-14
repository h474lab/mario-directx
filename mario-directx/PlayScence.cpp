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

using namespace std;

#define OBJECT_TYPE_MARIO			0
#define OBJECT_TYPE_BRICK			1
#define OBJECT_TYPE_GROUNDBRICK		2
#define OBJECT_TYPE_GOOMBA			3
#define OBJECT_TYPE_KOOPA			4
#define OBJECT_TYPE_VENUS_FIRE_TRAP	5
#define OBJECT_TYPE_SHORT_FIRE_TRAP	6
#define OBJECT_TYPE_PIRANHA_PLANT	7
#define OBJECT_TYPE_COLORED_BLOCK	8
#define OBJECT_TYPE_TUBE			9
#define OBJECT_TYPE_QUESTIONBRICK	10
#define OBJECT_TYPE_SQUARE_BRICK	11
#define OBJECT_TYPE_COIN			12
#define OBJECT_TYPE_MUSHROOM		13
#define OBJECT_TYPE_LEAF			14
#define OBJECT_TYPE_BACKGROUND		15

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

CPlayScene::CPlayScene(int id, LPCWSTR filePath, LPCWSTR tilesetFileName, LPCWSTR tiledBackgroundFileName, float tile_startX, float tile_startY, LPCWSTR objectsFileName, int initialZone, vector<CPlayZone> playZones, int world) :
	CScene(id, filePath)
{
	this->tilesetFileName = tilesetFileName;
	this->tiledBackgroundFileName = tiledBackgroundFileName;
	this->tile_x = tile_startX;
	this->tile_y = tile_startY;

	this->objectsFileName = objectsFileName;

	currentZone = initialZone;
	this->playZones = playZones;

	this->world = world;
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseObjects(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;
	CFireball* fireball = NULL;
	int nFireballs = 2;
	int fireball_ani_set;

	CGameObject* includedObj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		fireball_ani_set = atoi(tokens[4].c_str());
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;

		CGame::GetInstance()->SetPlayer(player);

		for (int i = 0; i < nFireballs; i++)
		{
			fireball = new CFireball();
			fireball->SetAnimationSet(animation_sets->Get(fireball_ani_set));
			player->AddFireball(fireball);
			objects.push_back(fireball);
		}

		playZones[currentZone].GetPlayerStartPosition(x, y);

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: 
	{
		obj = new CGoomba();
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
				objects.push_back(obj);
			}
		return;
	}
	case OBJECT_TYPE_GROUNDBRICK:
	{
		int numRows = atoi(tokens[4].c_str());
		int numColumns = atoi(tokens[5].c_str());
		obj = new CGroundBricks(numRows, numColumns);
		break;
	}
	case OBJECT_TYPE_COLORED_BLOCK:
		{
			int numRows = atoi(tokens[4].c_str());
			int numColumns = atoi(tokens[5].c_str());
			obj = new CColoredBlock(numRows, numColumns);
			break;
		}
	case OBJECT_TYPE_TUBE:
		{
			int numRows = atoi(tokens[4].c_str());
			int hasLid = atoi(tokens[5].c_str());
			obj = new CTube(numRows, hasLid);
			CTube* tube = dynamic_cast<CTube*>(obj);

			if (tokens.size() > 6)
			{
				int obj_type = atoi(tokens[6].c_str());
				int obj_ani_set = atoi(tokens[7].c_str());
				int bullet_ani_set;
				CBullet* bullet = NULL;

				switch (obj_type)
				{
				case OBJECT_TYPE_VENUS_FIRE_TRAP:
					includedObj = new CVenusFireTrap();
					includedObj->SetAnimationSet(animation_sets->Get(obj_ani_set));

					if (player)
						dynamic_cast<CVenusFireTrap*>(includedObj)->SetFollowingObject(player);

					bullet_ani_set = atoi(tokens[8].c_str());
					bullet = new CBullet();
					bullet->SetAnimationSet(animation_sets->Get(bullet_ani_set));
					dynamic_cast<CVenusFireTrap*>(includedObj)->SetBullet(bullet);

					objects.push_back(bullet);
					break;
				case OBJECT_TYPE_SHORT_FIRE_TRAP:
					includedObj = new CShortFireTrap();
					includedObj->SetAnimationSet(animation_sets->Get(obj_ani_set));

					if (player)
						dynamic_cast<CShortFireTrap*>(includedObj)->SetFollowingObject(player);

					bullet_ani_set = atoi(tokens[8].c_str());
					bullet = new CBullet();
					bullet->SetAnimationSet(animation_sets->Get(bullet_ani_set));
					dynamic_cast<CShortFireTrap*>(includedObj)->SetBullet(bullet);

					objects.push_back(bullet);
					break;
				case OBJECT_TYPE_PIRANHA_PLANT:
					includedObj = new CPiranhaPlant();
					includedObj->SetAnimationSet(animation_sets->Get(obj_ani_set));
					objects.push_back(includedObj);
					break;
				}

				tube->SetObject(includedObj);
			}

			if (includedObj)
			{
				objects.push_back(includedObj);
				includedObj = NULL;
			}
			break;
		}
	case OBJECT_TYPE_QUESTIONBRICK: 
		{
			obj = new CQuestionBrick();
			CQuestionBrick* brick = dynamic_cast<CQuestionBrick*>(obj);
			int i = 4;
			while (i < tokens.size())
			{
				
				int ani_set;
				int mushroom_level;

				switch (atoi(tokens[i].c_str()))
				{
				case OBJECT_TYPE_COIN:
					includedObj = new CCoin();
					includedObj->SetAnimationSet(
						animation_sets->Get(atoi(tokens[i + 1].c_str()))
					);

					brick->AddNewObject(includedObj);
					objects.push_back(includedObj);
					includedObj = NULL;
					i += 2;
					break;
				case OBJECT_TYPE_MUSHROOM:
					ani_set = atoi(tokens[i + 1].c_str());
					mushroom_level = atoi(tokens[i + 2].c_str());

					includedObj = new CMushroom(mushroom_level);
					includedObj->SetAnimationSet(animation_sets->Get(ani_set));
					dynamic_cast<CMushroom*>(includedObj)->SetContainer(obj);

					brick->AddNewObject(includedObj);
					objects.push_back(includedObj);
					includedObj = NULL;
					i += 3;
					break;
				case OBJECT_TYPE_LEAF:
					ani_set = atoi(tokens[i + 1].c_str());

					includedObj = new CLeaf();
					includedObj->SetAnimationSet(animation_sets->Get(ani_set));
					brick->AddNewObject(includedObj);
					i += 2;
					break;
				}

			}
			break;
		}
	case OBJECT_TYPE_SQUARE_BRICK:
	{
		obj = new CSquareBrick();
		((CSquareBrick*)obj)->SetFragmentAnimationSet(animation_sets->Get(atoi(tokens[4].c_str())));

		break;
	}
	case OBJECT_TYPE_COIN: obj = new CCoin(); break;
	case OBJECT_TYPE_KOOPA:
		{
			obj = new CKoopa();
			dynamic_cast<CKoopa*>(obj)->SetLevel(atoi(tokens[4].c_str()));
			break;
		}
	case OBJECT_TYPE_BACKGROUND: obj = new CBackground(); break;
	case OBJECT_TYPE_PORTAL:
		{	
			float r = atof(tokens[4].c_str());
			float b = atof(tokens[5].c_str());
			int scene_id = atoi(tokens[6].c_str());
			obj = new CPortal(x, y, r, b, scene_id);
		}
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
	if (includedObj) objects.push_back(includedObj);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneDirectory);

	// load background
	wstring tileset_path = wstring(sceneDirectory) + tilesetFileName;
	wstring tile_path = wstring(sceneDirectory) + tiledBackgroundFileName;
	tiled_background = new CTilemap(-10, 4, 11, tile_path.c_str(), tileset_path.c_str());
	tiled_background->LoadTiles();
	tiled_background->LoadMap();

	CResources::GetInstance()->LoadResources();

	// load map
	wstring objectPath = wstring(sceneDirectory) + objectsFileName;
	ifstream f;
	f.open(objectPath);			

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#' || line == "") continue;
		_ParseObjects(line);
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\Textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	CTextures::GetInstance()->Add(ID_HUD_BG, L"Resources\\Textures\\black-bg.png", D3DCOLOR_XRGB(255, 255, 255));

	HUD = new CHUD();

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneDirectory);

	StartGameTime();
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// get current zone's active area
	int minPixelWidth, maxPixelWidth;
	playZones[currentZone].GetHorizontalBounds(minPixelWidth, maxPixelWidth);
	
	int minPixelHeight, maxPixelHeight;
	playZones[currentZone].GetVerticalBounds(minPixelHeight, maxPixelHeight);

	// Reposition mario if needed
	float px, py;
	player->GetPosition(px, py);

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
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	if (cx < minPixelWidth) cx = minPixelWidth;
	else if (cx > maxPixelWidth - game->GetScreenWidth()) cx = maxPixelWidth - game->GetScreenWidth();

	if (cy > maxPixelHeight) cy = maxPixelHeight;
	else if (cy < minPixelHeight) cy = minPixelHeight;

	cy = (cy + (game->GetScreenHeight() - GAME_PLAY_HEIGHT));

	CGame::GetInstance()->SetCamPos((int)cx, (int)cy);

	HUD->SetPosition((int)cx, (int)cy + GAME_PLAY_HEIGHT);
	
	HUD->SetPowerLevel(player->GetPowerLevel());
	HUD->SetWorld(this->world);
	HUD->SetScore(game->GetScore());
	HUD->SetLives(game->GetLives());
	HUD->SetMoney(game->GetMoney());
	HUD->SetRemainingTime((GAMETIME - (GetTickCount64() - gameStartingTime)) / 1000);
}

void CPlayScene::Render()
{
	tiled_background->DrawFullTilemap(tile_x, tile_y);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	HUD->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;
	
	if (HUD)
	{
		HUD->Delete();
		delete HUD;
		HUD = NULL;
	}

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

	int shiftButtonPressed = 0;
	if (game->IsKeyDown(DIK_Z))
		shiftButtonPressed = 1;

	if (game->IsKeyDown(DIK_DOWN))
		mario->SetSittingState(1);
	else
		mario->SetSittingState(0);

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (shiftButtonPressed)
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (shiftButtonPressed)
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}
#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Background.h"
#include "ColoredBlock.h"
#include "Tube.h"
#include "QuestionBrick.h"
#include "SquareBrick.h"
#include "Coin.h"
#include "KoopaTroopa.h"
#include "GroundBricks.h"
#include "Mushroom.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath, int minPixelWidth, int maxPixelWidth, int minPixelHeight, int maxPixelHeight):
	CScene(id, filePath, minPixelWidth, maxPixelWidth, minPixelHeight, maxPixelHeight)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_MARIO			0
#define OBJECT_TYPE_BRICK			1
#define OBJECT_TYPE_GROUNDBRICK		101
#define OBJECT_TYPE_GOOMBA			2
#define OBJECT_TYPE_KOOPAS			3
#define OBJECT_TYPE_COLORED_BLOCK	4
#define OBJECT_TYPE_TUBE			5
#define OBJECT_TYPE_QUESTIONBRICK	6
#define OBJECT_TYPE_SQUARE_BRICK	7
#define OBJECT_TYPE_COIN			8
#define OBJECT_TYPE_KOOPATROOPA		9
#define OBJECT_TYPE_MUSHROOM		10
#define OBJECT_TYPE_BACKGROUND		11

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_GROUNDBRICK:
	{
		int numRows = atoi(tokens[4].c_str());
		int numColumns = atoi(tokens[5].c_str());
		obj = new CGroundBricks(numRows, numColumns);
		break;
	}
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;
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
			break;
		}
	case OBJECT_TYPE_QUESTIONBRICK: 
		{
			obj = new CQuestionBrick();
			CQuestionBrick* brick = dynamic_cast<CQuestionBrick*>(obj);
			int i = 4;
			while (i < tokens.size())
			{
				CGameObject* includedObj = NULL;
				
				switch (atoi(tokens[i].c_str()))
				{
				case OBJECT_TYPE_COIN:
					includedObj = new CCoin();
					includedObj->SetAnimationSet(
						animation_sets->Get(atoi(tokens[i + 1].c_str()))
					);
					i += 2;
					break;
				case OBJECT_TYPE_MUSHROOM:
					int ani_set = atoi(tokens[i + 1].c_str());
					int mushroom_level = atoi(tokens[i + 2].c_str());

					includedObj = new CMushroom(mushroom_level);
					includedObj->SetAnimationSet(animation_sets->Get(ani_set));

					dynamic_cast<CMushroom*>(includedObj)->SetContainer(obj);

					i += 3;
					break;
				}

				brick->AddNewObject(includedObj);
				objects.push_back(includedObj);
			}
			break;
		}
	case OBJECT_TYPE_SQUARE_BRICK: obj = new CSquareBrick(); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(); break;
	case OBJECT_TYPE_KOOPATROOPA:
		{
			float leftEdge = atof(tokens[4].c_str());
			float rightEdge = atof(tokens[5].c_str());
			obj = new CKoopaTroopa(leftEdge, rightEdge);
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
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
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

	/*if (player->IsOnTheFloor())
		DebugOut(L"\nOn The Floor");
	else
		DebugOut(L"\nOff The Floor");*/

	// Reposition mario if needed
	float px, py;
	player->GetPosition(px, py);

	float pLeft, pTop, pRight, pBottom;
	player->GetBoundingBox(pLeft, pTop, pRight, pBottom);
	float pWidth = pRight - pLeft;

	if (px < minPixelWidth) px = minPixelWidth;
	else if (px > maxPixelWidth - pWidth) px = maxPixelWidth - pWidth;

	player->SetPosition(px, py);

	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	int minPixelWidth, maxPixelWidth;
	this->GetBounds(minPixelWidth, maxPixelWidth);


	if (cx < minPixelWidth) cx = minPixelWidth;
	else if (cx > maxPixelWidth - game->GetScreenWidth()) cx = maxPixelWidth - game->GetScreenWidth();

	if (cy > maxPixelHeight) cy = maxPixelHeight;
	else if (cy < minPixelHeight) cy = minPixelHeight;

	CGame::GetInstance()->SetCamPos((int)cx, (int)cy);
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
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

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_SPACE:
		//float x, y;
		//mario->GetSpeed(x, y);
		//DebugOut(L"\nVelocity: %f %f", x, y);
		if (mario->IsJumping())
			mario->SetState(MARIO_STATE_JUMPING);
		break;
	case DIK_LSHIFT:
		mario->StartSpinning();
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

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;

	int shiftButtonPressed = 0;
	if (game->IsKeyDown(DIK_LSHIFT) || game->IsKeyDown(DIK_RSHIFT))
		shiftButtonPressed = 1;

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
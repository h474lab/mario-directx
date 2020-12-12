#include "IntroScene.h"
#include <fstream>
#include "Utils.h"

#include "Camera.h"
#include "Curtain.h"
#include "Title.h"
#include "Goomba.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Koopa.h"
#include "Beetle.h"

#include "IntroEvent.h"
#include "HUD.h"

void CIntroScene::ParseObjects(string line)
{
	vector<string> tokens = split(line);

	int type_id = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets *animation_sets = CAnimationSets::GetInstance();
	LPINTROEVENTS intro_events = CIntroEvents::GetInstance();

	CGameObject* obj = NULL;
	int currentCursor = -1;
	
	int numColumns, numRows, type;
	int sceneOption1, sceneOption2;
	int level;

	switch (type_id)
	{
	case OBJECT_TYPE_INTRO_CURTAIN:
		numColumns = atoi(tokens[4].c_str());
		numRows = atoi(tokens[5].c_str());
		type = atoi(tokens[6].c_str());
		obj = new CCurtain(numColumns, numRows, type);
		objects.push_back(obj);
		// put cursor = 7 in order to continue creating events
		currentCursor = 7;
		break;
	case OBJECT_TYPE_INTRO_TITLE:
		obj = new CTitle();
		objects.push_back(obj);
		currentCursor = 4;
		break;
	case OBJECT_TYPE_INTRO_OPTIONS:
		sceneOption1 = atoi(tokens[4].c_str());
		sceneOption2 = atoi(tokens[5].c_str());
		obj = new CIntroOptions(sceneOption1, sceneOption2);
		objects.push_back(obj);
		gameModeMenu = dynamic_cast<CIntroOptions*>(obj);
		currentCursor = 6;
		break;
	case OBJECT_TYPE_MARIO:
		level = atoi(tokens[4].c_str());
		obj = new CMario();
		((CMario*)obj)->SetLevel(level);
		objects.push_back(obj);
		currentCursor = 5;
		break;
	case OBJECT_TYPE_MUSHROOM:
		level = atoi(tokens[4].c_str());
		obj = new CMushroom(level);
		objects.push_back(obj);
		currentCursor = 5;
		break;
	case OBJECT_TYPE_GOOMBA:
		obj = new CGoomba();
		objects.push_back(obj);
		currentCursor = 4;
		break;
	case OBJECT_TYPE_LEAF:
		obj = new CLeaf();
		objects.push_back(obj);
		currentCursor = 4;
		break;
	case OBJECT_TYPE_KOOPA:
		obj = new CKoopa();
		objects.push_back(obj);
		currentCursor = 4;
		break;
	case OBJECT_TYPE_BEETLE:
		obj = new CBeetle();
		objects.push_back(obj);
		currentCursor = 4;
		break;
	}

	for (unsigned int i = currentCursor; i < tokens.size(); i += 3)
	{
		LPINTROEVENT event = new CIntroEvent(obj, atoi(tokens[i].c_str()), atoi(tokens[i + 1].c_str()), atoi(tokens[i + 2].c_str()));
		intro_events->Add(event);
	}

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	obj->SetPosition(x, y);
}

CIntroScene::CIntroScene(int id, LPCWSTR filePath, LPCWSTR objectFileName) : CScene(id, filePath) 
{
	intro_start = (DWORD) (DWORD)GetTickCount64();
	this->objectsFileName = objectFileName;
	this->gameModeMenu = NULL;
	key_handler = new CIntroSceneKeyHandler(this);
}

void CIntroScene::Load()
{
	LoadObjects();
	CCamera::GetInstance()->SetPosition(0.0f, 32.0f);
}

void CIntroScene::Update(DWORD dt)
{
	if ((DWORD)GetTickCount64() - intro_start > CHANGE_BACKGROUND_COLOR_TIME) CGame::GetInstance()->SetBackgroundColor(BACKGROUND_COLOR_INTRO_SCENE_AFTER);

	LPINTROEVENTS intro_events = CIntroEvents::GetInstance();
	vector<LPINTROEVENT> temp;
	temp.clear();
	while (true)
	{
		LPINTROEVENT event = intro_events->PeekNextEvent();
		if (!event || event->starting_time > (DWORD)GetTickCount64() - intro_start) break;
		if (dynamic_cast<CMario*>(event->object))
		{
			CMario* mario = dynamic_cast<CMario*>(event->object);
			mario->SetInIntro(1);
			temp.push_back(event);
			if (event->state == MARIO_STATE_JUMPING)
				mario->SetJumpingUp(1);
			else if (event->state == MARIO_STATE_FLY_JUMP_LEFT)
			{
				if ((DWORD)GetTickCount64() - mario_flyjump_timer > MARIO_FLY_JUMP_PUSHING_TIME)
				{
					mario_flyjump_timer = (DWORD)GetTickCount64();
					mario->SetJumpingUp(0);
					mario->FlyJump();
				}
			}
			event->object->SetState(event->state);
		}
		else if (dynamic_cast<CGoomba*>(event->object))
		{
			CGoomba* goomba = dynamic_cast<CGoomba*>(event->object);
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				goomba->SetLevel(event->level);
				event->object->SetState(event->state);
			}
		}
		else if (dynamic_cast<CBeetle*>(event->object))
		{
			CBeetle* beetle = dynamic_cast<CBeetle*>(event->object);
			beetle->SetState(event->state);
		}
		else
		{
			event->object->SetState(event->state);
		}
		intro_events->PopNextEvent();
	}

	for (LPINTROEVENT event : temp)
	{
		intro_events->Add(event);
	}

	vector<LPGAMEOBJECT> coObjects;
	for (auto object : objects) coObjects.push_back(object);
	coObjects.push_back(CHUD::GetInstance());

	for (auto object : objects)
		object->Update(dt, &coObjects);

	CHUD::GetInstance()->Update(dt);
}

void CIntroScene::Render()
{
	CHUD::GetInstance()->Render();

	for (auto object : objects)
		object->Render();
}

void CIntroScene::Unload()
{
	for (auto object : objects)
		delete object;
	objects.clear();
}

void CIntroSceneKeyHandler::KeyState(BYTE* states)
{
}

void CIntroSceneKeyHandler::OnKeyDown(int KeyCode)
{
	CIntroOptions* menu = ((CIntroScene*)scene)->GetMenu();
	if (KeyCode == DIK_DOWN || KeyCode == DIK_UP)
	{
		if (menu)
			menu->SwitchFocusingOption();
	}

	if (KeyCode == DIK_RETURN)
	{
		if (menu)
		{
			CGame::GetInstance()->SetGameState(GAME_STATE_WELCOME);
			CHUD::GetInstance()->SetLives(DEFAULT_LIVES);
			menu->SwitchSceneOption();
			scene->Unload();
		}
		else ((CIntroScene*)scene)->SetAppearingMenu();
	}
}

void CIntroSceneKeyHandler::OnKeyUp(int KeyCode)
{
}

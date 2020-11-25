#include "IntroScene.h"
#include <fstream>
#include "Utils.h"

#include "Camera.h"
#include "Curtain.h"
#include "Title.h"
#include "IntroEvent.h"
#include "HUD.h"


void CIntroScene::ParseObjects(string line)
{
	vector<string> tokens = split(line);

	int type_id = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets *animation_sets = CAnimationSets::GetInstance();
	LPINTROEVENTS intro_events = CIntroEvents::GetInstance();

	CGameObject* obj = NULL;
	int currentCursor = -1;
	
	int numColumns, numRows, type;
	int sceneOption1, sceneOption2;

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
	}

	for (int i = currentCursor; i < tokens.size(); i += 2)
	{
		LPINTROEVENT event = new CIntroEvent(obj, atoi(tokens[i].c_str()), atoi(tokens[i + 1].c_str()));
		intro_events->Add(event);
	}

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	obj->SetPosition(x, y);
}

CIntroScene::CIntroScene(int id, LPCWSTR filePath, LPCWSTR objectFileName) : CScene(id, filePath) 
{
	intro_start = (DWORD) GetTickCount64();
	this->objectsFileName = objectFileName;
	key_handler = new CIntroScenceKeyHandler(this);
}

void CIntroScene::Load()
{
	wstring objectPath = wstring(sceneDirectory) + objectsFileName;
	ifstream f;
	f.open(objectPath);

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#' || line == "") continue;
		ParseObjects(line);
	}

	f.close();
}

void CIntroScene::Update(DWORD dt)
{
	if ((DWORD)GetTickCount64() - intro_start > CHANGE_BACKGROUND_COLOR_TIME) CGame::GetInstance()->SetBackgroundColor(BACKGROUND_COLOR_INTRO_SCENE_AFTER);

	LPINTROEVENTS intro_events = CIntroEvents::GetInstance();
	while (true)
	{
		LPINTROEVENT event = intro_events->PeekNextEvent();
		if (!event || event->starting_time > (DWORD)GetTickCount64() - intro_start) break;
		event->object->SetState(event->state);
		intro_events->PopNextEvent();
	}

	for (auto object : objects)
		object->Update(dt);

	float cx = 0;
	float cy = (int) CGame::GetInstance()->GetScreenHeight() - GAME_PLAY_HEIGHT;

	CCamera::GetInstance()->SetPosition(cx, cy);
	CHUD::GetInstance()->SetPosition(cx, cy + GAME_PLAY_HEIGHT);
}

void CIntroScene::Render()
{
	for (auto object : objects)
		object->Render();

	CHUD::GetInstance()->Render();
}

void CIntroScene::Unload()
{
	for (auto object : objects)
		delete object;
	objects.clear();
}

void CIntroScenceKeyHandler::KeyState(BYTE* states)
{
}

void CIntroScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CIntroOptions* menu = ((CIntroScene*)scence)->GetMenu();
	if (KeyCode == DIK_DOWN || KeyCode == DIK_UP)
	{
		if (menu)
			menu->SwitchFocusingOption();
	}

	if (KeyCode == DIK_RETURN)
	{
		if (menu)
		{
			menu->SwitchSceneOption();
			scence->Unload();
		}
	}
}

void CIntroScenceKeyHandler::OnKeyUp(int KeyCode)
{
}

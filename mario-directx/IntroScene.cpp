#include "IntroScene.h"
#include <fstream>
#include "Utils.h"

#include "Camera.h"
#include "Curtain.h"
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

	switch (type_id)
	{
	case OBJECT_TYPE_INTRO_CURTAIN:
		int numColumns = atoi(tokens[4].c_str());
		int numRows = atoi(tokens[5].c_str());
		int type = atoi(tokens[6].c_str());
		obj = new CCurtain(numColumns, numRows, type);
		objects.push_back(obj);
		LPINTROEVENT event = new CIntroEvent(obj, atoi(tokens[7].c_str()), atoi(tokens[8].c_str()));
		intro_events->Add(event);
		break;
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
	float cy = CGame::GetInstance()->GetScreenHeight() - GAME_PLAY_HEIGHT;

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
}

void CIntroScenceKeyHandler::OnKeyUp(int KeyCode)
{
}

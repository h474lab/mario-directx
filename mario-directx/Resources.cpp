#include <fstream>
#include "Resources.h"
#include "Textures.h"
#include "Sprites.h"

CResources *CResources::__instance = NULL;

void CResources::_ParseSection_TEXTURES(string line)
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

void CResources::_ParseSection_SPRITES(string line)
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

void CResources::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CResources::_ParseSection_ANIMATION_SETS(string line)
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

void CResources::LoadTextures()
{
	ifstream f;
	f.open(texturesPath);

	while (!f.eof())
	{
		string line;
		getline(f, line);

		_ParseSection_TEXTURES(line);
	}
}

void CResources::LoadSprites()
{
	for (wstring object : objectList)
	{
		ifstream f;
		wstring path = spritesPath + object + L".txt";
		f.open(path);

		while (!f.eof())
		{
			string line;
			getline(f, line);

			if (line[0] == '#' || line == "") continue;

			_ParseSection_SPRITES(line);
		}
	}
}

void CResources::LoadAnimations()
{
	for (wstring object : objectList)
	{
		ifstream f;
		wstring path = animationsPath + object + L".txt";
		f.open(path);

		while (!f.eof())
		{
			string line;
			getline(f, line);

			if (line[0] == '#' || line == "") continue;

			_ParseSection_ANIMATIONS(line);
		}
	}
}

void CResources::LoadAnimationSets()
{
	for (wstring object : objectList)
	{
		ifstream f;
		wstring path = animationSetsPath + object + L".txt";
		f.open(path);

		while (!f.eof())
		{
			string line;
			getline(f, line);

			if (line[0] == '#' || line == "") continue;

			_ParseSection_ANIMATION_SETS(line);
		}
	}
}

void CResources::SetGameObjectList(LPCWSTR objectListPath)
{
	this->objectListPath = objectListPath;

	ifstream f;
	f.open(objectListPath);
	objectList.clear();

	while (!f.eof())
	{
		string object;
		getline(f, object);

		wstring w_object = wstring(object.begin(), object.end());
		objectList.push_back(w_object);
	}
}

void CResources::LoadResources()
{
	LoadTextures();
	LoadSprites();
	LoadAnimations();
	LoadAnimationSets();
}

CResources* CResources::GetInstance()
{
	if (__instance == NULL) __instance = new CResources();
	return __instance;
}

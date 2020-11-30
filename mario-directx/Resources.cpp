#include <fstream>
#include "Resources.h"
#include "Textures.h"
#include "Sprites.h"
#include "MapNode.h"
#include "Grid.h"
#include "HUD.h"

#include "MapGate.h"

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
	for (unsigned int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
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

	for (unsigned int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}


void CResources::_ParseSection_MAP_NODE_SETS(string line)
{
	CMapNodeSets* mapNode_sets = CMapNodeSets::GetInstance();
	vector<string> tokens = split(line);

	int world = atoi(tokens[0].c_str());
	
	// import id and position of map node
	int nodeId = atoi(tokens[1].c_str());
	float x = atof(tokens[2].c_str());
	float y = atof(tokens[3].c_str());

	// import id of left, top, right, bottom node of this node
	int leftNode = atoi(tokens[4].c_str());
	int topNode = atoi(tokens[5].c_str());
	int rightNode = atoi(tokens[6].c_str());
	int bottomNode = atoi(tokens[7].c_str());

	// load object
	int object_id = atoi(tokens[8].c_str());
	int scene_id;
	int ani_set;
	int object_type, object_level;
	CGameObject* obj = NULL;
	switch (object_id)
	{
	case OBJECT_TYPE_MAP_GATE:
		ani_set = atoi(tokens[9].c_str());
		scene_id = atoi(tokens[10].c_str());
		object_type = atoi(tokens[11].c_str());
		object_level = atoi(tokens[12].c_str());
		obj = new CMapGate(scene_id, x, y, object_level, object_type);
		obj->SetAnimationSet(CAnimationSets::GetInstance()->Get(ani_set));
		break;
	}

	if (!mapNode_sets->Exists(world)) mapNode_sets->Add(world, new CMapNodes());
	mapNode_sets->Get(world)->Add(nodeId, new CMapNode(obj, x, y, leftNode, topNode, rightNode, bottomNode));
}

void CResources::_ParseSection_GRID(string line)
{
	vector<string> tokens = split(line);

	int id = atoi(tokens[0].c_str());
	float start_x = atof(tokens[1].c_str());
	float end_x = atof(tokens[2].c_str());
	float start_y = atof(tokens[3].c_str());
	float end_y = atof(tokens[4].c_str());

	int numRows = atoi(tokens[5].c_str());
	int numColumns = atoi(tokens[6].c_str());

	CGrids::GetInstance()->Add(id, new CGrid(start_x, start_y, end_x, end_y, numRows, numColumns));
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

	CHUD::GetInstance()->SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_HUD_BACKGROUND));
}

void CResources::LoadMapNodes()
{
	ifstream f;
	f.open(mapNodesPath);
	while (!f.eof())
	{
		string line;
		getline(f, line);

		if (line[0] == '#' || line == "") continue;

		_ParseSection_MAP_NODE_SETS(line);
	}
}

void CResources::LoadGridList()
{
	ifstream f;
	f.open(gridListPath);
	while (!f.eof())
	{
		string line;
		getline(f, line);
		if (line[0] == '#' || line == "") continue;

		_ParseSection_GRID(line);
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
	LoadMapNodes();
	LoadGridList();
}

CResources* CResources::GetInstance()
{
	if (__instance == NULL) __instance = new CResources();
	return __instance;
}

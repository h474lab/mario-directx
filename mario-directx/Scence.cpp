#include "Scence.h"
#include "Utils.h"
#include <fstream>

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneDirectory = filePath;
}

void CScene::LoadObjects()
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

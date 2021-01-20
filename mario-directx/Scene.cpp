#include "scene.h"
#include "Utils.h"
#include <fstream>
#include "PlatformSet.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneDirectory = filePath;
}

void CScene::LoadObjects()
{
	// Clear all elements in Platform Set
	CPlatformSet::GetInstance()->Clear();

	// Get object file path
	wstring objectPath = wstring(sceneDirectory) + objectsFileName;
	ifstream f;
	f.open(objectPath);

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		// Skip comment line or blank line
		if (line[0] == '#' || line == "") continue;
		// Parse object defined in current line
		ParseObjects(line);
	}

	f.close();
}

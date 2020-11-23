#include "Scence.h"
#include "Utils.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneDirectory = filePath;
}

#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneDirectory = filePath;
}
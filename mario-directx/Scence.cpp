#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath, int minPixel, int maxPixel)
{
	this->id = id;
	this->sceneFilePath = filePath;
	this->minPixel = minPixel;
	this->maxPixel = maxPixel;
}

void CScene::GetBounds(int& minPixel, int& maxPixel)
{
	minPixel = this->minPixel;
	maxPixel = this->maxPixel;
}

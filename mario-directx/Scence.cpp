#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath, int minPixelWidth, int maxPixelWidth, int minPixelHeight, int maxPixelHeight)
{
	this->id = id;
	this->sceneFilePath = filePath;
	this->minPixelWidth = minPixelWidth;
	this->maxPixelWidth = maxPixelWidth;
	this->minPixelHeight = minPixelHeight;
	this->maxPixelHeight = maxPixelHeight;
}

void CScene::GetBounds(int& minPixelWidth, int& maxPixelWidth)
{
	minPixelWidth = this->minPixelWidth;
	maxPixelWidth = this->maxPixelWidth;
}

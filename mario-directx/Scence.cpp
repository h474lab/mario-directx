#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath, LPCWSTR tilesetFileName, LPCWSTR tiledBackgroundFileName, LPCWSTR objectsFileName, int minPixelWidth, int maxPixelWidth, int minPixelHeight, int maxPixelHeight, int world)
{
	this->id = id;
	this->sceneDirectory = filePath;

	this->tilesetFileName = tilesetFileName;
	this->tiledBackgroundFileName = tiledBackgroundFileName;
	this->objectsFileName = objectsFileName;

	this->minPixelWidth = minPixelWidth;
	this->maxPixelWidth = maxPixelWidth;
	this->minPixelHeight = minPixelHeight;
	this->maxPixelHeight = maxPixelHeight;

	this->world = world;
}

void CScene::GetBounds(int& minPixelWidth, int& maxPixelWidth)
{
	minPixelWidth = this->minPixelWidth;
	maxPixelWidth = this->maxPixelWidth;
}

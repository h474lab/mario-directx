#include "Tilemap.h"
#include "Textures.h"
#include <fstream>

CTilemap::CTilemap(int numRows, int numColumns, LPCWSTR tileFilePath, LPCWSTR tilesetFilePath, int tileWidth, int tileHeight, D3DCOLOR transparentColor)
{
	this->ID = 0;
	this->spriteList = CSprites::GetInstance();
	this->spriteList->Clear();

	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	this->numColumns = numColumns;
	this->numRows = numRows;

	this->tileFilePath = tileFilePath;
	this->tilesetFilePath = tilesetFilePath;

	this->transparentColor = transparentColor;
}

int CTilemap::getTileID(int tilePosition)
{
	return ID * 91 + 23 * tilePosition;
}

void CTilemap::LoadTiles()
{
	CTextures* textures = CTextures::GetInstance();
	textures->Add(ID, tilesetFilePath, transparentColor);

	LPDIRECT3DTEXTURE9 texture = textures->Get(ID);

	int position = 0;;
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			spriteList->Add(this->getTileID(position), j * tileWidth, i * tileHeight, (j + 1) * tileWidth, (i + 1) * tileHeight, texture);
			position++;
		}
	}
}

void CTilemap::LoadMap()
{
	// clear everything in the map before loading
	tilemap.clear();

	ifstream f;
	f.open(tileFilePath);
	bool result = tilemap.empty();

	char str[TILEMAP_MAX_SIZE];
	while (f.getline(str, TILEMAP_MAX_SIZE))
	{
		string line(str);
		vector<string> tile = split(line);

		vector<LPSPRITE> tile_line;
		bool result = tile_line.empty();

		for (unsigned int i = 0; i < tile.size(); i++)
		{
			int tilePos = atoi(tile[i].c_str());
			if (tilePos != -1)
			{
				int tileID = getTileID(tilePos);
				tile_line.push_back(spriteList->Get(tileID));
			}
			else tile_line.push_back(NULL);
		}

		tilemap.push_back(tile_line);
	}

	f.close();
}

void CTilemap::DrawFullTilemap(float posX, float posY, float left, float top, float right, float bottom)
{
	unsigned int start_x = 0, end_x = tilemap[0].size();
	unsigned int start_y = 0, end_y = tilemap.size();

	if (!(left == -1 || top == -1 || right == -1 || bottom == -1))
	{
		start_x = (unsigned int)(left - posX) / tileWidth;
		end_x = (unsigned int)(right - posX) / tileWidth;
		start_y = (unsigned int)(top - posY) / tileHeight;
		end_y = (unsigned int)(bottom - posY) / tileHeight;
	}

	for (unsigned int i = start_y; i < end_y; i++)
		for (unsigned int j = start_x; j < end_x; j++)
		{
			if (i >= tilemap.size() || j >= tilemap[i].size()) continue;
			float x = posX + j * this->tileWidth;
			float y = posY + i * this->tileHeight;

			if (tilemap[i][j]) tilemap[i][j]->Draw(x, y);
			//CGame::GetInstance()->Draw(x, y, CTextures::GetInstance()->Get(10), 0, 0, 16, 16);
		}

	//spriteList->Get(-9887)->Draw(50, 150);
}

CTilemaps* CTilemaps::__instance = NULL;

void CTilemaps::Add(int id, LPTILEMAP tilemap)
{
	tilemaps.insert(std::make_pair(id, tilemap));
	tilemap->SetTilemapId(id);
}

LPTILEMAP CTilemaps::Get(int id)
{
	return tilemaps.at(id);
}

void CTilemaps::Clear()
{
	tilemaps.clear();
}

CTilemaps* CTilemaps::GetInstance()
{
	if (__instance == NULL) __instance = new CTilemaps();
	return __instance;
}

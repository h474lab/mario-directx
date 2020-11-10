#include "Tilemap.h"
#include "Textures.h"
#include <fstream>

CTilemap::CTilemap(int id, int numRows, int numColumns, LPCWSTR tileFilePath, LPCWSTR tilesetFilePath, int tileWidth, int tileHeight, D3DCOLOR transparentColor)
{
	this->ID = id;

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
	return ID * 991 + 23 * tilePosition;
}

void CTilemap::LoadTiles()
{
	CTextures* textures = CTextures::GetInstance();
	textures->Add(ID, tilesetFilePath, transparentColor);

	LPDIRECT3DTEXTURE9 texture = textures->Get(ID);

	spriteList = CSprites::GetInstance();
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
	ifstream f;
	f.open(tileFilePath);
	tilemap.empty();

	char str[TILEMAP_MAX_SIZE];
	while (f.getline(str, TILEMAP_MAX_SIZE))
	{
		string line(str);
		vector<string> tile = split(line);

		vector<LPSPRITE> tile_line;
		tile_line.empty();

		for (int i = 0; i < tile.size(); i++)
		{
			int tileID = getTileID(atoi(tile[i].c_str()));
			tile_line.push_back(spriteList->Get(tileID));

			//DebugOut(L"[INFO] Tile loaded Ok: id=%d, %s\n", tileID, tileFilePath);
		}

		tilemap.push_back(tile_line);
	}

	f.close();
}

void CTilemap::DrawFullTilemap(float posX, float posY)
{
	for (int i = 0; i < tilemap.size(); i++)
		for (int j = 0; j < tilemap[i].size(); j++)
		{
			float x = posX + j * this->tileWidth;
			float y = posY + i * this->tileHeight;

			tilemap[i][j]->Draw(x, y);
			//CGame::GetInstance()->Draw(x, y, CTextures::GetInstance()->Get(10), 0, 0, 16, 16);
		}

	//spriteList->Get(-9887)->Draw(50, 150);
}

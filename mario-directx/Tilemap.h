#pragma once

#include "Game.h"

#define TILEMAP_MAX_SIZE	1024

class CTilemap
{
private:
	int ID;

	int tileWidth, tileHeight;
	int numRows, numColumns;

	CSprites *spriteList;
	vector<vector<LPSPRITE>> tilemap;

	LPCWSTR tilesetFilePath;
	LPCWSTR tileFilePath;

	D3DCOLOR transparentColor;
public:
	CTilemap(int numRows, int numColumns, LPCWSTR tileFilePath, LPCWSTR tilesetFilePath, int tileWidth = 16, int tileHeight = 16, D3DCOLOR transparentColor = D3DCOLOR_XRGB(0, 255, 8));
	void SetTilemapId(int id) { ID = id; }

	int getTileID(int tilePosition);

	void LoadTiles();
	void LoadMap();

	void DrawFullTilemap(float posX, float posY, float left = -1, float top = -1, float right = -1, float bottom = -1);
};

typedef CTilemap* LPTILEMAP;

class CTilemaps
{
private:
	static CTilemaps* __instance;
	unordered_map<int, LPTILEMAP> tilemaps;
public:
	void Add(int id, LPTILEMAP tilemap);
	LPTILEMAP Get(int id);
	void Clear();

	static CTilemaps* GetInstance();
};


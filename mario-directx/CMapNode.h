#pragma once
#include "GameObject.h"

#define LEFT_NODE	0
#define RIGHT_NODE	1
#define TOP_NODE	2
#define BOTTOM_NODE	3

class CMapNode;
typedef CMapNode* LPMAPNODE;

class CMapNode
{
	CGameObject* object;
	float x, y;
	CMapNode* leftNode;
	CMapNode* rightNode;
	CMapNode* topNode;
	CMapNode* bottomNode;
public:
	CMapNode(CGameObject* object, float x, float y, CMapNode* leftNode, CMapNode* topNode, CMapNode* rightNode, CMapNode* bottomNode);
	LPMAPNODE GetNode(int type);
};

class CMapNodes
{
	static CMapNodes* __instance;
	unordered_map<int, LPMAPNODE> mapNodes;
public:
	static CMapNodes* GetInstance();
	void Add(int id, LPMAPNODE mapNode);
	LPMAPNODE Get(int id);
	void Clear();
};
#pragma once
#include "GameObject.h"

#define NULL_NODE	-1

#define LEFT_NODE	0
#define RIGHT_NODE	1
#define TOP_NODE	2
#define BOTTOM_NODE	3

class CMapNode;
typedef int LPMAPNODE;

class CMapNode
{
	CGameObject* object;
	float x, y;
	int leftNode, rightNode, topNode, bottomNode;
public:
	CMapNode(CGameObject* object, float x, float y, int leftNode, int topNode, int rightNode, int bottomNode);
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
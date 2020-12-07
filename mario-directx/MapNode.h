#pragma once
#include "GameObject.h"

#define NULL_NODE	-1

#define LEFT_NODE	0
#define RIGHT_NODE	1
#define TOP_NODE	2
#define BOTTOM_NODE	3

class CMapNode;
typedef CMapNode* LPMAPNODE;

class CMapNodes;
typedef CMapNodes* LPMAPNODES;

class CMapNode
{
	CGameObject* object;
	float x, y;
	int leftNode, rightNode, topNode, bottomNode;
public:
	CMapNode(CGameObject* object, float x, float y, int leftNode, int topNode, int rightNode, int bottomNode);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	int GetNode(int type);
	CGameObject* GetNodeObject();
};

class CMapNodes
{
	LPMAPNODE currentNode;
	unordered_map<int, LPMAPNODE> mapNodes;
public:
	void Add(int id, LPMAPNODE mapNode);
	LPMAPNODE Get(int id);
	void SetCurrentNode(LPMAPNODE currentNode) { this->currentNode = currentNode; }
	LPMAPNODE GetCurrentNode();
	vector<LPMAPNODE> GetAllNodes();
	void Clear();
};

class CMapNodeSets
{
	static CMapNodeSets* __instance;
	unordered_map<int, LPMAPNODES> mapNodeSets;
public:
	static CMapNodeSets* GetInstance();

	int Exists(int world);
	void Add(int world, LPMAPNODES mapNodes);
	void ResetNodes(int world);
	LPMAPNODES Get(int world);
};
#include "MapNode.h"

void CMapNodes::Add(int id, LPMAPNODE mapNode)
{
	mapNodes.insert(std::make_pair(id, mapNode));
}

LPMAPNODE CMapNodes::Get(int id)
{
	return mapNodes.at(id);
}

vector<LPMAPNODE> CMapNodes::GetAllNodes()
{
	vector<LPMAPNODE> result;
	result.clear();
	for (std::unordered_map<int, LPMAPNODE>::iterator it = mapNodes.begin(); it != mapNodes.end(); ++it)
		result.push_back(it->second);
}

void CMapNodes::Clear()
{
	mapNodes.clear();
}

CMapNode::CMapNode(CGameObject* object, float x, float y, int leftNode, int topNode, int rightNode, int bottomNode)
{
	this->object = object;
	this->x = x;
	this->y = y;
	this->leftNode = leftNode;
	this->topNode = topNode;
	this->rightNode = rightNode;
	this->bottomNode = bottomNode;
}

int CMapNode::GetNode(int type)
{
	if (type == LEFT_NODE) return leftNode;
	if (type == RIGHT_NODE) return rightNode;
	if (type == TOP_NODE) return topNode;
	if (type == BOTTOM_NODE) return bottomNode;
	return NULL_NODE;
}

CGameObject* CMapNode::GetNodeObject()
{
	return object;
}

CMapNodeSets* CMapNodeSets::GetInstance()
{
	if (__instance == NULL) __instance = new CMapNodeSets();
	return __instance;
}

int CMapNodeSets::Exists(int world)
{
	if (mapNodeSets.find(world) == mapNodeSets.end()) return 0;
	return 1;
}

void CMapNodeSets::Add(int world, LPMAPNODES mapNodes)
{
	mapNodeSets.insert(std::make_pair(world, mapNodes));
}

LPMAPNODES CMapNodeSets::Get(int world)
{
	if (!Exists(world)) return NULL;
	return mapNodeSets.at(world);
}

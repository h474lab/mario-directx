#include "CMapNode.h"

CMapNodes *CMapNodes::__instance = NULL;

CMapNodes* CMapNodes::GetInstance()
{
	if (__instance != NULL) __instance = new CMapNodes();
	return __instance;
}

void CMapNodes::Add(int id, LPMAPNODE mapNode)
{
	mapNodes.insert(std::make_pair(id, mapNode));
}

LPMAPNODE CMapNodes::Get(int id)
{
	return mapNodes.at(id);
}

void CMapNodes::Clear()
{
	mapNodes.clear();
}

CMapNode::CMapNode(CGameObject* object, float x, float y, CMapNode* leftNode, CMapNode* topNode, CMapNode* rightNode, CMapNode* bottomNode)
{
	this->object = object;
	this->x = x;
	this->y = y;
	this->leftNode = leftNode;
	this->topNode = topNode;
	this->rightNode = rightNode;
	this->bottomNode = bottomNode;
}

LPMAPNODE CMapNode::GetNode(int type)
{
	switch (type) {
	case LEFT_NODE:
		return leftNode;
	case RIGHT_NODE:
		return rightNode;
	case TOP_NODE:
		return topNode;
	case BOTTOM_NODE:
		return bottomNode;
	}
	return NULL;
}

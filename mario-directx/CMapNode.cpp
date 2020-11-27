#include "CMapNode.h"

CMapNodes *CMapNodes::__instance = NULL;

CMapNodes* CMapNodes::GetInstance()
{
	if (__instance == NULL) __instance = new CMapNodes();
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

LPMAPNODE CMapNode::GetNode(int type)
{
	CMapNodes* mapNodes = CMapNodes::GetInstance();

	switch (type) {
	case LEFT_NODE:
		if (leftNode != NULL_NODE)
			return mapNodes->Get(leftNode);
		break;
	case RIGHT_NODE:
		if (rightNode != NULL_NODE)
			return mapNodes->Get(rightNode);
		break;
	case TOP_NODE:
		if (topNode != NULL_NODE)
			return mapNodes->Get(topNode);
		break;
	case BOTTOM_NODE:
		if (bottomNode != NULL_NODE)
			return mapNodes->Get(bottomNode);
		break;
	}
	return NULL;
}

#pragma once
#include "GameObject.h"

#define MAPGATE_LEVEL_GAME		0
#define MAPGATE_LEVEL_MINIGAME	1
#define MAPGATE_LEVEL_NONE		2

#define MAPGATE_TYPE_LEVEL_1	0
#define MAPGATE_TYPE_LEVEL_2	1
#define MAPGATE_TYPE_LEVEL_3	2
#define MAPGATE_TYPE_LEVEL_4	3
#define MAPGATE_TYPE_LEVEL_5	4
#define MAPGATE_TYPE_LEVEL_6	5
#define MAPGATE_TYPE_DOOR		6
#define MAPGATE_TYPE_TEMPLE		7
#define MAPGATE_TYPE_BLADE_CARD	8
#define MAPGATE_TYPE_MUSHROOM	9
#define MAPGATE_TYPE_CASTLE		10
#define MAPGATE_TYPE_START		11

#define MAPGATE_STATE_OPEN		0
#define MAPGATE_STATE_CLOSED	1

#define MAPGATE_ANI_GATE_1	0
#define MAPGATE_ANI_GATE_2	1
#define MAPGATE_ANI_GATE_3	2
#define MAPGATE_ANI_GATE_4	3
#define MAPGATE_ANI_GATE_5	4
#define MAPGATE_ANI_GATE_6	5
#define MAPGATE_ANI_DOOR	6

#define MAPGATE_ANI_TEMPLE_ORIGINAL		7
#define MAPGATE_ANI_TEMPLE_DEMOLISHED	8
#define MAPGATE_ANI_START				9
#define MAPGATE_ANI_BLADE_CARD_NORMAL	10
#define MAPGATE_ANI_BLADE_N				11
#define MAPGATE_ANI_MUSHROOM			12
#define MAPGATE_ANI_CASTLE				13

#define MAPGATE_ANI_ACHIEVED_WHITE	14
#define MAPGATE_ANI_ACHIEVED_ORANGE	15

#define CASTLE_ROOF_HEIGHT	16

class CMapGate : public CGameObject
{
	int sceneId;
	int type, level;
public:
	CMapGate(int sceneId, float x, float y, int level, int type);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render();
};


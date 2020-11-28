#include "MapGate.h"

CMapGate::CMapGate(int sceneId, float x, float y, int level, int type)
{
	this->sceneId = sceneId;

	this->x = x;
	this->y = y;

	this->level = level;
	this->type = type;
}

void CMapGate::Render()
{
	if (level == MAPGATE_LEVEL_NONE) return;

	int ani = -1;
	if (state == MAPGATE_STATE_CLOSED)
	{
		if (type == MAPGATE_TYPE_TEMPLE)
			ani = MAPGATE_ANI_TEMPLE_DEMOLISHED;
		else if (level == MAPGATE_LEVEL_GAME)
			ani = MAPGATE_ANI_ACHIEVED_WHITE;
		else
			ani = MAPGATE_ANI_ACHIEVED_ORANGE;
	}
	else
	{
		switch (type)
		{
		case MAPGATE_TYPE_LEVEL_1:
			ani = MAPGATE_ANI_GATE_1;
			break;
		case MAPGATE_TYPE_LEVEL_2:
			ani = MAPGATE_ANI_GATE_2;
			break;
		case MAPGATE_TYPE_LEVEL_3:
			ani = MAPGATE_ANI_GATE_3;
			break;
		case MAPGATE_TYPE_LEVEL_4:
			ani = MAPGATE_ANI_GATE_4;
			break;
		case MAPGATE_TYPE_LEVEL_5:
			ani = MAPGATE_ANI_GATE_5;
			break;
		case MAPGATE_TYPE_LEVEL_6:
			ani = MAPGATE_ANI_GATE_6;
			break;
		case MAPGATE_TYPE_DOOR:
			ani = MAPGATE_ANI_DOOR;
			break;
		case MAPGATE_TYPE_TEMPLE:
			ani = MAPGATE_ANI_TEMPLE_ORIGINAL;
			break;
		case MAPGATE_TYPE_BLADE_CARD:
			ani = MAPGATE_ANI_BLADE_CARD_NORMAL;
			break;
		case MAPGATE_TYPE_MUSHROOM:
			ani = MAPGATE_ANI_MUSHROOM;
			break;
		case MAPGATE_TYPE_CASTLE:
			ani = MAPGATE_ANI_CASTLE;
			break;
		case MAPGATE_TYPE_START:
			ani = MAPGATE_ANI_START;
			break;
		}
	}

	if (ani != -1)
	{
		if (type != MAPGATE_TYPE_CASTLE)
			animation_set->at(ani)->Render(x, y);
		else
			animation_set->at(ani)->Render(x, y - CASTLE_ROOF_HEIGHT);
	}
}

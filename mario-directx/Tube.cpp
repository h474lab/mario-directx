#include "Tube.h"

CTube::CTube(int numRows, int hasLid)
{
	this->numRows = numRows;
	this->hasLid = hasLid;
}

void CTube::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);

	if (object) object->SetPosition(x + TUBE_CELL_WIDTH / 2, y);
}

void CTube::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (object)
	{
		if (objLastState == FLYING_DIRECTION_DOWN && object->GetFlyingDirection() == FLYING_DIRECTION_NOMOVE)
		{
			object->SetDisappearingState();
			StartDelayingObject();
		}

		if (object->GetFlyingDirection() == FLYING_DIRECTION_NOMOVE && GetTickCount64() - objectDelay_start > TUBE_OBJECT_DELAYING_TIME)
		{
			object->SetFlyingDirection(FLYING_DIRECTION_UP, 1);
		}

		objLastState = object->GetFlyingDirection();
	}
}

void CTube::Render()
{
	for (int i = 0; i < numRows; i++)
	{
		if (i == 0 && hasLid == 1)
		{
			animation_set->at(TUBE_ANI_UPPER_LID_LEFT)->Render(x, y + 16 * i);
			animation_set->at(TUBE_ANI_UPPER_LID_RIGHT)->Render(x + TUBE_CELL_WIDTH, y + 16 * i);
			continue;
		}
		else if (i == numRows - 1 && hasLid == 2)
		{
			animation_set->at(TUBE_ANI_LOWER_LID_LEFT)->Render(x, y + 16 * i);
			animation_set->at(TUBE_ANI_LOWER_LID_RIGHT)->Render(x + TUBE_CELL_WIDTH, y + 16 * i);
			continue;
		}
		animation_set->at(TUBE_ANI_LEFT_EDGE)->Render(x, y + 16 * i);
		animation_set->at(TUBE_ANI_RIGHT_EDGE)->Render(x + TUBE_CELL_WIDTH, y + 16 * i);
	}
}

void CTube::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + TUBE_CELL_WIDTH * 2;
	b = t + TUBE_CELL_HEIGHT * numRows;
}

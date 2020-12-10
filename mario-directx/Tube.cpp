#include "Tube.h"
#include "Utils.h"

CTube::CTube(int numRows, int lidType, int zoneID)
{
	this->numRows = numRows;
	this->lidType = lidType;
	this->doorToZone = zoneID;
	renderScore = RENDER_SCORE_TUBE;
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
		if ((objLastState == FLYING_DIRECTION_DOWN && object->GetFlyingDirection() == FLYING_DIRECTION_NOMOVE))
		{
			object->SetDisappearingState();
			StartDelayingObject();
		}

		if (object->GetFlyingDirection() == FLYING_DIRECTION_NOMOVE && (DWORD)GetTickCount64() - objectDelay_start > TUBE_OBJECT_DELAYING_TIME)
		{
			object->SetFlyingDirection(FLYING_DIRECTION_UP, 1);
		}
		else
		{
			float object_x, object_y;
			followingObject->GetPosition(object_x, object_y);
			float l, t, r, b;
			followingObject->GetBoundingBox(l, t, r, b);
			float object_width = r - l;
			GetBoundingBox(l, t, r, b);
			float width = r - l;

			if ((object_x < this->x && this->x - (object_x + object_width) < DISTANCE_TO_MARIO_FOR_NOT_APPEARING) ||
				(object_x > this->x && object_x - (this->x + width) < DISTANCE_TO_MARIO_FOR_NOT_APPEARING))
				StartDelayingObject();
		}

		objLastState = object->GetFlyingDirection();
	}
}

void CTube::Render()
{
	for (int i = 0; i < numRows; i++)
	{
		if (i == 0 && lidType == TUBE_TYPE_UPPER_LID)
		{
			animation_set->at(TUBE_ANI_UPPER_LID_LEFT)->Render(x, y + TUBE_CELL_HEIGHT * i);
			animation_set->at(TUBE_ANI_UPPER_LID_RIGHT)->Render(x + TUBE_CELL_WIDTH, y + TUBE_CELL_HEIGHT * i);
			continue;
		}
		else if (i == numRows - 1 && lidType == TUBE_TYPE_LOWER_LID)
		{
			animation_set->at(TUBE_ANI_LOWER_LID_LEFT)->Render(x, y + TUBE_CELL_HEIGHT * i);
			animation_set->at(TUBE_ANI_LOWER_LID_RIGHT)->Render(x + TUBE_CELL_WIDTH, y + TUBE_CELL_HEIGHT * i);
			continue;
		}
		animation_set->at(TUBE_ANI_LEFT_EDGE)->Render(x, y + TUBE_CELL_HEIGHT * i);
		animation_set->at(TUBE_ANI_RIGHT_EDGE)->Render(x + TUBE_CELL_WIDTH, y + TUBE_CELL_HEIGHT * i);
	}
}

void CTube::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + TUBE_CELL_WIDTH * TUBE_MAX_COLUMN;
	b = t + TUBE_CELL_HEIGHT * numRows;
}

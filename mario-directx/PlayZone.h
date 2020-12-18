#pragma once
class CPlayZone
{
private:
	float min_px_x, max_px_x;
	float min_px_y, max_px_y;

	//int allowSavingPosition;
	float player_x, player_y;	// player's start position
public:
	void SetHorizontalBounds(float start, float end) { min_px_x = start; max_px_x = end; }
	void GetHorizontalBounds(float& start, float& end) { start = min_px_x; end = max_px_x; }

	void SetVerticalBounds(float start, float end) { min_px_y = start; max_px_y = end; }
	void GetVerticalBounds(float& start, float& end) { start = min_px_y; end = max_px_y; }

	/*void SetAllowSavingPosition(int allow) { allowSavingPosition = allow; }
	int GetAllowSavingPosition() { return allowSavingPosition; }*/

	void SetPlayerStartPosition(float x, float y) { player_x = x; player_y = y; }
	void GetPlayerStartPosition(float& x, float& y) { x = player_x; y = player_y; }
};
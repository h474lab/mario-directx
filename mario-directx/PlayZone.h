#pragma once
class CPlayZone
{
private:
	int min_px_x, max_px_x;
	int min_px_y, max_px_y;
	
	float player_x, player_y;	// player's start position
public:
	void SetHorizontalBounds(int start, int end) { min_px_x = start; max_px_x = end; }
	void GetHorizontalBounds(int& start, int& end) { start = min_px_x; end = max_px_x; }

	void SetVerticalBounds(int start, int end) { min_px_y = start; max_px_y = end; }
	void GetVerticalBounds(int& start, int& end) { start = min_px_y; end = max_px_y; }

	void SetPlayerStartPosition(float x, float y) { player_x = x; player_y = y; }
	void GetPlayerStartPosition(float& x, float& y) { x = player_x; y = player_y; }
};
#pragma once

#define CAMERA_FLOATING_SPEED_X	0.05f

class CCamera
{
private:
	float x, y;
	int lock = 0;	// not allow camera to change its position
	static CCamera* __instance;
public:
	void LockCamera(int value) { lock = value; }

	void SetPosition(float x, float y);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }

	static CCamera* GetInstance();
};


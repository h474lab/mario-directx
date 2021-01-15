#include "Camera.h"
#include <cstddef>

CCamera *CCamera::__instance = NULL;

void CCamera::SetPosition(float x, float y)
{
	if (!lock)
	{
		this->x = x;
		this->y = y;
	}
}

CCamera* CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}

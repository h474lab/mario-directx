#pragma once
#include "Scence.h"


class CIntroScene : public CScene
{
	DWORD intro_start;
public:
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};


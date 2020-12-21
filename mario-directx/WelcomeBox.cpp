#include "WelcomeBox.h"
#include "Game.h"

CWelcomeBox::CWelcomeBox()
{
	background = 1;
	SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_WELCOME_BOX));
	appearing_time = 0;

	world = new CNumber();

	this->lives[0] = new CNumber();
	this->lives[1] = new CNumber();

	this->state = WELCOME_BOX_STATE_DISAPPEAR;
	this->mario = NULL;
}

void CWelcomeBox::SetWorld(int world)
{
	this->world->SetCurrentNumber(world);
	this->world->SetState(NUMBER_STATE_AVAILABLE);
}

void CWelcomeBox::SetLives(int lives)
{
	if (lives < 10)
	{
		this->lives[0]->SetState(NUMBER_STATE_UNAVAILABLE);

		this->lives[1]->SetState(NUMBER_STATE_AVAILABLE);
		this->lives[1]->SetCurrentNumber(lives);
	}
	else
	{
		this->lives[0]->SetState(NUMBER_STATE_AVAILABLE);
		this->lives[0]->SetCurrentNumber(lives / 10);

		this->lives[1]->SetState(NUMBER_STATE_AVAILABLE);
		this->lives[1]->SetCurrentNumber(lives % 10);
	}
}

void CWelcomeBox::SetMario(CMapMario* mario)
{
	this->mario = mario;
}

void CWelcomeBox::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	world->SetPosition(x + WORLD_POSITION_X, y + WORLD_POSITION_Y);
	for (int i = 0; i < 2; i++)
	{
		lives[i]->SetPosition(x + LIVES_POSITION_X + NUMBER_WIDTH * i, y + LIVES_POSITION_Y);
	}

	mario->SetPosition(x + MARIO_POSITION_X, y + MARIO_POSITION_Y);
}

void CWelcomeBox::SetState(int state)
{
	if (state == this->state) return;
	CGameObject::SetState(state);
	CGame* game = CGame::GetInstance();
	switch (state)
	{
	case WELCOME_BOX_STATE_APPEAR:
		appearing_time = (DWORD)GetTickCount64();
		break;
	case WELCOME_BOX_STATE_DISAPPEAR:
		break;
	}
}

void CWelcomeBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == WELCOME_BOX_STATE_DISAPPEAR) return;

	if ((DWORD)GetTickCount64() - appearing_time > WELCOME_BOX_APPEARING_TIME)
	{
		SetState(WELCOME_BOX_STATE_DISAPPEAR);
	}
}

void CWelcomeBox::Render()
{
	if (state == WELCOME_BOX_STATE_DISAPPEAR) return;

	animation_set->at(WELCOME_ANI_FRAME)->Render(x, y);

	world->Render();
	lives[0]->Render();
	lives[1]->Render();

	if (mario) mario->Render();
}

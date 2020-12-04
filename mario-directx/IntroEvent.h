#pragma once
#include "GameObject.h"

struct CIntroEvent;
typedef CIntroEvent* LPINTROEVENT;
struct CIntroEvent
{
	CGameObject* object;
	DWORD starting_time;
	int state;
	int level;

	CIntroEvent(CGameObject* object, DWORD time, int state, int level)
	{
		this->object = object;
		this->starting_time = time;
		this->state = state;
		this->level = level;
	}

	static bool compare(const LPINTROEVENT& a, LPINTROEVENT& b)
	{
		return a->starting_time < b->starting_time;
	}
};

class CIntroEvents
{
	static CIntroEvents *__instance;

	unsigned int current_event;
	vector<LPINTROEVENT> intro_events;
public:
	CIntroEvents() { current_event = -1; }
	static CIntroEvents* GetInstance();

	void Add(LPINTROEVENT intro_event);
	vector<LPINTROEVENT> GetAll() { return intro_events; }
	LPINTROEVENT Get(int id) { return intro_events.at(id); }

	LPINTROEVENT PopNextEvent();
	LPINTROEVENT PeekNextEvent();
};

typedef CIntroEvents* LPINTROEVENTS;
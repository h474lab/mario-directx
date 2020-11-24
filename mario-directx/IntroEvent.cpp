#include "IntroEvent.h"
#include <algorithm>

CIntroEvents* CIntroEvents::__instance = NULL;

CIntroEvents* CIntroEvents::GetInstance()
{
	if (__instance == NULL) __instance = new CIntroEvents();
	return __instance;
}

void CIntroEvents::Add(LPINTROEVENT intro_event)
{
	intro_events.push_back(intro_event);
	std::sort(intro_events.begin(), intro_events.end(), CIntroEvent::compare);
}

LPINTROEVENT CIntroEvents::PopNextEvent()
{
	current_event++;
	if (current_event < intro_events.size())
		return intro_events.at(current_event);
	return NULL;
}

LPINTROEVENT CIntroEvents::PeekNextEvent()
{
	if (current_event + 1 < intro_events.size())
		return intro_events.at(current_event + 1);
	return NULL;
}

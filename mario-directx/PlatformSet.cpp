#include "PlatformSet.h"

CPlatformSet* CPlatformSet::__instance = NULL;

CPlatform::CPlatform(float l, float r)
{
	left = l;
	right = r;
}

float CPlatform::GetLeft()
{
	return (right - left <= 16 && right - left > 0) ? left - 8 : left;
}

float CPlatform::GetRight()
{
	return (right - left <= 16 && right - left > 0) ? right + 8 : right;
}

bool CPlatforms::CompareLeft(const LPPLATFORM& first, LPPLATFORM& second)
{
	if (first->GetLeft() == second->GetLeft())
		return (first->GetRight() < second->GetRight());

	return (first->GetLeft() < second->GetLeft());
}

void CPlatforms::MergeOverlappedPlatforms(int index)
{
	int leftEdgeCheck = 0, rightEdgeCheck = 0;

	// If current index is not at the beginning of platforms,
	// check if the previous value is overlapping the current one
	if (index > 0)
	{
		if (platforms[index - 1]->GetRight() >= platforms[index]->GetLeft())
		{
			platforms[index]->SetLeft(platforms[index - 1]->GetLeft());
			leftEdgeCheck = 1;
		}
	}

	// In case current index is not at the end of platform list
	if (index < platforms.size() - 1)
	{
		if (platforms[index + 1]->GetLeft() <= platforms[index]->GetRight())
		{
			platforms[index]->SetRight(platforms[index + 1]->GetRight());
			rightEdgeCheck = 1;
		}
	}

	// Remove previous or next value
	if (rightEdgeCheck) platforms.erase(platforms.begin() + index + 1);
	if (leftEdgeCheck) platforms.erase(platforms.begin() + index - 1);
}

void CPlatforms::SplitPlatformWithRange(int index, float end_1, float begin_2)
{
	// Insert new platform next to 'index' position
	if (begin_2 < platforms[index]->GetRight())
		platforms.insert(platforms.begin() + index + 1, new CPlatform(begin_2, platforms[index]->GetRight()));
	
	// Set the new value for the right of 'index' value
	if (end_1 > platforms[index]->GetLeft())
		platforms[index]->SetRight(end_1);
	else
		platforms.erase(platforms.begin() + index);
}

void CPlatforms::Add(float l, float r)
{
	// If platform list is empty, add a new one!
	if (platforms.empty())
	{
		platforms.push_back(new CPlatform(l, r));
		std::sort(platforms.begin(), platforms.end(), CompareLeft);
		return;
	}

	// Search for nearest left value
	if (l <= platforms[0]->GetLeft())
	{
		platforms.insert(platforms.begin(), new CPlatform(l, r));
	}
	else
	{
		for (int i = 0; i < platforms.size(); i++)
		{
			if (i == platforms.size() - 1 ||
				(platforms[i]->GetLeft() <= l &&
					platforms[i + 1]->GetLeft() >= l))
			{
				// Insert new platform into platform list
				platforms.insert(platforms.begin() + i + 1, new CPlatform(l, r));
				
				// If there are overlapping platforms created before, merge them
				MergeOverlappedPlatforms(i);
				return;
			}
		}
	}
}

void CPlatforms::Remove(float l, float r)
{
	// Platform list is empty or left > right, then there is nothing to remove
	if (platforms.empty() || l > r) return;

	// Split / remove with appropriate range
	for (int i = 0; i < platforms.size(); i++)
		if ((platforms[i]->GetLeft() <= l && platforms[i]->GetRight() >= l) ||
			(platforms[i]->GetLeft() <= r && platforms[i]->GetRight() >= r) ||
			(platforms[i]->GetLeft() >= l && platforms[i]->GetRight() <= r))
		{
			SplitPlatformWithRange(i, l, r);
		}
}

bool CPlatforms::CheckAvalable(float x)
{
	int left = 0, right = platforms.size() - 1;

	int i = 0;
	while (left <= right)
	{
		// Get the mid-value
		i = (right + left) / 2;

		// x is contained in platform number i
		if (platforms[i]->GetLeft() <= x && platforms[i]->GetRight() >= x)
			return true;

		// Platform might be on the right
		if (platforms[i]->GetRight() < x)
			left = i + 1;
		// Platform might be on the left
		else if (platforms[i]->GetLeft() > x)
			right = i - 1;
	}
	
	// Can't find any platform containing x
	return false;
}

CPlatformSet* CPlatformSet::GetInstance()
{
	if (__instance == NULL) __instance = new CPlatformSet();
	return __instance;
}

void CPlatformSet::Add(CGameObject* object)
{
	// Get object's position
	float x, y;
	object->GetPosition(x, y);

	// Calculate width and height
	float l, t, r, b;
	object->GetBoundingBox(l, t, r, b);
	float w = r - l, h = b - t;

	// If platform key does not exists, create a new one
	if (platforms.find(t) == platforms.end())
	{
		platforms.insert(make_pair(t, new CPlatforms(t)));
	}

	// Add new range into platform set
	platforms[y]->Add(x, x + w);
}

void CPlatformSet::Remove(CGameObject* object)
{
	// Get object's position
	float x, y;
	object->GetPosition(x, y);

	// Calculate width and height
	float l, t, r, b;
	object->GetBoundingBox(l, t, r, b);
	float w = r - l, h = b - t;

	// Remove if platform height is available
	if (platforms.find(y) != platforms.end())
	{
		platforms[y]->Remove(x, x + w);
	}
}

bool CPlatformSet::CheckAvailable(float x, float y)
{
	// If platform height is available
	if (platforms.find(y) != platforms.end())
		return platforms[y]->CheckAvalable(x);
	// If platform height is not available
	else return false;
}

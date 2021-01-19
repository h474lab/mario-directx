#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "GameObject.h"

using namespace std;

class CPlatform
{
	float left, right;
public:
	CPlatform(float l, float r);

	// Set Left or Right value
	void SetLeft(float value) { left = value; }
	void SetRight(float value) { right = value; }

	// Get Left or Right value
	float GetLeft() { return left; }
	float GetRight() { return right; }
};

typedef class CPlatform* LPPLATFORM;

// Contains a set of platforms with the same top value
// Notes: Cannot handle adding/removing objects with the same left, right and top value
class CPlatforms
{
	float top;
	vector<LPPLATFORM> platforms;

	static bool CompareLeft(const LPPLATFORM& first, LPPLATFORM& second);
	void MergeOverlappedPlatforms(int index);
	void SplitPlatformWithRange(int index, float end_1, float begin_2);
public:
	CPlatforms(float t) { top = t; }

	void Add(float l, float r);
	void Remove(float l, float r);
	bool CheckAvalable(float x);
};

class CPlatformSet
{
	// A combination of all platforms with key is 'top' value
	unordered_map<float, CPlatforms*> platforms;
public:
	void Add(CGameObject* object);
	void Remove(CGameObject* object);
	bool CheckAvailable(float x, float y);
	void Clear() { platforms.clear(); }
};


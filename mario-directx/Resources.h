#pragma once
#include "Game.h"

#define RESOURCES_MAX_LINE	1024

class CResources
{
private:
	static CResources* __instance;

	vector<wstring> objectList;

	LPCWSTR objectListPath;
	LPCWSTR texturesPath, spritesPath, animationsPath, animationSetsPath;
	LPCWSTR mapNodesPath;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_MAP_NODE_SETS(string line);

	void LoadTextures();
	void LoadSprites();
	void LoadAnimations();
	void LoadAnimationSets();
	void LoadMapNodes();
public:
	void SetTexturesPath(LPCWSTR texturesPath) { this->texturesPath = texturesPath; }
	void SetGameObjectList(LPCWSTR objectListPath);
	void SetSpritesPath(LPCWSTR spritesPath) { this->spritesPath = spritesPath; }
	void SetAnimationsPath(LPCWSTR animationsPath) { this->animationsPath = animationsPath; }
	void SetAnimationSetsPath(LPCWSTR animationSetsPath) { this->animationSetsPath = animationSetsPath; }
	void SetMapNodesPath(LPCWSTR mapNodesPath) { this->mapNodesPath = mapNodesPath; }

	void LoadResources();

	static CResources *GetInstance();
};
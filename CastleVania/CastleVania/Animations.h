#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Sprites.h"
#include "Game.h"
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

using namespace rapidxml;



class AnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	AnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef AnimationFrame *LPANIMATION_FRAME;

class Animation
{

	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	bool isComplete;
public:
	Animation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(string spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha = 255);
	void Render(int nx, float x, float y, int alpha);
	bool GetComplete() { return this->isComplete; }
	void ResetCurrentFrame() { currentFrame = -1; }
};

typedef Animation *LPANIMATION;

class Animations
{
	static Animations * __instance;

	unordered_map<string, LPANIMATION> animations;

public:
	void Add(string id, LPANIMATION ani);
	void LoadListAnimations(const char* filePath);
	LPANIMATION Get(string id);

	static Animations * GetInstance();
};

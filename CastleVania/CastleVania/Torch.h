#pragma once
#include "GameObject.h"
#define TORCH 1
#define TORCH_DELETE 2
#define TORCH_BBOX_WIDTH 32
#define TORCH_BBOX_HEIGHT 64

class Torch:public GameObject
{
	string ani;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> &coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &r, float &t, float &b);
};


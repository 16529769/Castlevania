#pragma once
#include "GameObject.h"
#define KNIFE_SPEED 0.5f
#define KNIFE_ATTACK 2
#include "Torch.h"
#include <cmath>
using namespace std;


class Knife :public GameObject
{
	bool attack = false;
	DWORD untouchable_start;
	int untouchable;
	float x_start, y_start;
public:
	Knife();
	~Knife();
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>& coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetPosition(float x, float y);
	void SetAttack(bool a) { this->attack = a; }
	void SetState(int state);
	void SetPositionStart(float x, float y) { this->x_start = x; this->y_start = y; }
	void Setnx(int nx) { this->nx = nx; }
};


#pragma once
#include "GameObject.h"
#define WHIP_BBOX_WIDTH 23
#define WHIP_BBOX_HEIGHT 23
#define WHIP 1 
#define WHIP_DELETE 2

class Whip:public GameObject
{
private:
	string ani;
	bool box = false;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> &coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &r, float &t, float &b);
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void Setnx(int nx) { this->nx = nx; }

	// xoa box 
	void SetBox(bool a) { this->box = a; }
};


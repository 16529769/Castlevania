#pragma once
#include "GameObject.h"
#define WHIP_BBOX_WIDTH 23
#define WHIP_BBOX_HEIGHT 23
#define WHIP_LEVEL_1 1 
#define WHIP_LEVEL_2 3
#define WHIP_LEVEL_3 4
#define WHIP_DELETE 2

class Whip:public GameObject
{
private:
	int level=1;
	string ani;
	bool box = false;
public:
	Whip() {
		AddAnimation("whip_lv1");
		AddAnimation("whip_lv2");
		//AddAnimation("whip_lv3");
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> &coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &r, float &t, float &b);
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void Setnx(int nx) { this->nx = nx; }
	void LevelUp() {
		if (level <2)
		{
			level++;
		}
	}
	// xoa box 
	void SetBox(bool a) { this->box = a; }
};


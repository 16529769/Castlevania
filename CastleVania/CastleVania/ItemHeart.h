#pragma once
#include "GameObject.h"
#define ITEMHEART_STATE 100
#define ITEMHEART_STATE_DIE 200
#define ITEMHEART_ANI				82
#define ITEMHGEART_ANI_DIE			83
#define ITEMHEART_BBOX_HEIHT        16
#define ITEMHGEART_BBOX_WIDTH		16
class ItemHeart:public GameObject
{
public:
	ItemHeart();
	
	//void Render();
	//virtual void SetState(int state);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
};


#pragma once
#include "GameObject.h"
#include "Brick.h"

#define BIG_HEART_BBOX_WIDTH		24
#define	BIG_HEART_BBOX_HEIGHT		20
#define SMALL_HEART_BBOX_WIDTH		16
#define	SMALL_HEART_BBOX_HEIGHT		16
#define ITEM_SMALL_HEART 0
#define ITEM_BIG_HEART 1

#define ITEMWHIP_BBOX_WIDTH 32
#define ITEMWHIP_BBOX_HEIGHT 32
#define ITEM_WHIP 2

#define ITEMKNIFE_BBOX_WIDTH 35
#define ITEMKNIFE_BBOX_HEIGHT 18
#define ITEM_KNIFE 3

class Items :public GameObject
{
public:
	Items(){
		AddAnimation("item_heart");
		AddAnimation("item_whip");
		AddAnimation("item_knife");
		vy = 0.1f;
	}
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void CreateItem();

};


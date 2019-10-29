#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.15f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT				500
#define SIMON_STATE_ATTACK          600
#define SIMON_STATE_SITATTACK		700
//#define SIMON_STATE_JUMPATTACK      800

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3
#define SIMON_ANI_ATTACK			4
#define SIMON_ANI_SITATTACK			5
//#define SIMON_ANI_JUMPATTACK        6

#define SIMON_ANI_DIE				8


#define SIMON_BBOX_WIDTH 60 
#define SIMON_BBOX_HEIGHT 63 

#define SIMON_UNTOUCHABLE_TIME 5000



class Simon : public GameObject
{
	int level;
	int untouchable;

	bool isJumping = false;
	bool isSitting;
	bool isAttacking;
	bool isComplete;

	DWORD untouchable_start;

	bool start = false;
	int startTime = 0;
	string ani;
	

public:
	Whip *whip;
	Simon() : GameObject()
	{
		nx = 1;
		untouchable = 0;
		whip = new Whip();
		whip->AddAnimation("whip_lv1");
		
	}
	bool isTouchGround;

	bool isDead = false;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	int GetY() { return y; }
	int GetVy() { return vy; }

	bool IsJumping() { return (state==SIMON_STATE_JUMP && isJumping ); }
	bool IsSitting() { return isSitting; }

	//danh
	bool IsAttacking() { return (state == SIMON_STATE_ATTACK && !this->isComplete); }
	bool IsSitAttacking() { return (state == SIMON_STATE_SITATTACK && !this->isComplete); }
	//bool IsJumpAttacking() { return (state == SIMON_STATE_JUMPATTACK && !this->isComplete); }


	void Sit() { isSitting = true; }
	void reset();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

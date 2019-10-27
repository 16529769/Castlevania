#include <algorithm>

#include "Simon.h"
#include "Game.h"
#include "Torch.h"




#pragma region Update 
void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	// Calculate dx, dy 
	GameObject::Update(dt);
	//Whip *whip;
	//this->whip->SetPosition(100, 100);

	//whip->SetPosition(this->x - 90, this->y);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	//if(state == SIMON_STATE_ATTACK)
	//	if (start == false)
	//	{
	//		start = true;
	//		startTime += GetTickCount();
	//	}
	//	else
	//	{
	//		float remain = GetTickCount() - startTime;

	//		if (remain > 350)
	//		{
	//			start = false;
	//			remain = 0;
	//			startTime = 0;
	//			reset();
	//			whip->reset();
	//			SetState(SIMON_STATE_IDLE);
	//		}
	//	}

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		

		/*if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;*/

		//block moi va cham 
		//x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brick *>(e->obj))
			{
				isTouchGround = true;
				// block 
				x += dx;
				if (e->ny != 0)
				{
					if (e->ny == -1.0f)
						vy = 0;
					else
						y += dy;
				}
			}
			else if (dynamic_cast<Torch *>(e->obj))
			{	
				if (e->nx != 0)
					x += dx;
				if (e->ny != 0)
				{
					if (e->ny == -1.0f && isTouchGround == false)
						y += dy;
					else
						vy = 0;
				}			
			}

			//va cham roi va nen 
			if (dynamic_cast<Torch *>(e->obj))
			{

			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
#pragma endregion Simon 


void Simon::Render()
{

	if (state == SIMON_STATE_DIE)
		ani = "simon_ani_idle";
	else if (state == SIMON_STATE_SIT)
	{
		ani = "simon_ani_sitting";
		vx = 0;
	}
	else if (state == SIMON_STATE_JUMP) {
		ani = "simon_ani_jumping";
	}
	else if (state == SIMON_STATE_ATTACK)
	{
		ani = "simon_ani_attacking";
	}

	else
		if (vx == 0)
		{
			if (nx > 0) ani = "simon_ani_idle";
			else ani = "simon_ani_idle";
		}
		else if (vx > 0)
		{
			ani = "simon_ani_walking";
			nx = 1;
		}
		else
		{
			ani = "simon_ani_walking";
			nx = -1;
		}


	int alpha = 255;
	if (untouchable) alpha = 128;
	if (IsAttacking())
	{
		whip->Setnx(this->nx);
		whip->SetPosition(this->x - 90, this->y + 1);
		whip->Render();
	}
	animations[ani]->Render(nx, x, y, alpha);
	
	this->isComplete = animations[ani]->GetComplete();

	//whip

	RenderBoundingBox();
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		isSitting = false;
		//whip->SetState(2);
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		//whip->SetState(2);
		isSitting = false;
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		//whip->SetState(2);

		vy = -SIMON_JUMP_SPEED_Y;
		isSitting = false;
		isJumping = true;
		isTouchGround = false;
		break;
	case SIMON_STATE_SIT:
		//whip->SetState(2);
		isSitting = true;
		isTouchGround = true;
		break;
	case SIMON_STATE_IDLE:
		//whip->SetState(2);
		isSitting = false;
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		//whip->SetState(2);
		break;
	
	case SIMON_STATE_ATTACK:
		//whip->SetState(1);
		vx = 0;
		break;
	}
	
}


void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
	
}

void Simon::reset()
{
	animations[ani]->ResetCurrentFrame();
}




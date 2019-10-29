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

		

		

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brick *>(e->obj))
			{
				isJumping = false;
				//// block 
				//x += dx;
				//if (e->ny != 0)
				//{
				//	if (e->ny == -1.0f)
				//		vy = 0;
				//	else
				//		y += dy;
				//}
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;


				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				
			}
			else if (dynamic_cast<Torch *>(e->obj))
			{	
				if (e->nx != 0)
					x += dx;
				if (e->ny != 0)
				{
					if (e->ny == -1.0f )
						y += dy;
					else
						vy = 0;
				}			
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
		this->whip->SetState(1);
	}
	else if (state == SIMON_STATE_SITATTACK)
	{
		ani = "simon_ani_sitattack";
		this->whip->SetState(1);
	}
	else if (state == SIMON_STATE_WALKING_RIGHT || state == SIMON_STATE_WALKING_LEFT)
	 {
		 ani = "simon_ani_walking";
	 }
	else if (state == SIMON_STATE_IDLE)
	 {
		 ani = "simon_ani_idle";
	 }
	/*else if (state == SIMON_STATE_JUMPATTACK)
	{
		ani = "simon_ani_jumpattack";
		this->whip->SetState(1);
	}*/

	/*else
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
		}*/


	int alpha = 255;
	if (untouchable) alpha = 128;

	if (IsAttacking())
	{
		whip->Setnx(this->nx);
		whip->SetPosition(this->x - 90, this->y + 1);
		whip->Render();
	}

	if(IsSitAttacking())
	{
		whip->Setnx(this->nx);
		whip->SetPosition(this->x - 90, this->y + 15);
		whip->Render();
	}


	/*if (IsJumpAttacking())
	{
		whip->Setnx(this->nx);
		whip->SetPosition(this->x - 90, this->y + 15);
		whip->Render();
	}*/


	animations[ani]->Render(nx, x, y, alpha);

	this->isComplete = animations[ani]->GetComplete();
	this->whip->SetBox(isComplete);
	RenderBoundingBox();
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		isSitting = false;
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:	
		isSitting = false;
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		isSitting = false;
		isJumping = true;
		isAttacking = false;
		break;
	case SIMON_STATE_SIT:	
		isSitting = true;
		break;
	case SIMON_STATE_IDLE:	
		isSitting = false;
		isJumping = false;
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;	
		break;
	
	case SIMON_STATE_ATTACK:	
		vx = 0;
		isAttacking = false;
		break;

	case SIMON_STATE_SITATTACK:
		//isAttacking = true;
		vx = 0;
		break;

	//case SIMON_STATE_JUMPATTACK:
	//	//vy = -SIMON_JUMP_SPEED_Y;
	//	vx = 0;
	//	break;
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




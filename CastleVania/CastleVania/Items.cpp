#include "Items.h"





void Items::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	// Check collision between item and ground (falling on ground)
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed


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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// collision of Simon and Candle -> do nothing -> update x;
			if (dynamic_cast<Brick *>(e->obj))
			{
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void Items::Render()
{
	switch (state)
	{
	case ITEM_BIG_HEART:
		animations["item_heart"]->Render(x,y);
		break;
	case ITEM_WHIP:
		animations["item_whip"]->Render(x, y);
		break;
	case ITEM_KNIFE:
		animations["item_knife"]->Render(x, y);
	}
	
	RenderBoundingBox();
	
}

void Items::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	switch (state)
	{
	case ITEM_BIG_HEART:
		r = x + BIG_HEART_BBOX_WIDTH;
		b = y + BIG_HEART_BBOX_HEIGHT;
		break;
	case ITEM_WHIP:
		r = x + BIG_HEART_BBOX_WIDTH;
		b = y + 32;
		break;
	case ITEM_KNIFE:
		r = x + ITEMKNIFE_BBOX_WIDTH;
		b = y + ITEMKNIFE_BBOX_HEIGHT;
		break;
	}
		
	
	
}

void Items::CreateItem()
{
	if (x < 320)
	{
		SetPosition(x, y + 25);
		SetState(ITEM_BIG_HEART);
	}
	else if (x > 320&&x<800)
	{
		SetState(ITEM_WHIP);
	}
	else if (x >= 800)
	{
		SetState(ITEM_KNIFE);
	}
}



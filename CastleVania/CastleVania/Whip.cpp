#include "Whip.h"
#include "Torch.h"



void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>& coObjects)
{
	GameObject::Update(dt);
	if (box == true)
	{
		for (UINT i = 0; i < coObjects.size(); i++)
		{
			LPGAMEOBJECT e = coObjects[i];
			if (dynamic_cast<Torch *>(e))
			{
				if (this->AABBx(e) == true)
				{
					if (e->GetState() != TORCH_DELETE)
					{
						e->SetState(TORCH_DELETE);
						//e->SetDie(true);
					}
					coObjects[i]->SetDie(true);
				}
			}
		} 
	}
	
}


void Whip::Render()
{
	if (state == WHIP)
	{
		ani = "whip_lv1";
		animations[ani]->Render(nx, x, y, 255);
		RenderBoundingBox();
	}
}

void Whip::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x+140;
	t = y+15;
	//r = x + WHIP_BBOX_WIDTH;
	r = l + 55;
	//b = y + WHIP_BBOX_HEIGHT;
	b = t + 18;
}

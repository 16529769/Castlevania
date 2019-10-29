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
						
					}
					coObjects[i]->SetDie(true);
				}
			}
		} 
	}	
}


void Whip::Render()
{
	string ani;
	switch (level)
	{
	case 1:
		ani = "whip_lv1";
		break;
	case 2:
		ani = "whip_lv2";
		break;
	/*case 3:
		ani = "whip_lv3";
	
		break;*/
	default:
		break;
	}
	animations[ani]->Render(nx,x, y,255);
	RenderBoundingBox();
}

void Whip::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	switch (state)
	{
	case WHIP_LEVEL_1:

		if (nx == 1)
		{
			l = x + 140;
			t = y + 15;
			r = l + 55;
			b = t + 18;
		}
		else if (nx == -1)
		{
			l = x + 50;
			t = y + 15;
			r = l + 55;
			b = t + 18;
		}
		break;

	case WHIP_LEVEL_2:

		if (nx == 1)
		{
			l = x + 140;
			t = y + 15;
			r = l + 55;
			b = t + 18;
		}
		else if (nx == -1)
		{
			l = x + 50;
			t = y + 15;
			r = l + 55;
			b = t + 18;
		}
		break;
	}
	
}


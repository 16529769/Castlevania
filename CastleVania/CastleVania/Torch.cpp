#include "Torch.h"




void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>& coObjects)
{
	
}

void Torch::Render()
{
	if (state == TORCH)
	{
		ani = "torch_ani";
		animations[ani]->Render(x, y);
		RenderBoundingBox();
	}
	
}

void Torch::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x ;
	t = y;
	r = x + TORCH_BBOX_WIDTH;
	//r = l + 60 + 20;
	b = y + TORCH_BBOX_HEIGHT;
	//b = t + 18;
}

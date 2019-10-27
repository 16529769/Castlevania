#include "Whip.h"




void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>& coObjects)
{

}


void Whip::Render()
{

	ani = "whip_lv1";
	animations[ani]->Render(nx,x, y,255);
	//RenderBoundingBox();
	
}

void Whip::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + WHIP_BBOX_WIDTH;
	//r = l + 60 + 20;
	b = y + WHIP_BBOX_HEIGHT;
	//b = t + 18;
}

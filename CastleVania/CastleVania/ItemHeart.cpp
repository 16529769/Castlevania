#include "ItemHeart.h"



ItemHeart::ItemHeart()
{
}

void ItemHeart::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + ITEMHGEART_BBOX_WIDTH;
	b = y + ITEMHEART_BBOX_HEIHT;
}




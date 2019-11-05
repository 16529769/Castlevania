#include "Knife.h"



Knife::Knife()
{
	vx = 0.5f;
	AddAnimation("item_knife");
}


Knife::~Knife()
{
}

void Knife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	if (nx > 0)
	{
		x += dx;
	}
	else
		x -= dx;

	double distance = sqrt(pow(x - x_start, 2.0f) + pow(y - y_start, 2.0f));
	if (distance > 150)
	{
		this->die = true;
	}
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<Torch *>(e))
		{
			if (AABBx(e) == true)
			{
				e->die = true;
				this->die = true;
			}
		}
	}
}


void Knife::Render()
{
	string ani;
	
	animations["item_knife"]->Render(nx*-1,x, y,255);
	RenderBoundingBox();
	
}

void Knife::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + 35;
	b = t + 18;
}

void Knife::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y + 18;
}

void Knife::SetState(int state)
{
	GameObject::SetState(state);	
}

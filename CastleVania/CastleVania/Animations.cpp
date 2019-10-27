#include "Animations.h"

void Animation::Add(string spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

void Animation::Render(int nx,float x, float y, int alpha)
{
	this->isComplete = false;
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size() - 1)
			{
				this->isComplete = true;
			}
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(nx,x, y, alpha);
}

Animations * Animations::__instance = NULL;

Animations * Animations::GetInstance()
{
	if (__instance == NULL) __instance = new Animations();
	return __instance;
}

void Animations::Add(string id, LPANIMATION ani)
{
	animations[id] = ani;
}

void Animations::LoadListAnimations(const char * filePath)
{
	rapidxml::file<> xmlFile(filePath);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("Animations");
	//xml_node<>* animationNode = rootNode->first_node("animation");
	int i = 0;
	for (xml_node<>* animationNode = rootNode->first_node(); animationNode; animationNode = animationNode->next_sibling()) {

		LPANIMATION ani;

		int defaultTime = atoi(animationNode->first_attribute("defaultTime")->value());
		string aniId = string(animationNode->first_attribute("ID")->value());
		ani = new Animation(defaultTime);

		xml_node<>* frameNode = rootNode->first_node("frame");
		for (xml_node<>* frameNode = animationNode->first_node("frame"); frameNode; frameNode = frameNode->next_sibling())
		{
			string spriteId = string(frameNode->first_attribute("spriteID")->value());
			ani->Add(spriteId);
		}

		
		Add(aniId, ani);
	}
}

LPANIMATION Animations::Get(string id)
{
	return animations[id];
}



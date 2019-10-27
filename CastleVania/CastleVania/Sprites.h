#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

using namespace std;
using namespace rapidxml;

class Sprite
{
	string id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	Sprite(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha = 255);
	void Draw(int nx, float x, float y, int alpha);
};

typedef Sprite * LPSPRITE;

/*
	Manage sprite database
*/
class Sprites
{
	static Sprites * __instance;

	unordered_map<string, LPSPRITE> sprites;

public:
	void Add(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void LoadSpriteSheet(const char* filePath, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(string id);
	LPSPRITE &operator[](string idSprite) { return sprites[idSprite]; }
	static Sprites * GetInstance();
};


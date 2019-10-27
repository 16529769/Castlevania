#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Texture.h"
#include "Sprites.h"

class TileMap
{
	LPDIRECT3DTEXTURE9 texMap;
	// chieu rong 
	int map_Width;
	// chieu cao
	int map_Height;
	// so hang
	int nums_row;
	//so cot
	int nums_col;
	// chieu rong cua tile
	int tile_Width;
	// chieu cao cua tile
	int tile_Height;
	LPCWSTR filePath_tex;
	LPCWSTR filePath_data;
	// ID cua tile map
	int ID;
public:
	// ma tran du lieu map
	vector<vector<int>> map_Data;
	// luu cac tile
	Sprites * sprites;
	TileMap(LPCWSTR filePath_data, int map_width, int map_height, int tile_width, int tile_height);
	// load tat ca cac block tile luu vao sprites
	void LoadResources();
	// load ma tran du lieu map
	/*void Load_MapData();*/
	// ve tat ca cac tile nam trong camera
	void Draw(D3DXVECTOR2 camPosition);
	int GetMapWidth() { return map_Width; }
	void SetTileMap(LPDIRECT3DTEXTURE9 texTM) { this->texMap = texTM; }


	~TileMap();
};
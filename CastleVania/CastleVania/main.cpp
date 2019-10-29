#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "GameObject.h"
#include "Texture.h"
#include "Simon.h"
#include "KeyboardEvent.h"
#include "Brick.h"
#include "TileMap.h"
#include "Whip.h"
#include "Torch.h"
#include "Items.h"


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define MAX_FRAME_RATE 120



Game *game;
Simon *simon;
TileMap * tilemap;
//Whip * whip;
vector<LPGAMEOBJECT> objects;
vector<LPGAMEOBJECT> items;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{

	Textures * textures = Textures::GetInstance();
	textures->Add(200, L"textures\\simon\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(300, L"textures\\ground\\brick.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(400, L"textures\\Map\\Scene1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(500, L"textures\\whip\\whip.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(600, L"textures\\Torch\\Torch.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(100, L"textures\\red.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(700, L"textures\\item\\items.png", D3DCOLOR_XRGB(255, 0, 255));





	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();

	auto texMap = textures->Get(400);
	tilemap = new TileMap(L"textures\\Map\\Scene1_map.txt", 1536, 384, 32, 32);
	tilemap->SetTileMap(texMap);
	tilemap->LoadResources();




	auto texSimon = textures->Get(200);
	sprites->LoadSpriteSheet("textures\\simon\\simon.xml", texSimon);
	

	auto texBrick = textures->Get(300);
	sprites->LoadSpriteSheet("textures\\ground\\brick.xml", texBrick);

	auto texWhip = textures->Get(500);
	sprites->LoadSpriteSheet("textures\\whip\\whip.xml", texWhip);

	auto texTorch = textures->Get(600);
	sprites->LoadSpriteSheet("textures\\Torch\\Torch.xml", texTorch);

	auto texItem = textures->Get(700);
	sprites->LoadSpriteSheet("textures\\item\\items.xml", texItem);
	
	

	animations->LoadListAnimations("textures\\Torch\\Torch_ani.xml");
	animations->LoadListAnimations("textures\\simon\\simon_animation.xml");
	animations->LoadListAnimations("textures\\ground\\brick_animation.xml");
	animations->LoadListAnimations("textures\\whip\\whip_ani.xml");
	animations->LoadListAnimations("textures\\item\\items_ani.xml");

	simon = new Simon();
	simon->AddAnimation("simon_ani_idle");		// idle
	simon->AddAnimation("simon_ani_walking");		// walk
	simon->AddAnimation("simon_ani_sitting");		// sit
	simon->AddAnimation("simon_ani_jumping");  // jumping
	simon->AddAnimation("simon_ani_attacking"); //attack
	simon->AddAnimation("simon_ani_sitattack"); //sit attack
	simon->AddAnimation("simon_ani_effect"); //nhap nhay 

	simon->SetState(SIMON_STATE_IDLE);
	simon->SetPosition(0, 0);

	objects.push_back(simon);

	for (int i = 0; i < 50; i++)
	{
		Brick *brick = new Brick();
		brick->AddAnimation("brick_idle");
		brick->SetPosition(i * 32, 340.0f);
		objects.push_back(brick);
	}

	for (int i = 0; i < 5; i++)
	{
		Torch *torch = new Torch();
		torch->AddAnimation("torch_ani");
		torch->SetPosition(100 + i*200, 340 - 64);
		objects.push_back(torch);
	}
	
}



void Control() {
	
	if (simon->isDead)
	{
		return;
	}
	if (simon->IsAttacking())
	{
		return;
	}
	if (simon->IsSitAttacking())
	{
		return;
	}
	
	
	if (simon->IsEffectItem())
	{
		return;
	}

	
	if (IsKeyPress(DIK_E)) {
		if (simon->GetState() == SIMON_STATE_SIT)
		{
			simon->SetState(SIMON_STATE_SITATTACK);
		}
		else
		{
			simon->SetState(SIMON_STATE_ATTACK);
		}
	}
	
	else if (simon->IsJumping())
	{
		return;
	}
	
	else if (IsKeyPress(DIK_SPACE) && (!simon->IsSitting()))
	{
		simon->SetState(SIMON_STATE_JUMP);
	}
	
	
	else if (IsKeyDown(DIK_LEFT)) {
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else if (IsKeyDown(DIK_RIGHT)) {
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (IsKeyDown(DIK_DOWN)) {
		simon->SetState(SIMON_STATE_SIT);
	}
	else {
		simon->SetState(SIMON_STATE_IDLE);
	}
	
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	Control();

	for (int i = 1; i < objects.size() + items.size(); i++)
	{
		if (i < objects.size())
		{
			coObjects.push_back(objects[i]);

		}
		else 
			coObjects.push_back(items[i- objects.size()]);
	}
	simon->whip->Update(dt, objects);
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->die == true)
		{	
			if (objects[i]->haveItem)
			{
				Items *item = new Items();
				item->SetPosition(objects[i]->x, objects[i]->y);
				item->CreateItem();
				items.push_back(item);
			}
			//objects[i]->Update(dt, &coObjects);
			objects.erase(objects.begin() + i);
		}
		else
		{
			objects[i]->Update(dt, &coObjects);
		}
	}

	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->die == true)
		{
			items.erase(items.begin() + i);
		}else
			items[i]->Update(dt, &coObjects);
	}
	//simon->Update(dt, &coObjects);
	
	if (simon->GetX() < 10) {
		simon->SetPosition(10, simon->GetY());
	}
	else if (simon->GetX() >= 1460) {
		simon->SetPosition(1460, simon->GetY());
	}
	if (simon->GetX() >= 320 && simon->GetX() < 1200)
	{
		game->SetCamPos(simon->x - 320, 0);
	}
	float cx, cy;
	cx = simon->GetX();
	cy = simon->GetY();
	if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tilemap->GetMapWidth())
	{
		game->SetCamPos(cx - SCREEN_WIDTH / 2, 0);
	}
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		tilemap->Draw(game->GetCamPos());

		for (int i = 1; i < objects.size(); i++)
			objects[i]->Render();
		for (int i = 0; i < items.size(); i++)
		{
			items[i]->Render();
		}
		simon->Render();
		
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			PollKeyboard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = Game::GetInstance();
	game->Init(hWnd);

	InitDirectInput();
	InitKeyboard(hWnd);
	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT , SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
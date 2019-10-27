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


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 255, 200)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define MAX_FRAME_RATE 120



Game *game;
Simon *simon;
TileMap * tilemap;
//Whip * whip;
vector<LPGAMEOBJECT> objects;


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
	textures->Add(400, L"textures\\Map\\hello1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(500, L"textures\\whip\\whip.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(600, L"textures\\Torch\\Torch.png", D3DCOLOR_XRGB(255, 0, 255));




	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();

	auto texMap = textures->Get(400);
	tilemap = new TileMap(L"textures\\Map\\mapcut2.txt", 1536, 384, 32, 32);
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

	animations->LoadListAnimations("textures\\Torch\\Torch_ani.xml");
	animations->LoadListAnimations("textures\\simon\\simon_animation.xml");
	animations->LoadListAnimations("textures\\ground\\brick_animation.xml");
	animations->LoadListAnimations("textures\\whip\\whip_ani.xml");


	simon = new Simon();
	simon->AddAnimation("simon_ani_idle");		// idle
	simon->AddAnimation("simon_ani_walking");		// walk
	simon->AddAnimation("simon_ani_sitting");		// sit
	simon->AddAnimation("simon_ani_jumping");  // jumping
	simon->AddAnimation("simon_ani_attacking"); //attack
	//simon->SetState(SIMON_STATE_IDLE);
	simon->SetPosition(0, 0);
	objects.push_back(simon);

	for (int i = 0; i < 50; i++)
	{
		Brick *brick = new Brick();
		brick->AddAnimation("brick_idle");
		brick->SetPosition(i * 32, 320.0f);
		objects.push_back(brick);
	}

	for (int i = 0; i < 5; i++)
	{
		Torch *torch = new Torch();
		torch->AddAnimation("torch_ani");
		torch->SetPosition(300 + i*200, 320 - 64);
		objects.push_back(torch);
	}
	/*Torch *torch = new Torch();
	torch->AddAnimation("torch_ani");
	torch->SetPosition(300 , 320 - 64);
	objects.push_back(torch);
*/
	


}
//class CSampleKeyHander : public CKeyEventHandler
//{
//	virtual void KeyState(BYTE *states);
//	virtual void OnKeyDown(int KeyCode);
//	virtual void OnKeyUp(int KeyCode);
//};
//
//CSampleKeyHander * keyHandler;
//
//void CSampleKeyHander::OnKeyDown(int KeyCode)
//{
//
//	if (simon->IsJumping()) return;
//	switch (KeyCode)
//	{
//	
//	case DIK_D:
//		simon->SetState(SIMON_STATE_ATTACK);
//		break;
//
//	}
//
//}


void Control() {
	if (simon->IsAttacking())
	{
		return;
	}
	 if (simon->isDead || simon->isTouchGround == false) {
		return;
	} else if (IsKeyPress(DIK_SPACE)&&(!simon->IsSitting())) {

		simon->SetState(SIMON_STATE_JUMP);
	}
	else if (IsKeyDown(DIK_RIGHT)) {
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (IsKeyDown(DIK_LEFT)) {
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else if (IsKeyDown(DIK_DOWN)) {
		simon->SetState(SIMON_STATE_SIT);
		
	}
	else if (IsKeyDown(DIK_D)) {
		simon->SetState(SIMON_STATE_ATTACK);
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
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	//simon->Update(dt, &coObjects);
	if (simon->x >= 320)
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
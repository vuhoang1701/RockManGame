#include "Game.h"


CGame::CGame(void)
{
	d3d = NULL;
	d3ddev = NULL;
	backbuffer = NULL;
}


CGame::~CGame(void)
{
	if(d3d)
		d3d->Release();
	if(d3ddev)
		d3ddev->Release();
	if(backbuffer)
		backbuffer->Release();
}

HWND CGame::GetWindowHandle()
{
	return hwnd;
}

LPD3DXSPRITE CGame::GetSpriteHandle()
{
	return sprite_handle;
}

LPDIRECT3DDEVICE9 CGame::GetD3DDevice()
{
	return d3ddev;
}
//=====================
bool CGame::Init_Window(HINSTANCE hInstance)
{
	// Register to windows
	WNDCLASS wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wndclass.hIcon = LoadIcon(NULL, IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WinProc;
	wndclass.lpszClassName = NAME;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	if (FAILED(RegisterClass(&wndclass)))
		return FALSE;

	// Create window
	hwnd = CreateWindow(NAME, 
		NAME,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		this
		);
	if (!hwnd)
		return FALSE;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return TRUE;
}

LRESULT CALLBACK CGame::WinProc(HWND m_hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(m_hWnd, iMessage, wParam, lParam);
}

//======================

bool CGame::Init_Direct3D()
{

	//initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		MessageBox(hwnd, "Error initializing Direct3D", "Error", MB_OK);
		return 0;
	}

	//set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS m_d3d_paramters; 
	ZeroMemory(&m_d3d_paramters, sizeof(m_d3d_paramters));

	m_d3d_paramters.Windowed = TRUE;
	m_d3d_paramters.SwapEffect = D3DSWAPEFFECT_COPY;
	m_d3d_paramters.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3d_paramters.BackBufferCount = 1;
	m_d3d_paramters.BackBufferWidth = SCREEN_WIDTH;
	m_d3d_paramters.BackBufferHeight = SCREEN_HEIGHT;
	m_d3d_paramters.hDeviceWindow = hwnd;
	m_d3d_paramters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	//create Direct3D device (software)
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&m_d3d_paramters, 
		&d3ddev);

	if (d3ddev == NULL)
	{
		return FALSE;
	}
	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	D3DXCreateSprite(d3ddev, &sprite_handle);
	return TRUE;
}
//=================

int CGame::Game_Init()
{
	if(!Init_Direct3D())
	return 0;
	HRESULT hr = D3DXCreateSprite(d3ddev,&sprite_handle);
	if(hr != D3D_OK)
		return 0;
	back = new Texture(d3ddev);
	back->LoadTexture("..\\Data\\background.jpg",NULL, 1537, 224);
	
	Rockman = new CRockman(400,sprite_handle,d3ddev);
	obj = new CGameObj(0,100, 100, Rockman->_Image);
	rm = new CRockmanObj(0,30,30,Rockman->_Image,0.5,2);
	if(back->LoadTexture("..\\Data\\background.jpg",NULL, 1537, 224) == NULL)
		return 0;
	Cam = new CCamera();
	d3ddev->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backbuffer);
	return 1;
	
}
CCamera* CGame::GetCam()
{
	return Cam;
}
void CGame::Game_Run()
{
	MSG msg;
	if(Init_Keyboard(hwnd) == 0)
		return ;
	int done = 0;
	   while(!done)
		{
			
		  if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				if(msg.message == WM_QUIT)
					done = 1;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		  
			else
			{
				HRESULT hr = d3ddev->BeginScene();
				if(SUCCEEDED(hr))
					{
						int now = GetTickCount();
						Poll_Keyboard();
						d3ddev->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,255,255),1,0);
						D3DXVECTOR3 pos = Cam->GetPointTransform(0,224);
						sprite_handle->Begin(D3DXSPRITE_ALPHABLEND);
						rm->Update(Cam, now);
						sprite_handle->Draw(
						back->GetTexture(),
						NULL,
						NULL,
						&pos,
						D3DCOLOR_XRGB(255,255,255)
						);
						//obj->Render(sprite_handle, Cam);
						//[Rockman->Update(Cam);
						//Rockman->Render(sprite_handle, Cam);
						
						
						rm->Render(sprite_handle, Cam);
						sprite_handle->End();
					}
					d3ddev->EndScene();
					d3ddev->Present(NULL,NULL,NULL,NULL);
			  }
	
		
	}
		
}
void CGame::Game_End()
{

}
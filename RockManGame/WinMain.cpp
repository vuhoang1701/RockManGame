#include "Game.h"
#include "dxinput.h"
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR nCmdLine,int nCmdShow)
{
	CGame* game = new CGame();
	if(!game->Init_Window(hInstance))
		return 0;
	if(!Init_DirectInput(game->GetWindowHandle()))
		return 0;

	game->Game_Init();
	game->Game_Run();
	return 0;
}
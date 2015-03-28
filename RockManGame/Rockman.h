#pragma once
#include "dxinput.h"
#include "Sprite.h"
#include "Camera.h"
class CRockman
{
	
	int _RockmanX;
	int _RockmanY;
	int _RockmanV;
	LPD3DXSPRITE _spritehanlde;
	bool right;
	int countdelay;
	int delay;
	LPDIRECT3DDEVICE9 _d3ddev;
public:
	Sprite* _Image;
	CRockman(int,LPD3DXSPRITE,LPDIRECT3DDEVICE9);
	void Update(CCamera*);
	void Render(LPD3DXSPRITE ,CCamera*);
	void OnKeyDown(int);
	~CRockman(void);
};


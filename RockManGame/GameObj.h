#pragma once
#include "Sprite.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Camera.h"
class CGameObj
{
protected:
	int _Id;
	bool _isAlive;
	RECT _Bound;
	D3DXVECTOR2 _Pos;
	Sprite *_Spr;

	
public:
	CGameObj(void);
	CGameObj(int, int, int, Sprite*);
	void Render(LPD3DXSPRITE, CCamera*);
	~CGameObj(void);
};


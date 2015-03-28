#pragma once


#include <d3d9.h>
#include <d3dx9.h>
#include "Texture.h"
class Sprite
{
protected:
	Texture* _Image;

	int _Count;
	int _SpritePerRow;
public:
	int _Width;
	int _Height;
	int _Index;
	Sprite(){};
	void SetDevice(LPDIRECT3DDEVICE9);
	Sprite(LPDIRECT3DDEVICE9 , char*,int ,int ,int ,int );
	void Next();
	void Reset();
	void Render(LPD3DXSPRITE,D3DXVECTOR3);
	~Sprite();
};


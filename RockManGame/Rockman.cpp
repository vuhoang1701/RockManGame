#include "Rockman.h"



CRockman::CRockman(int h,LPD3DXSPRITE spritehandle,LPDIRECT3DDEVICE9 d3ddev)
{
	
	_Image = new Sprite(d3ddev,"..\\Data\\Megaman_Run.png",288/6,48,6,6);
	_spritehanlde = spritehandle;
	_d3ddev = d3ddev;
	_RockmanX = 100;
	_RockmanY = 800;
	_RockmanV = 4;
	_Image->_Index = 5;
	right = true;
	countdelay = 6;
	 delay = 0;
}


void CRockman::Render(LPD3DXSPRITE spritehandle, CCamera* Cam)
{
	D3DXVECTOR3 pos = Cam->GetPointTransform(_RockmanX, _RockmanY);
	_Image->Render(spritehandle,pos);
	

}
void CRockman::Update(CCamera *cam)
{
		if(Key_Down(DIK_ESCAPE))
				PostQuitMessage(0);
				if (Key_Down(DIK_L) )
				{
					right = true;
					if(++delay - countdelay >10)
					{
						delay = 0;	
						if(++_Image->_Index > 5)
							_Image->_Index = 3;
			
					}
							_RockmanX += _RockmanV;
				}	
				else if (Key_Down(DIK_J))
				{
					right = false;
					if(++delay>countdelay)
					{
						delay = 0;
						if(--_Image->_Index < 6)
							_Image->_Index = 7;
					}
					_RockmanX -= _RockmanV;
				}
				else if(Key_Down(DIK_K))
				{
					if(right) _Image->_Index = 4;
					else _Image->_Index = 5;
				}
				else if(Key_Down(DIK_I))
				{
					if(right) _Image->_Index = 1;
					else _Image->_Index = 8;
				}
				else
				{
					
					if(++delay - countdelay>70)
					{
						delay = 0;
						if(++_Image->_Index > 1)
							_Image->_Index = 0;
					}
				}
				cam->Update(_RockmanX);
}
CRockman::~CRockman(void)
{
	_Image->~Sprite();
}

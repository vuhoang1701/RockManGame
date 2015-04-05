#pragma once
#include "d3dx9.h"
class CCamera
{
private:
	D3DXMATRIX _MatrixTransform;
public:
	D3DXVECTOR2 _pos;
	int _width;
	int _height;
	CCamera();
	~CCamera(void);
	void Update(int x,int y);
	D3DXVECTOR3 GetPointTransform(int x, int y);
	
};

#include "Camera.h"


CCamera::CCamera()
{
	_pos.x = 0;
	_pos.y = 224;
	_width = 256;
	_height = 224;
	D3DXMatrixIdentity(&_MatrixTransform);
	_MatrixTransform._22 = -1;
}
CCamera::~CCamera(void)
{
}

void CCamera::Update(int x,int y)
{
	_pos.y = y + _height - 50;
	_pos.x = x - _width/2;
	if(_pos.x < 0)
		_pos.x = 0;
}

D3DXVECTOR3 CCamera::GetPointTransform(int x, int y)
{
	_MatrixTransform._41 = - _pos.x;
	_MatrixTransform._42 = _pos.y;

	D3DXVECTOR3 pos(x, y, 0);
	D3DXVECTOR4 v_result;

	D3DXVec3Transform(&v_result, &pos, &_MatrixTransform);

	return D3DXVECTOR3(v_result.x, v_result.y,0);
}

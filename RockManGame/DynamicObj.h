#pragma once
#include "GameObj.h"

using namespace std;
class DynamicObj :
	public CGameObj
{
protected:
	enum Direction
	{
		left,
		right,
		top,
		bot,
	};
	Direction _Dir;
	float	m_velocX;
	float	m_velocY;

public:
	virtual void SetVeloc(float x,float y);
	virtual D3DXVECTOR2 GetVeloc();

	DynamicObj(int id,float x,float y,Sprite* sprite,float Vel_X,float Vel_y);
	DynamicObj(void);
	virtual void Update(CCamera*, int time);
	~DynamicObj(void);
};


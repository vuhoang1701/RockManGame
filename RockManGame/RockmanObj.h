#pragma once
#include "DynamicObj.h"
#include "dxinput.h"
class CRockmanObj:public DynamicObj
{
protected:
	int countdelay;
	int delay;
	int timerun;
	float gravity;
	bool onGround;
public:
	CRockmanObj(void);
	CRockmanObj(int id, int x, int y, Sprite* spr, float velx, float vely);
	void SetVeloc(int velx, int vely);
	D3DXVECTOR2 GetVeloc();
	void Update(CCamera*, int time);
	~CRockmanObj(void);
};


#include "RockmanObj.h"


CRockmanObj::CRockmanObj(void)
{
}
CRockmanObj::CRockmanObj(int id, int x, int y, Sprite* spr, float velx, float vely):DynamicObj(id, x, y, spr, velx, vely)
{
	onGround = true;
	timerun = 0;
	countdelay = 0;
	delay = 0;
	gravity = - 0.5; 
};
void CRockmanObj::SetVeloc(int velx, int vely)
{
	this->m_velocX = velx;
	this->m_velocY = vely;
}
D3DXVECTOR2 CRockmanObj::GetVeloc()
{
	D3DXVECTOR2 a(this->m_velocX, this->m_velocY);
	return a;
}
void CRockmanObj::Update(CCamera *Cam, int time)
{
	float deltatime = time - timerun;
	if(deltatime >20)
	{

		m_velocY +=	gravity*(deltatime/15);
		_Pos.y += m_velocY;
		if(_Pos.y <= 50)
			{
				onGround = true;
				_Pos.y = 50;
				m_velocY = 0;
			}		
		
		if(Key_Down(DIK_ESCAPE))
				PostQuitMessage(0);
		if (Key_Down(DIK_L) && onGround == true)
		{
			_Dir = right;
			if(++delay - countdelay >3)
			{
				delay = 0;	
				if(++this->_Spr->_Index > 5)
					this->_Spr->_Index = 3;
			
			}
			this->_Pos.x += this->m_velocX*(deltatime/15);
		}
		else if(Key_Down(DIK_L) && onGround == false)
		{
			this->_Pos.x += this->m_velocX*(deltatime/15);
		}
		else if (Key_Down(DIK_J))
		{
			_Dir = left;
			if(++delay>countdelay)
			{
				delay = 0;
				if(--this->_Spr->_Index < 6)
					this->_Spr->_Index = 7;
			}
			this->_Pos.x -= this->m_velocX*deltatime;
		}
		//test==================================
		else if (Key_Down(DIK_I))
		{
			_Dir = left;
			if(++delay>countdelay)
			{
				delay = 0;
				if(--this->_Spr->_Index < 6)
					this->_Spr->_Index = 7;
			}
			this->_Pos.y += this->m_velocX*deltatime;
		}
		else if (Key_Down(DIK_K))
		{
			_Dir = left;
			if(++delay>countdelay)
			{
				delay = 0;
				if(--this->_Spr->_Index < 6)
					this->_Spr->_Index = 7;
			}
			this->_Pos.y -= this->m_velocX*deltatime;
		}
		//============================================
		else if( Key_Down(DIK_SPACE) && onGround== true)
		{
			m_velocY = 10;
			onGround= false;
		}

		else
		{
					
			if(++delay - countdelay>70)
			{
				delay = 0;
				if(++this->_Spr->_Index > 1)
					this->_Spr->_Index = 0;
			}
		}
	
				
				
				Cam->Update(_Pos.x,_Pos.y);
				timerun = time;
	}


	
}


CRockmanObj::~CRockmanObj(void)
{
}

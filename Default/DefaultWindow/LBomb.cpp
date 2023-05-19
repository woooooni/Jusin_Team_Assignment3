#include "stdafx.h"
#include "LBomb.h"
#include	"ObjMgr.h"
#include	"TimeMgr.h"


CLBomb::CLBomb()
{
}


CLBomb::~CLBomb()
{
}

void CLBomb::Initialize(void)
{
	m_eItemType = ITEM_BOMB;
	m_tInfo.vSize = { 200, 200, 0 };

	m_fCreatedTime = 0.f;
	m_fMaxExistTime = 3.f;
					
}

int CLBomb::Update(void)
{
	m_fCreatedTime += DELTA_TIME;

	Check_Dead();

	return 0;
}

void CLBomb::Late_Update(void)
{
}

void CLBomb::Render(HDC hDC)
{
	HBRUSH myB = CreateSolidBrush(RGB(255, 0, 50));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f),
		(int)(m_tInfo.vPos.y - m_tInfo.vSize.y* 0.5f),
		(int)(m_tInfo.vPos.x + m_tInfo.vSize.x* 0.5f),
		(int)(m_tInfo.vPos.y + m_tInfo.vSize.y* 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);


	myB = CreateSolidBrush(RGB(255, 255, 0));
	oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - 50 * 0.5f),
		(int)(m_tInfo.vPos.y -50* 0.5f),
		(int)(m_tInfo.vPos.x + 50* 0.5f),
		(int)(m_tInfo.vPos.y + 50* 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);
}

void CLBomb::Release(void)
{
}

void CLBomb::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}

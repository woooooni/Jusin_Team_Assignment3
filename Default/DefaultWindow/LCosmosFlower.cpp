#include "stdafx.h"
#include "LCosmosFlower.h"
#include	"TimeMgr.h"


CLCosmosFlower::CLCosmosFlower()
{
}


CLCosmosFlower::~CLCosmosFlower()
{

}

void CLCosmosFlower::Initialize(void)
{
	m_tInfo.vSize = { 60, 60, 0 };

	m_fSpeed = 100.f;

}

int CLCosmosFlower::Update(void)
{
	if (m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f < 0)
		m_bDead = true;

	if (m_tInfo.vDir != VECTOR(0, 0, 0))
	{
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * DELTA_TIME;
	}

	return 0;
}

void CLCosmosFlower::Late_Update(void)
{
	if (m_bDead)
		m_eRendType = REND_END;
}

void CLCosmosFlower::Render(HDC hDC)
{
	HBRUSH myB = CreateSolidBrush(RGB(255, 155, 155));
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
		(int)(m_tInfo.vPos.x - 15 * 0.5f),
		(int)(m_tInfo.vPos.y - 15 * 0.5f),
		(int)(m_tInfo.vPos.x + 15 * 0.5f),
		(int)(m_tInfo.vPos.y + 15 * 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);
}

void CLCosmosFlower::Release(void)
{
}

void CLCosmosFlower::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}

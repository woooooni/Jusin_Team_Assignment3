#include "stdafx.h"
#include "LBee.h"
#include	"TimeMgr.h"



CLBee::CLBee(INFO	p_Info)
{
	m_tInfo = p_Info;
}


CLBee::~CLBee()
{
}

void CLBee::Initialize(void)
{
	m_tInfo.vDir = { 0, -1 , 0 };

	m_fSpeed = 30.f;
}

int CLBee::Update(void)
{
	if (m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f < 0)
	{
		m_bDead = true;
		return 1;
	}

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * DELTA_TIME;


	return 0;
}

void CLBee::Late_Update(void)
{
	if (m_bDead)
		m_eRendType = REND_END;
}

void CLBee::Render(HDC hDC)
{
	HBRUSH myB = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f),
		(int)(m_tInfo.vPos.y - m_tInfo.vSize.y* 0.5f),
		(int)(m_tInfo.vPos.x + m_tInfo.vSize.x* 0.5f),
		(int)(m_tInfo.vPos.y + m_tInfo.vSize.y* 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);
}

void CLBee::Release(void)
{
}

void CLBee::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}

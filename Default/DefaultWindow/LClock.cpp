#include "stdafx.h"
#include "LClock.h"
#include	"TimeMgr.h"

CLClock::CLClock() : m_fCurTime(0.f)
{
	ZeroMemory(m_strTmp, sizeof(m_strTmp));
}


CLClock::~CLClock()
{
}

void CLClock::Initialize(void)
{
	m_tInfo.vSize = { 100,100,0 };
}

int CLClock::Update(void)
{
	m_fCurTime += DELTA_TIME;

	return 0;
}

void CLClock::Late_Update(void)
{
}

void CLClock::Render(HDC hDC)
{
	RECT myR =
	{
		(LONG)(m_tInfo.vPos.x - m_tInfo.vSize.x),
		(LONG)(m_tInfo.vPos.y - m_tInfo.vSize.y),
		(LONG)(m_tInfo.vPos.x + m_tInfo.vSize.x),
		(LONG)(m_tInfo.vPos.y + m_tInfo.vSize.y)

	};


	swprintf_s(m_strTmp, L"%d", (int)m_fCurTime);

	DrawText(hDC, m_strTmp, lstrlen(m_strTmp), &myR, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void CLClock::Release(void)
{
}

void CLClock::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}

#include "stdafx.h"
#include "LItem.h"
#include	"TimeMgr.h"


CLItem::CLItem(INFO p_Info)
{
	m_tInfo = p_Info;
}


CLItem::~CLItem()
{
}

void CLItem::Initialize(void)
{
	m_tInfo.vSize = { 50.f, 50.f, 0.f };
	m_fSpeed = 100;
}

int CLItem::Update(void)
{

	Move();
	return 0;
}

void CLItem::Late_Update(void)
{
	if (m_bDead)
		m_eRendType = REND_END;
}

void CLItem::Render(HDC hDC)
{
	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f),
		(int)(m_tInfo.vPos.y - m_tInfo.vSize.y* 0.5f),
		(int)(m_tInfo.vPos.x + m_tInfo.vSize.x* 0.5f),
		(int)(m_tInfo.vPos.y + m_tInfo.vSize.y* 0.5f)
		);
}

void CLItem::Release(void)
{
}

void CLItem::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	if (p_Type == OBJ_PLAYER)
		m_bDead = true;
}

void CLItem::Move()
{
	if ((clamp(m_tInfo.vPos.x, m_tInfo.vSize.x * 0.5f, WINCX - m_tInfo.vSize.x * 0.5f) > m_tInfo.vPos.x && m_tInfo.vDir.x < 0)
		|| (clamp(m_tInfo.vPos.x, m_tInfo.vSize.x * 0.5f, WINCX - m_tInfo.vSize.x * 0.5f) < m_tInfo.vPos.x && m_tInfo.vDir.x > 0))
	{
		m_tInfo.vDir.x *= -1.f;
	}
	if ((clamp(m_tInfo.vPos.y, m_tInfo.vSize.y * 0.5f, WINCY - m_tInfo.vSize.y * 0.5f) > m_tInfo.vPos.y && m_tInfo.vDir.y < 0)
		|| (clamp(m_tInfo.vPos.y, m_tInfo.vSize.y * 0.5f, WINCY - m_tInfo.vSize.y * 0.5f) < m_tInfo.vPos.y && m_tInfo.vDir.y > 0))
	{
		m_tInfo.vDir.y *= -1.f;
	}


	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * DELTA_TIME;
}




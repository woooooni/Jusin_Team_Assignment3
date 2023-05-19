#include "stdafx.h"
#include "LShield.h"
#include	"ObjMgr.h"
#include	"TimeMgr.h"


CLShield::CLShield()
{
}


CLShield::~CLShield()
{
}

void CLShield::Initialize(void)
{
	m_eItemType = ITEM_SHIELD;
	m_tInfo.vSize = { 100, 100, 0 };

	m_fCreatedTime = 0.f;
	m_fMaxExistTime = 3.f;
}

int CLShield::Update(void)
{
	m_fCreatedTime += DELTA_TIME;

	if (Check_Dead())
	{

		return 1;
	}
	if (CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER))
		m_tInfo.vPos = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos;

	return 0;
}

void CLShield::Late_Update(void)
{
	if (m_bDead)
		m_eRendType = REND_END;
}

void CLShield::Render(HDC hDC)
{
	HBRUSH myB = CreateSolidBrush(RGB(0, 0, 255));
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

void CLShield::Release(void)
{
}

void CLShield::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}

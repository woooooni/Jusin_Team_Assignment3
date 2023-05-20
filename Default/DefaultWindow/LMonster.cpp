#include "stdafx.h"
#include "LMonster.h"
#include	"ObjMgr.h"
#include	"TimeMgr.h"

CLMonster::CLMonster(INFO	p_Info) : m_bTargetd(false)
{
	m_tInfo = p_Info;
}


CLMonster::~CLMonster()
{
}

void CLMonster::Initialize(void)
{
	m_tInfo.vSize = { 50.f, 50.f, 0.f };

	m_eObjType = OBJ_MONSTER;


}

int CLMonster::Update(void)
{
	Follow_Player();

	return 0;
}

void CLMonster::Late_Update(void)
{
}

void CLMonster::Render(HDC hDC)
{

	HBRUSH myB = CreateSolidBrush(RGB(255, 0, 0));
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

void CLMonster::Release(void)
{
}

void CLMonster::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	if (p_Type == OBJ_EFFECT)
		m_bDead = true;
}

void CLMonster::Follow_Player()
{
	CObj* player = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER);

	if (player == nullptr)
		return;

	m_tInfo.vDir = player->Get_Info().vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	m_fSpeed = 100.f * DELTA_TIME;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

}

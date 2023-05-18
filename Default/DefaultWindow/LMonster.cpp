#include "stdafx.h"
#include "LMonster.h"
#include	"ObjMgr.h"


CLMonster::CLMonster()
{
}


CLMonster::~CLMonster()
{
}

void CLMonster::Initialize(void)
{
	m_tInfo.vSize = { 50.f, 50.f, 0.f };

	m_fSpeed = 1.f;
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
}

void CLMonster::Release(void)
{
}

void CLMonster::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}

void CLMonster::Follow_Player()
{
	CObj* player = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER);

	if (player == nullptr)
		return;

	m_tInfo.vDir = player->Get_Info().vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

}

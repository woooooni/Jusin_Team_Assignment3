#include "stdafx.h"
#include "Laser_TW.h"
#include "Camera_TW.h"
#include "TimeMgr.h"
CLaser_TW::CLaser_TW()
	:CObj_TW(OBJ_TYPE::OBJ_LASER)
	, m_fLen(300.f)
{
}


CLaser_TW::~CLaser_TW()
{
	
}

void CLaser_TW::Initialize(void)
{
	m_fSpeed = 3000.f;
	SetScale(D3DXVECTOR3{ 30.f, 30.f, 0.f });
}

int CLaser_TW::Update(void)
{
	m_vPos += m_vDir * m_fSpeed * DELTA_TIME;
	return 0;
}

void CLaser_TW::Late_Update(void)
{

}

void CLaser_TW::Render(HDC hDC)
{
	D3DXVECTOR3 vRenderPos = CCamera_TW::GetInst()->GetRenderPos(GetPos());

	MoveToEx(hDC, vRenderPos.x - m_vDir.x * m_fLen, vRenderPos.y - m_vDir.y * m_fLen, nullptr);
	LineTo(hDC, vRenderPos.x + m_vDir.x * m_fLen, vRenderPos.y + m_vDir.y * m_fLen);

	
}

void CLaser_TW::Release(void)
{

}

void CLaser_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{

}

